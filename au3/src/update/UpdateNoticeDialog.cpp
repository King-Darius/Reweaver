/*!********************************************************************

 Audacity: A Digital Audio Editor

 @file UpdateNoticeDialog.cpp
 @brief Declare a dialog to notify the user about automatic update checking.

 Dmitry Vedenko
 **********************************************************************/

#include "UpdateNoticeDialog.h"

#include <wx/button.h>
#include <wx/stattext.h>

#include "ShuttleGui.h"

static const auto title
    =/* i18n-hint: Title of the offline update notice dialog. */
      XO("Manual updates");

static const auto firstParagraph
    =/* i18n-hint: The first paragraph of the offline update notice dialog. */
      XO("Reweaver does not contact update servers or download releases automatically.");

static const auto secondParagraph
    =/* i18n-hint: The second paragraph of the offline update notice dialog. */
      XO("To stay informed about new versions, check trusted distribution channels manually whenever it suits you.");

BEGIN_EVENT_TABLE(UpdateNoticeDialog, wxDialogWrapper)
EVT_BUTTON(wxID_OK, UpdateNoticeDialog::OnOk)
EVT_SIZE(UpdateNoticeDialog::OnSize)
END_EVENT_TABLE()

IMPLEMENT_CLASS(UpdateNoticeDialog, wxDialogWrapper)

UpdateNoticeDialog::UpdateNoticeDialog(wxWindow* parent)
    : wxDialogWrapper(
        /* i18n-hint: Title of the app update notice dialog. */
        parent, -1, XO("App updates"), wxDefaultPosition, wxDefaultSize,
        wxCAPTION | wxCLOSE_BOX)
{
    ShuttleGui S(this, eIsCreating);

    S.StartVerticalLay();
    {
        S.AddSpace(0, 16);

        S.StartHorizontalLay(wxEXPAND, 0);
        {
            S.AddSpace(24, 0);

            S.StartPanel();
            {
                S.SetBorder(8);

                wxStaticText* titleCtrl = S.AddVariableText(title, false, 0, 500);

                wxFont font = titleCtrl->GetFont().MakeLarger().MakeBold();

                titleCtrl->SetFont(font);

                S.AddFixedText(firstParagraph, false, 500);

                S.AddFixedText(secondParagraph, false, 500);

                S.AddSpace(0, 8);
            }
            S.EndPanel();

            S.AddSpace(24, 0);
        }
        S.EndHorizontalLay();

        S.StartHorizontalLay(wxEXPAND);
        {
            S.AddSpace(1, 0, 1);

            S.Id(wxID_OK).AddButton(XO("&OK"))->SetFocus();

            S.AddSpace(8, 0);
        }
        S.EndHorizontalLay();
    }

    S.EndVerticalLay();

    Fit();
    Layout();

    Center();
}

void UpdateNoticeDialog::OnOk(wxCommandEvent&)
{
    EndModal(wxOK);
}

void UpdateNoticeDialog::OnSize(wxSizeEvent&)
{
    Fit();
    Layout();
}
