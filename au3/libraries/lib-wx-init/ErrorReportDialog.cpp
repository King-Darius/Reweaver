/**********************************************************************

  Audacity: A Digital Audio Editor

  ErrorReportDialog.cpp

  Dmitry Vedenko

**********************************************************************/

#include "ErrorReportDialog.h"

#include <wx/app.h>
#include <wx/artprov.h>
#include <wx/button.h>
#include <wx/collpane.h>
#include <wx/dialog.h>
#include <wx/html/htmlwin.h>
#include <wx/icon.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/bmpbuttn.h>

#include "AllThemeResources.h"
#include "Theme.h"
#include "HelpText.h"
#include "Prefs.h"
#include "ShuttleGui.h"
#include "HelpSystem.h"

namespace {
// wxWidgets set an inaccessible border for the wxCollapsiblePane
// which makes layout of the dialog even more difficult.
// This code was copied from the wxWidgets 3.1.3 collpaneg.cpp
int GetCollapsiblePaneBorder(wxWindow* root)
{
#if defined(__WXMAC__)
    (void)root;
    return 6;
#elif defined(__WXMSW__)
    return root->ConvertDialogToPixels(wxSize(2, 0)).x;
#else
    (void)root;
    return 5;
#endif
}
}

BEGIN_EVENT_TABLE(ErrorReportDialog, wxDialogWrapper)
EVT_BUTTON(wxID_HELP, ErrorReportDialog::OnHelp)
END_EVENT_TABLE()

ErrorReportDialog::ErrorReportDialog(
    wxWindow* parent, const TranslatableString& dlogTitle,
    const TranslatableString& message, const ManualPageID& helpUrl,
    const wxString& log, const bool modal)
    : wxDialogWrapper(
        parent, wxID_ANY, dlogTitle, wxDefaultPosition, wxDefaultSize,
        wxDEFAULT_DIALOG_STYLE)
    , mHelpUrl(helpUrl)
{
    wxUnusedVar(modal);

    ShuttleGui S(this, eIsCreating);

    const wxFont headingFont = wxFont(wxFontInfo(12).Bold());
    const wxFont textFont = wxFont(wxFontInfo(10));

    const int CollapsibleBorderSize = GetCollapsiblePaneBorder(this);

    S.SetBorder(0);

    S.StartHorizontalLay(wxEXPAND, 0);
    {
        S.AddSpace(40 - CollapsibleBorderSize, 0);

        S.StartVerticalLay(wxEXPAND, 0);
        {
            S.AddSpace(0, 32);

            S.StartHorizontalLay(wxEXPAND, 0);
            {
                S.AddSpace(CollapsibleBorderSize);

                S.StartVerticalLay(wxEXPAND, 0);
                {
                    S.StartHorizontalLay(wxEXPAND, 1);
                    {
                        S.StartVerticalLay(0);
                        {
                            wxBitmap bitmap = wxArtProvider::GetBitmap(
                                wxART_WARNING, wxART_MESSAGE_BOX, wxSize(24, 24));

                            S.Prop(0).AddWindow(
                                safenew wxStaticBitmap(S.GetParent(), -1, bitmap));

                            S.AddSpace(0, 0, 1);
                        }
                        S.EndVerticalLay();

                        S.AddSpace(10, 0);

                        S.StartVerticalLay(0);
                        {
                            S.AddSpace(0, 7);

                            S.Prop(1)
                            .AddVariableText(message, false, 0, 560)
                            ->SetFont(headingFont);
                        }
                        S.EndVerticalLay();
                    }
                    S.EndHorizontalLay();

                    S.AddSpace(0, 20);

                    S.AddSpace(0, 12);
                    S.AddVariableText(
                        XO("Reweaver keeps crash diagnostics on your device. Nothing will be transmitted automatically."))
                    ->SetFont(textFont);

                    S.AddSpace(0, 6);

                    S.AddVariableText(
                        XO("You may copy the information below if you want to share it with someone you trust."))
                    ->SetFont(textFont);
                }
                S.EndVerticalLay();
            }
            S.EndHorizontalLay();

            S.AddSpace(0, 6);

            S.StartHorizontalLay(wxEXPAND, 0);
            {
                auto pane = safenew wxCollapsiblePane(
                    S.GetParent(), wxID_ANY, XO("Problem details").Translation());

                S.Style(wxEXPAND | wxALIGN_LEFT);
                S.Prop(1);
                S.AddWindow(pane);

                ShuttleGui SI(pane->GetPane(), eIsCreating);

                SI.StartVerticalLay();
                {
                    SI.Style(
                        wxTE_RICH | wxTE_READONLY | wxTE_MULTILINE | wxTE_DONTWRAP)
                    .MinSize(wxSize(0, 152))
                    .Name(XO("Problem details"))
                    .AddTextBox({}, log, 0);
                }
                SI.EndVerticalLay();
            }
            S.EndHorizontalLay();

            S.AddSpace(0, 20);

            S.StartHorizontalLay(wxEXPAND);
            {
                if (!mHelpUrl.empty()) {
                    wxBitmapButton* helpButton
                        =S.Id(wxID_HELP).AddBitmapButton(theTheme.Bitmap(bmpHelpIcon));
                    // For screen readers
                    helpButton->SetToolTip(XO("Help").Translation());
                    helpButton->SetLabel(XO("Help").Translation());
                }

                S.AddSpace(0, 0, 1);

                S.Id(wxID_OK).AddButton(XO("&OK"));
            }
            S.EndHorizontalLay();

            S.AddSpace(0, 20);
        }
        S.EndVerticalLay();

        S.AddSpace(28, 0);
    }
    S.EndHorizontalLay();

    S.SetBorder(2);

    Layout();
    GetSizer()->Fit(this);
    SetMinSize(GetSize());
    Center();
}

void ErrorReportDialog::OnHelp(wxCommandEvent& event)
{
    const auto& helpUrl = mHelpUrl.GET();
    if (helpUrl.StartsWith(wxT("innerlink:"))) {
        HelpSystem::ShowHtmlText(
            this, TitleText(helpUrl.Mid(10)), HelpText(helpUrl.Mid(10)), false,
            true);
        return;
    }

    HelpSystem::ShowHelp(this, mHelpUrl, false);
}
