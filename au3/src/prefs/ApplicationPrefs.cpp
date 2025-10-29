/**********************************************************************

  Audacity: A Digital Audio Editor

  ApplicationPrefs.cpp

  Anton Gerasimov


*******************************************************************//**

\class ApplicationPrefs
\brief A PrefsPanel to enable/disable certain general application options like checking updates, etc.

*//*******************************************************************/

#include "ApplicationPrefs.h"
#include "update/UpdateManager.h"

#include <wx/defs.h>
#include <wx/hyperlink.h>

#include "Prefs.h"
#include "ShuttleGui.h"

#include "AccessibleLinksFormatter.h"

////////////////////////////////////////////////////////////////////////////////

static ComponentInterfaceSymbol s_ComponentInterfaceSymbol{ XO("Application") };

ApplicationPrefs::ApplicationPrefs(wxWindow* parent, wxWindowID winid)
    :  PrefsPanel(parent, winid, XO("Application"))
{
    Populate();
}

ApplicationPrefs::~ApplicationPrefs()
{
}

ComponentInterfaceSymbol ApplicationPrefs::GetSymbol() const
{
    return s_ComponentInterfaceSymbol;
}

TranslatableString ApplicationPrefs::GetDescription() const
{
    return XO("Preferences for Application");
}

ManualPageID ApplicationPrefs::HelpPageName()
{
    return "Application_Preferences";
}

void ApplicationPrefs::Populate()
{
    //------------------------- Main section --------------------
    // Now construct the GUI itself.
    // Use 'eIsCreatingFromPrefs' so that the GUI is
    // initialised with values from gPrefs.
    ShuttleGui S(this, eIsCreatingFromPrefs);
    PopulateOrExchange(S);
    // ----------------------- End of main section --------------
}

void ApplicationPrefs::PopulateOrExchange(ShuttleGui& S)
{
    S.SetBorder(2);
    S.StartScroller();

    /* i18n-hint: Title for the update notifications panel in the preferences dialog. */
    S.StartStatic(XO("Update notifications"));
    {
        S.StartVerticalLay();
        {
            S.AddFixedText(
                XO("Reweaver does not perform automatic update checks. No network requests are made unless you initiate them manually."),
                false,
                470);

            S.AddFixedText(
                XO("You can check for new releases through trusted distribution channels without the application contacting any servers."),
                false,
                470);
        }

        S.EndVerticalLay();
    }

    S.EndStatic();
    S.EndScroller();
}

bool ApplicationPrefs::Commit()
{
    ShuttleGui S(this, eIsSavingToPrefs);
    PopulateOrExchange(S);
    DefaultUpdatesCheckingFlag->Invalidate();

    return true;
}

namespace {
PrefsPanel::Registration sAttachment{ "Application",
                                      [](wxWindow* parent, wxWindowID winid, AudacityProject*)
    {
        wxASSERT(parent); // to justify safenew
        return safenew ApplicationPrefs(parent, winid);
    }
};
}
