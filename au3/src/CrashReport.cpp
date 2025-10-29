/**********************************************************************

 Audacity: A Digital Audio Editor

 CrashReport.cpp

 *//*******************************************************************/

#include "CrashReport.h"

#if defined(HAS_CRASH_REPORT)
#include <wx/log.h>

#if defined(__WXMSW__)
#include <wx/evtloop.h>
#endif

#include "AudacityTextEntryDialog.h"
#include "Internat.h"

namespace CrashReport {
void Generate(wxDebugReport::Context)
{
    wxDebugReportCompress report;

    const auto notice = XO(
        "Reweaver does not automatically collect crash data, IP addresses, or other identifiers. "
        "This support bundle contains only this notice so you can share additional information manually if you choose.");

    report.AddText(
        wxT("ReweaverPrivacyNotice.txt"),
        notice.Translation(),
        XO("Reweaver Privacy Notice").Translation());

    const bool ok = wxDebugReportPreviewStd().Show(report);

#if defined(__WXMSW__)
    wxEventLoop::SetCriticalWindow(NULL);
#endif

    if (ok && report.Process()) {
        AudacityTextEntryDialog dlg(
            nullptr,
            XO("Support bundle created at:"),
            XO("Reweaver Support Bundle"),
            report.GetCompressedFileName(),
            wxOK | wxCENTER);
        dlg.SetName(dlg.GetTitle());
        dlg.ShowModal();

        wxLogMessage(wxT("Support bundle created at: %s"), report.GetCompressedFileName());

        report.Reset();
    }
}
}
#endif
