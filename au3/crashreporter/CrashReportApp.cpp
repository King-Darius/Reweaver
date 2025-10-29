#include "CrashReportApp.h"

#include <memory>
#include <vector>

#include <wx/cmdline.h>
#include <wx/chartype.h>
#include <wx/artprov.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/filefn.h>

#include "google_breakpad/processor/basic_source_line_resolver.h"
#include "google_breakpad/processor/minidump_processor.h"
#include "google_breakpad/processor/process_state.h"
#include "google_breakpad/processor/minidump.h"
#include "processor/stackwalk_common.h"

#include "warning.xpm"

#include <Internat.h>

IMPLEMENT_APP(CrashReportApp);
namespace {
void PrintMinidump(google_breakpad::Minidump& minidump)
{
    google_breakpad::BasicSourceLineResolver resolver;
    google_breakpad::MinidumpProcessor minidumpProcessor(nullptr, &resolver);
    google_breakpad::MinidumpThreadList::set_max_threads(std::numeric_limits<uint32_t>::max());
    google_breakpad::MinidumpMemoryList::set_max_regions(std::numeric_limits<uint32_t>::max());

    google_breakpad::ProcessState processState;

    if (minidumpProcessor.Process(&minidump, &processState) != google_breakpad::PROCESS_OK) {
        printf("Failed to process minidump");
    } else {
        google_breakpad::PrintProcessState(processState, true, false, &resolver);
    }
}

wxString MakeDumpString(google_breakpad::Minidump& minidump, const wxString& temp)
{
#if _WIN32
    auto stream = _wfreopen(temp.wc_str(), L"w+", stdout);
#else
    auto stream = freopen(temp.utf8_str().data(), "w+", stdout);
#endif
    if (stream == NULL) {
        throw std::runtime_error("Failed to print minidump: cannot open temp file");
    }
    PrintMinidump(minidump);
    fflush(stdout);

    auto length = ftell(stream);
    std::vector<char> bytes(length);
    fseek(stream, 0, SEEK_SET);
    fread(&bytes[0], 1, length, stream);
    fclose(stream);

#if _WIN32
    _wremove(temp.wc_str());
#else
    remove(temp.utf8_str().data());
#endif

    return wxString::From8BitData(&bytes[0], bytes.size());
}

wxString MakeHeaderString(google_breakpad::Minidump& minidump)
{
    if (auto exception = minidump.GetException()) {
        if (auto rawException = exception->exception()) {
            // i18n-hint C++ programming assertion
            return wxString::Format(_("Exception code 0x%x"), rawException->exception_record.exception_code);
        } else {
            // i18n-hint C++ programming assertion
            return _("Unknown exception");
        }
    } else if (auto assertion = minidump.GetAssertion()) {
        auto expression = assertion->expression();
        if (!expression.empty()) {
            return expression;
        }
    }
    return _("Unknown error");
}

void DoShowCrashReportFrame(const wxString& header, const wxString& dump)
{
    auto dialog = new wxDialog(
        nullptr,
        wxID_ANY,
        _("Problem Report for Reweaver"),
        wxDefaultPosition,
        wxDefaultSize,
        wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)
        );

#if defined(__WXMSW__)
    dialog->SetFocus();
#endif

    auto mainLayout = new wxBoxSizer(wxVERTICAL);

    auto headerLayout = new wxBoxSizer(wxHORIZONTAL);
    headerLayout->Add(new wxStaticBitmap(dialog, wxID_ANY, wxIcon(warning)));
    headerLayout->AddSpacer(5);

