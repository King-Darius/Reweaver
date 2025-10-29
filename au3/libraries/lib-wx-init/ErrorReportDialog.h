/**********************************************************************

  Audacity: A Digital Audio Editor

  ErrorReportDialog.h

  Dmitry Vedenko

**********************************************************************/

#ifndef __AUDACITY_SENTRYERRORDIALOG__
#define __AUDACITY_SENTRYERRORDIALOG__

#include <memory>

#include <wx/defs.h>
#include <wx/msgdlg.h>

#include "wxPanelWrapper.h" // to inherit

//! A dialog that presents error details without sending any data.
class ErrorReportDialog final : public wxDialogWrapper
{
public:
    ErrorReportDialog(
        wxWindow* parent, const TranslatableString& dlogTitle, const TranslatableString& message, const ManualPageID& helpUrl,
        const wxString& log, const bool modal);

    ~ErrorReportDialog() override = default;

private:
    void OnHelp(wxCommandEvent& event);

    ManualPageID mHelpUrl;

    DECLARE_EVENT_TABLE()
};

#endif // __AUDACITY_SENTRYERRORDIALOG__
