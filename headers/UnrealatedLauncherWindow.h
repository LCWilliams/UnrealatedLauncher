// COPYRIGHT © 2018
// AUTHOR(S):	Lee Connor Williams
// All Rights Reserved

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
#include <headers/Launcher_Global.h>
#include <headers/Launcher_Projects.h>
#include <headers/Launcher_Engines.h>			// Engines Tab
#include <headers/Launcher_Marketplace.h>		// Marketplace Tab
#include <headers/Launcher_Community.h>			// Community Tab
#include <headers/LauncherUtility.h>			// Launcher Utilities.
#include <headers/Launcher_RepoManagerGit.h>	// Repo Manager: Git Functions.

#include <sys/stat.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <limits.h>
#include <stdlib.h>

// External:
#include <headers/external/simpleIni/SimpleIni.h>
#include <headers/external/git2.h>

namespace UnrealatedLauncher{

	class UnrealatedLauncherWindow;
	class UnrealatedSettings;
	class UnrealatedLauncherRepoManager;

	class UnrealatedLauncherWindow : public Gtk::Window {
	
	public:
	UnrealatedLauncherWindow();
	virtual ~UnrealatedLauncherWindow();
	
	void settings_closed();		// Closes the launcher settings revealer. 
	void repoManager_closed();	// Closes the repo manager revealer.
	void repoManager_open();	// Opens the repo manager revealer.
	bool launcherIdleCheck();	// Connected to run every second, checks all pages task count.
	
	void repoManager_updateWindowProgressBar(double p_double){ // Updates the main window progress bar.
		if(p_double < 0){
			v_repoManagerProgressBar.pulse();
		} else{
			v_repoManagerProgressBar.set_fraction(p_double);
		}
	} // END - Update Window Progress Bar.
	
	void repoManager_setWindowProgressBarVisible(bool p_show){
		v_repoManagerProgressBar.set_visible(p_show);
	}

	
	bool repoManager_getRevealed(){	return v_repoManagerRevealer.get_reveal_child();	} // Returns the status of the revealer.
	
	
	Glib::RefPtr<Gtk::Application> ref_application;
	
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
	Gtk::MenuItem	menuItem_Launcher_About,
					menuItem_Launcher_Quit,
					menuItem_Launcher_Settings,
					menuItem_Launcher_RepoManager;
	Gtk::Menu v_LauncherMenu;
	
	// Page Refs:
	UnrealatedLauncher::Launcher_ProjectTab* v_projectsTabRef;
	UnrealatedLauncher::Launcher_EngineTab* v_enginesTabRef;
	UnrealatedLauncher::Launcher_MarketTab* v_marketTabRef;
	UnrealatedLauncher::Launcher_CommunityTab* v_communityTabRef;
	
	// Progress Bars:
	Gtk::ProgressBar	v_ProjectsProgressBar,
						v_EnginesProgressBar,
						v_MarketProgressBar,
						v_CommunityProgressBar,
						v_repoManagerProgressBar;
	
	Gtk::Stack v_LauncherPageStack;
	Gtk::StackSwitcher btn_LauncherPageStack; // The Stack Switcher Buttons.
	Gtk::Revealer v_UtilityBarRevealer, v_settingsRevealer, v_repoManagerRevealer;
	Gtk::Grid v_UtilityBar;
	
	// Settings window;
	UnrealatedSettings* v_settingsRef; // Used to call initial run functions.
	UnrealatedLauncherRepoManager* v_launcherRepoManagerRef;
	

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
	void menuItem_Launcher_RepoManager_clicked();


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
		
		// PUBLIC SETTINGS:
			// General:
			
			// Engines:
			string 	settings_launcherRepositoryDirectory;	// Directory of the launcher repository.
			string	settings_launcherHomeDirectory;			// Directory of the launchers home directory.

			
		// END - PUBLIC SETTINGS
		
	protected:
	// Main Notebook:
		Gtk::Notebook v_settingsNotebook;

			// Scrolled window & flowbox for each tab:
		Gtk::ScrolledWindow	page_general_scrollWindow,
							page_projects_scrollWindow, 
							page_engines_scrollWindow, 
							page_market_scrollWindow, 
							page_community_scrollWindow;
		Gtk::FlowBox	page_general_flowBox, 
						page_projects_flowBox, 
						page_engines_flowBox, 
						page_market_flowBox, 
						page_community_flowBox;

		Gtk::Button	btn_confirmSettings, 
					btn_cancelSettings, 
					btn_resetAll;
		
