#ifndef UNREALATEDLAUNCHERWINDOW
#define UNREALATEDLAUNCHERWINDOW

#include <gtkmm.h>
#include <headers/Projects_Tab.h>
#include <headers/UnrealatedLauncherWindow.h>
#include <headers/Projects_Tab.h>
#include <headers/LauncherSettings.h>
#include <headers/LauncherMainButtons.h>

namespace UnrealatedLauncher{

class UnrealatedLauncherWindow : public Gtk::Window {
	
	public:
	UnrealatedLauncherWindow();
	virtual ~UnrealatedLauncherWindow();
	
	protected:
	// VARIABLES
	Gtk::AboutDialog v_aboutDialogue;
	UnrealatedLauncher::ProjectTabContainer v_ProjectsWindow;
	// Buttons:
	Gtk::Button btn_Projects;
	Gtk::Button btn_Engines;
	Gtk::Button btn_Market;
	Gtk::Button btn_Community;
	LauncherMainButton btn_Test;

	// FUNCTIONS
	void ToggleMainButtons(bool p_Enable); // Deprecating
	void UpdateMainWindow(int p_NewPage);
	// Button Functions
	void on_QuitClicked();
	void on_AboutClicked();
	void On_AboutWindow_Close(int p_response_id);
	void btn_ProjectsClicked();
	void btn_EnginesClicked();
	void btn_MarketClicked();
	void btn_CommunityClicked();

}; // END - Class: Unrealated Launcher Window.

} // END - Namespace

#endif // UNREALATEDLAUNCHERWINDOW