    auto headerText = new wxStaticText(dialog, wxID_ANY, header);
    headerText->SetFont(wxFont(wxFontInfo().Bold()));
    headerLayout->Add(headerText, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

    mainLayout->Add(headerLayout, wxSizerFlags().Border(wxALL));
    mainLayout->AddSpacer(5);

    auto privacyMessage = new wxStaticText(
        dialog,
        wxID_ANY,
        _("Reweaver keeps crash diagnostics on your device. No information is transmitted automatically."));
    privacyMessage->Wrap(480);
    mainLayout->Add(privacyMessage, wxSizerFlags().Border(wxLEFT | wxRIGHT));

    mainLayout->AddSpacer(5);

    auto deletionMessage = new wxStaticText(
        dialog,
        wxID_ANY,
        _("The temporary minidump has been removed. You may copy the details below if you wish to share them manually."));
    deletionMessage->Wrap(480);
    mainLayout->Add(deletionMessage, wxSizerFlags().Border(wxLEFT | wxRIGHT));

    mainLayout->AddSpacer(10);
    mainLayout->Add(new wxStaticText(dialog, wxID_ANY, _("Problem details")), wxSizerFlags().Border(wxALL));

    auto dumpTextCtrl = new wxTextCtrl(
        dialog,
        wxID_ANY,
        dump,
        wxDefaultPosition,
        wxSize(500, 300),
        wxTE_RICH | wxTE_READONLY | wxTE_MULTILINE | wxTE_DONTWRAP);
    dumpTextCtrl->SetFont(wxFont(wxFontInfo().Family(wxFONTFAMILY_TELETYPE)));
    dumpTextCtrl->ShowPosition(0);
    mainLayout->Add(dumpTextCtrl, wxSizerFlags().Border(wxALL).Expand());

    auto buttonsLayout = new wxBoxSizer(wxHORIZONTAL);

    auto okButton = new wxButton(dialog, wxID_OK, wxT("OK"));
    okButton->Bind(wxEVT_BUTTON, [dialog](wxCommandEvent&)
    {
        dialog->Close(true);
    });
    buttonsLayout->Add(okButton);

    mainLayout->Add(buttonsLayout, wxSizerFlags().Border(wxALL).Align(wxALIGN_RIGHT));
    dialog->SetSizerAndFit(mainLayout);

    dialog->Bind(wxEVT_CLOSE_WINDOW, [dialog](wxCloseEvent&)
    {
        dialog->Destroy();
    });

    dialog->Show(true);
}

}

bool CrashReportApp::OnInit()
{
    if (!wxApp::OnInit()) {
        return false;
    }

    static std::unique_ptr<wxLocale> sLocale(new wxLocale(wxLANGUAGE_DEFAULT));
#if defined(__WXOSX__)
    sLocale->AddCatalogLookupPathPrefix(wxT("../Resources"));
#elif defined(__WXMSW__)
    sLocale->AddCatalogLookupPathPrefix(wxT("Languages"));
#elif defined(__WXGTK__)
    sLocale->AddCatalogLookupPathPrefix(wxT("./locale"));
    sLocale->AddCatalogLookupPathPrefix(wxString::Format(wxT("%s/share/locale"), wxT(INSTALL_PREFIX)));
#endif
    sLocale->AddCatalog("audacity");
    sLocale->AddCatalog("wxstd");

    google_breakpad::Minidump minidump(mMinidumpPath.ToStdString(), false);
    if (!minidump.Read()) {
        return false;
    }

    wxFileName temp(mMinidumpPath);
    temp.SetExt("tmp");

    wxString header;
    wxString details;
    try
    {
        header = MakeHeaderString(minidump);
        details = MakeDumpString(minidump, temp.GetFullPath());
    }
    catch (std::exception& e)
    {
        wxMessageBox(e.what());
        return false;
    }

    if (wxFileExists(mMinidumpPath)) {
        wxRemoveFile(mMinidumpPath);
    }

    if (mSilent) {
        wxPrintf("%s\n\n%s\n", header, details);
        return false;
    }

    SetExitOnFrameDelete(true);
    ShowCrashReport(header, details);
    return true;
}

void CrashReportApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    static const wxCmdLineEntryDesc cmdLineEntryDesc[] =
    {
        { wxCMD_LINE_SWITCH, "s", "silent", "Process the minidump without opening the user interface" },
        { wxCMD_LINE_PARAM,  NULL, NULL, "path to minidump file", wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY },
        { wxCMD_LINE_NONE }
    };

    parser.SetDesc(cmdLineEntryDesc);

    wxApp::OnInitCmdLine(parser);
}

bool CrashReportApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    mMinidumpPath = parser.GetParam(0);
    mSilent = parser.Found("s");

    return wxApp::OnCmdLineParsed(parser);
}

void CrashReportApp::ShowCrashReport(const wxString& header, const wxString& text)
{
    DoShowCrashReportFrame(header, text);
}
