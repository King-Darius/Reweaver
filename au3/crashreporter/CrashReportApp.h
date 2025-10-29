/*!********************************************************************
*
 Audacity: A Digital Audio Editor

 CrashReportApp.h

 Vitaly Sverchinsky

 **********************************************************************/

#include <wx/wx.h>
#include <map>
#include <string>

//! Crash reporter GUI application
/*! Presents crash information locally without performing any network access. */
class CrashReportApp final : public wxApp
{
    wxString mMinidumpPath;

    bool mSilent{ false };
public:
    bool OnInit() override;
    void OnInitCmdLine(wxCmdLineParser& parser) override;
    bool OnCmdLineParsed(wxCmdLineParser& parser) override;

private:
    void ShowCrashReport(const wxString& header, const wxString& text);
};

DECLARE_APP(CrashReportApp);
