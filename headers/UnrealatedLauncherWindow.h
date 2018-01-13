#ifndef UNREALATEDLAUNCHERWINDOW
#define UNREALATEDLAUNCHERWINDOW

#include <gtkmm.h>
#include <headers/Projects_Tab.h>
#include <headers/UnrealatedLauncherWindow.h>
#include <headers/Projects_Tab.h>
#include <headers/Engines_Tab.h>
#include <headers/LauncherSettings.h>

namespace UnrealatedLauncher{

class UnrealatedLauncherWindow : public Gtk::Window {
	
	public:
	UnrealatedLauncherWindow();
	virtual ~UnrealatedLauncherWindow();
	
	protected:
// VARIABLES
	Gtk::AboutDialog v_aboutDialogue;
	// Buttons:
	Gtk::Button btn_Projects;
	Gtk::Button btn_Engines;
	Gtk::Button btn_Market;
	Gtk::Button btn_Community;
	Gtk::MenuButton btn_Launcher;
		// Utility bar QuickLaunch
	Gtk::Button btn_QuickLaunch;
	Gtk::LinkButton btn_link_help;
	
	
	// Menu Items
	Gtk::CheckMenuItem menuItem_Launcher_ToggleUtilityBar;
	
	Gtk::Stack v_LauncherPageStack;
	Gtk::StackSwitcher btn_LauncherPageStack; // The Stack Switcher Buttons.
	
	// Progress Bars:
	Gtk::ProgressBar v_ProjectsProgressBar;
	Gtk::ProgressBar v_EnginesProgressBar;
	Gtk::ProgressBar v_MarketProgressBar;
	Gtk::ProgressBar v_CommunityProgressBar;
	
	Gtk::Grid v_UtilityBar;
	
	Gtk::Menu v_LauncherMenu;

// FUNCTIONS
	void openDefaultTab();
	// Button Functions
	void on_QuickLaunch_clicked();
		// Launcher Menu Buttons
	void on_QuitClicked();
	void on_AboutClicked();
	void On_AboutWindow_Close(int p_response_id);
	void on_ToggleUtilityBar_Clicked();

		// Main Button Functions
	void btn_ProjectsClicked();
	void btn_EnginesClicked();
	void btn_MarketClicked();
	void btn_CommunityClicked();
	void toggleMainButtons(bool p_Enable); //Sets whether to set all main buttons as enabled (sensitive/default), or disabled.
	void updateMainWindow(int p_NewPage); //Updates the main window revealers, utilises ToggleMainButtons function.
	void btn_LauncherClicked();
	
}; // END - Class: Unrealated Launcher Window.

} // END - Namespace

#endif // UNREALATEDLAUNCHERWINDOW