		// GENERAL:
		Gtk::Grid page_general_interface;
		
		Gtk::Frame page_general_interface_frame;
		
		Gtk::Label txt_defaultPage;
		
		Gtk::CheckButton	btn_useSystemTheme, 
							btn_utilityOpenOnDefault, 
							btn_showLauncherRepoStatus, 
							btn_showLatestCommit;
		Gtk::ComboBoxText btn_defaultPage;
		
		// ENGINES:
		Gtk::Grid	page_engines_general, 
					page_engines_directories, 
					page_engines_addOptions, 
					page_engines_manageLauncherRepo;
		
		Gtk::Frame	page_engines_general_frame,
					page_engines_directories_frame,
					page_engines_addOptions_frame,
					page_engines_manageLauncherRepo_frame;
		
		Gtk::CheckButton	btn_backgroundSync,
							btn_backgroundSync_regenLists,
							btn_defaultShowTaggedCommits;
		
		Gtk::FileChooserButton	btn_launcherRepoDir,
								btn_defaultInstallDir, 
								btn_defaultSourceDir;

		Gtk::Label	txt_launcherRepoUpdateInterval,
					txt_RepoDirLabel,
					txt_defaultInstallDirLabel,
					txt_defaultSourceDirLabel,
					txt_maxTaggedCommits, 
					txt_maxCommits, 
					txt_commitWrap;
		
		Gtk::SpinButton	btn_launcherRepoUpdateInterval,
						btn_maxTaggedCommits,
						btn_maxCommits,
						btn_commitWrap;

	// Button Functions:
		void btn_cancelSettings_clicked();
		void btn_confirmSettings_clicked();
		void btn_resetAll_clicked();
		
		void btn_backgroundSync_clicked();
		
		void settings_writeSettingsVariables();	// Reads the ini settings and stores them in public variables.
		
	// Utility:
		void setPageFlowBoxSettings(Gtk::FlowBox* p_flowbox);
	};

class UnrealatedLauncherRepoManager : public Gtk::Grid{
	public:
		UnrealatedLauncherRepoManager();
		virtual ~UnrealatedLauncherRepoManager();

// PUBLIC VARIABLES:
		UnrealatedLauncherWindow* ref_window;

// PUBLIC FUNCTIONS:
		void launcherRepoManager_setup(); // Modifies the UI for initial usage.
		void launcherRepoManager_setRepoDirectory(string* p_path);
		void launcherRepoManager_setSettingsReference(UnrealatedSettings* p_settingsReference);
		void launcherRepoManager_setStatusFields(double p_progressPercent, string p_task, string p_taskProgress);	// Updates the status elements.
		
// INTER-THREAD COMMUNICATION:
		bool threadComm_onlineTaskBusy = false;	// Used to check if an online task is busy, and used by timeouts.
		bool threadComm_loginPrompt = false;
		bool threadComm_attemptedLoginWithSavedInfo = false; 	// Used by IF within credential callback to either prompt a login, or use existing credentials.
//		unsigned int threadComm_currentTask = 0;// Incremental int, used by a switch within timeouts for efficiency.
		condition_variable threadComm_loginPrompt_conditionVar;		// Condition variable used to pause the onlineThread if a login prompt is called.

		mutex threadComm_mutex_currentStage;	// Mutex that protects the thread_comm_* variables.
		string threadComm_username, threadComm_password;	// Git Username & password set from Login prompt.

// GIT ITEMS:
		string repoManager_repoDirectory;
		git_repository*	repoManager_repo;
		git_remote*		repoManager_remoteRepo;
		git_cred*		repoManager_gitCredential;
		git_transport* repoManager_transport;

		const char *repoManager_RepoURL = "https://github.com/EpicGames/UnrealEngine.git"; 


//		const char *repoManager_RepoURL = "git://github.com/libgit2/TestGitRepository.git"; 
	

		// UI Buffer
		string	threadComm_repoStatusText = "",				// Text used to update the repository status.
				threadComm_currentTaskText = "",			// Text used to update the current task.
				threadComm_currentTaskProgressText = "";	// Text used to update the current task progress; shown in the progress bar.
		double	threadComm_currentTaskProgress = 0;			// Double used to update the progress bar.
		unsigned int	threadComm_currentStage;			// Integer of the current stage for a multi-stage process.
		
	
	private:
// PRIVATE VARIABLES:
		UnrealatedSettings* ref_settings;

		Gtk::FlowBox v_repoManager_flowBox;
		
