#ifndef UNREALATEDLAUNCHERWINDOW
#define UNREALATEDLAUNCHERWINDOW
#include <gtkmm/application.h>
#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm/settings.h>
#include <gtkmm/cssprovider.h>

#include <cstring>
#include <string>
#include <X11/Xlib.h>


//#include <headers/LauncherMainPages.h>
#include <headers/Launcher_Projects.h>
#include <headers/Launcher_Engines.h>
#include <headers/Launcher_Marketplace.h>
#include <headers/Launcher_Community.h>

#include <headers/external/simpleIni/SimpleIni.h>

namespace UnrealatedLauncher{
	
	class UnrealatedLauncherWindow;
	class UnrealatedSettings;

class UnrealatedLauncherWindow : public Gtk::Window {
	
	public:
	UnrealatedLauncherWindow();
	virtual ~UnrealatedLauncherWindow();
	
	void settings_closed();
	bool launcherIdleCheck(); // Connected to run every second, checks all pages task count.
	
	
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
	Gtk::MenuItem menuItem_Launcher_Settings;
	Gtk::Menu v_LauncherMenu;
	
	// Page Refs:
	UnrealatedLauncher::Launcher_ProjectTab* v_projectsTabRef;
	UnrealatedLauncher::Launcher_EngineTab* v_enginesTabRef;
	UnrealatedLauncher::Launcher_MarketTab* v_marketTabRef;
	UnrealatedLauncher::Launcher_CommunityTab* v_communityTabRef;
	
	// Progress Bars:
	Gtk::ProgressBar v_ProjectsProgressBar;
	Gtk::ProgressBar v_EnginesProgressBar;
	Gtk::ProgressBar v_MarketProgressBar;
	Gtk::ProgressBar v_CommunityProgressBar;
	
	Gtk::Stack v_LauncherPageStack;
	Gtk::StackSwitcher btn_LauncherPageStack; // The Stack Switcher Buttons.
	Gtk::Revealer v_UtilityBarRevealer, v_settingsRevealer;
	Gtk::Grid v_UtilityBar;
	
	// Settings window;
	UnrealatedSettings* v_settingsRef; // Used to call initial run functions.

// FUNCTIONS
	void openDefaultTab();
	// Button Functions
	void on_QuickLaunch_clicked();
		// Launcher Menu Buttons
	void on_QuitClicked();
	void on_AboutClicked();
	void On_AboutWindow_Close(int p_response_id);
	void on_ToggleUtilityBar_Clicked();
	void on_Settings_Clicked();
	
	
	bool launcherIdle(); // Idle Update.
	
	
	void ReadPreferences(); // Reads the preferences file and applies [general] settings.

		// Main Button Functions
//	void btn_LauncherClicked();
	
}; // END - Class: Unrealated Launcher Window.

	class UnrealatedSettings : public Gtk::Grid{
		public:
		UnrealatedSettings();
		virtual ~UnrealatedSettings();
		
		UnrealatedLauncherWindow* v_windowRef;
		void missingPrefs(){ btn_confirmSettings_clicked(); } // Public function to cause the file to be created.
		void readPreferences(); // Reads the Ini file and changes the buttons accordingly
		
	protected:
	// Main Notebook:
		Gtk::Notebook v_settingsNotebook;

			// Scrolled window & flowbox for each tab:
		Gtk::ScrolledWindow page_general_scrollWindow, page_projects_scrollWindow, page_engines_scrollWindow, page_market_scrollWindow, page_community_scrollWindow;
		Gtk::FlowBox page_general_flowBox, page_projects_flowBox, page_engines_flowBox, page_market_flowBox, page_community_flowBox;

		Gtk::Button btn_confirmSettings, btn_cancelSettings, btn_resetAll;
		
		// GENERAL:
		Gtk::Grid page_general_interface;
		Gtk::Frame page_general_interface_frame;
		
		Gtk::Label txt_useSysTheme, txt_utilityOpenOnDefault, txt_showLauncherRepoStatus, txt_showLatestCommit, txt_defaultPage;
		Gtk::CheckButton btn_useSystemTheme, btn_utilityOpenOnDefault, btn_showLauncherRepoStatus, btn_showLatestCommit;
		Gtk::ComboBoxText btn_defaultPage;
		
		// ENGINES:
		Gtk::Grid page_engines_general, page_engines_directories, page_engines_addOptions, page_engines_manageLauncherRepo;
		Gtk::Frame page_engines_general_frame, page_engines_directories_frame, page_engines_addOptions_frame, page_engines_manageLauncherRepo_frame;
		
		Gtk::CheckButton btn_backgroundSync, btn_defaultShowBranches;
		Gtk::FileChooserButton btn_launcherRepoDir, btn_defaultInstallDir, btn_defaultSourceDir;
		Gtk::Label txt_backgroundSync, txt_launcherRepoUpdateInterval, txt_defaultShowBranches, txt_RepoDirLabel, txt_defaultInstallDirLabel, txt_defaultSourceDirLabel,
			txt_maxBranches, txt_maxCommits, txt_commitWrap;
		Gtk::SpinButton btn_launcherRepoUpdateInterval, btn_maxBranches, btn_maxCommits, btn_commitWrap;
			// Engines: manage local repo.
	//		Gtk::Button btn_cloneRepo
//		Gtk::Switch _tmp;

	// Button Functions:
		void btn_cancelSettings_clicked();
		void btn_confirmSettings_clicked();
		void btn_resetAll_clicked();
		
		void btn_backgroundSync_clicked();
		
	// Utility:
		void setPageGridSettings(Gtk::Grid* p_grid);
		void setPageFlowBoxSettings(Gtk::FlowBox* p_flowbox);
	};

} // END - Namespace

#endif // UNREALATEDLAUNCHERWINDOW