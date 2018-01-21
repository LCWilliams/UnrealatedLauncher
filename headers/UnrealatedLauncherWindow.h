#ifndef UNREALATEDLAUNCHERWINDOW
#define UNREALATEDLAUNCHERWINDOW

#include <headers/LauncherMainPages.h>
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
	Gtk::MenuButton btn_Launcher;
		// Utility bar QuickLaunch
	Gtk::Button btn_QuickLaunch;
	Gtk::LinkButton btn_link_help;
	
	// Menu Items
	Gtk::CheckMenuItem menuItem_Launcher_ToggleUtilityBar;
	Gtk::Menu v_LauncherMenu;
	
	// Progress Bars:
	Gtk::ProgressBar v_ProjectsProgressBar;
	Gtk::ProgressBar v_EnginesProgressBar;
	Gtk::ProgressBar v_MarketProgressBar;
	Gtk::ProgressBar v_CommunityProgressBar;
	
	Gtk::Stack v_LauncherPageStack;
	Gtk::StackSwitcher btn_LauncherPageStack; // The Stack Switcher Buttons.
	Gtk::Grid v_UtilityBar;	

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
//	void btn_LauncherClicked();
	
}; // END - Class: Unrealated Launcher Window.

} // END - Namespace

#endif // UNREALATEDLAUNCHERWINDOW