		Gtk::Frame	repoManager_login_frame, 
					repoManager_manageButtons_frame, 
					repoManager_status_frame,
					repoManager_options_frame;
		
		Gtk::Grid	repoManager_login,
					repoManager_manageButtons,
					repoManager_status,
					repoManager_options;
					
		Gtk::Button	btn_closeWindow;			// Button for closing the manager window.
		
		
// LOGIN:
		Gtk::Grid v_login_subgrid_loginEntries;
		
		Gtk::Revealer v_login_revealer;	// Revealer to show/hide the login when nessecery.
		
		Gtk::Label	txt_login_username,
					txt_login_password,
					txt_login_status_label,
					txt_login_status;

		Gtk::Entry	btn_login_username,
					btn_login_password;
					
		Gtk::Button	btn_login_login,	// Attached function changes condition variable.
					btn_login_logout;	// Release is visible only if a SSH key is present.
		Gtk::CheckButton btn_login_rememberDetails;	// Double acts as bool get/set; 

// BUTTONS/MANAGE:
		Gtk::Button	btn_manage_getNew,
					btn_manage_update,
					btn_manage_generateLists,
					btn_manage_updateAll,
					btn_manage_clearRepo,
					btn_manage_clearRepoConfirm,
					btn_manage_clearRepoCancel;
		Gtk::ButtonBox btn_manage_clearRepo_box; // Button box for ClearRepo confirm/cancel.
		
// STATUS:
		Gtk::Label	txt_status_currentTask_label,
					txt_status_currentTask,
					txt_status_repoStatus_label,
					txt_status_repoStatus;

		Gtk::ProgressBar v_status_progressBar;

		Gtk::LevelBar v_status_levelBar;
		
		Gtk::Button	btn_status_cancel,
					btn_status_cancel_force; // Cancel calls git_cancel.  Force calls terminate.
		
		thread*		ref_currentThread; // Reference for current thread, in order to call terminate.


// OPTIONS:
//		Gtk::Button btn_options_stopSync;
		


// FUNCTIONS:
	// Button function.
		void btn_closeWindow_clicked();
		void btn_login_login_clicked();
		void btn_login_logOut_clicked();

		void btn_manage_getNew_clicked();
		void btn_manage_generateLists_clicked();
		void btn_manage_update_clicked();
		void btn_manage_updateAll_clicked();
		void btn_manage_clearRepo_clicked();
		void btn_manage_clearRepoCancel_clicked();
		void btn_manage_clearRepoConfirm_clicked();
			int clearRepo_calledCount; // Incremented each time the function is called.  Used as bool for final loop to set currentStage.
		void btn_status_cancel_clicked();
		void btn_status_cancel_force_clicked();
		
		void RepoManager_updateRepoDir(){	// Grabs settings_launcherRepositoryDirectory and stores it in repoManager_repoDirectory.
		repoManager_repoDirectory = ref_settings->settings_launcherRepositoryDirectory;
		}
		
	//	UI Related
		void RepoManager_setOnlineRelated(bool p_state);	// Changes the sensitivity of online related buttons.
		
		
	//	Git related | Defined in Launcher_RepoManager_Git.cpp
		bool RepoManagerGit_OpenRepo();			// Opens the launcher repository.  Returns FALSE on error/doesn't exist.
		void RepoManagerGit_SetCloneOptions(git_clone_options* p_cloneOptions);	// Sets Clone Options.
		void RepoManagerGit_SetFetchOptions(git_fetch_options* p_fetchOptions);	// Sets fetch options.
	
	// Timeout Functions (Inter-thread communication: declared in Launcher_Repomanager_Threads.cpp
		void RepoManager_timeout_updateGUI();// Repetative code, updates all GUI items within Status.
		bool RepoManager_timeout();
		
	// Thread Functions:
		void RepoManager_thread_GetNew();
		void RepoManager_thread_GenerateLists();
		void RepoManager_thread_update();
		void RepoManager_thread_updateAll();
		void RepoManager_thread_clearRepo();
		void RepoManager_thread_clearRepoPath(string p_directory);
		void RepoManager_thread_taskFailed(string p_status, string p_consoleError); // Status for GUI text, console error printed to the terminal. Closes Libgit2.
		
		// Probably redundant:
		bool RepoManager_timeout_getNew();
		bool RepoManager_timeout_update();
		bool RepoManager_timeout_updateAll();
		bool RepoManager_timeout_clearRepo();
	
}; // END - Unrealated launcher repo manager.

} // END - Namespace



#endif // UNREALATEDLAUNCHERWINDOW