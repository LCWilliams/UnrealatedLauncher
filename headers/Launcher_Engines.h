#ifndef LAUNCHERENGINES
#define LAUNCHERENGINES

#include <gtkmm.h>
#include <gtkmm/combobox.h>
#include <string>
#include <vector>

#include <string>
#include <fstream>
#include <dirent.h>
#include <cstdio>
#include <stdio.h>
#include <iostream>

#include <sys/stat.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <limits.h>
#include <stdlib.h>
// External:
#include <headers/external/simpleIni/SimpleIni.h>

#include <headers/external/git2.h>
//#include <headers/external/git2/sys/repository.h>

//	typedef struct git_repository; // Not used...

namespace UnrealatedLauncher{
	using namespace std;
	
	class EngineBlock;
	class Launcher_EngineTab;
//	class UnrealatedLauncherWindow;


	class Launcher_EngineTab : public Gtk::Grid{
	public:
		Launcher_EngineTab();
		virtual ~Launcher_EngineTab();
		vector<EngineBlock*> v_EngineBlockArray;
//		UnrealatedLauncher::UnrealatedLauncherWindow* v_windowRef; // Ref to parent window.
	
	// Public Functions:
		void DeleteEngineBlock(EngineBlock* p_blockReference); // Removes an enigne block, and its files.
		void CloseAddWizard();
		void AddPageTask(){
			mutex_engineTab.lock();
			v_tasks++;
			if(v_tasks < 1){SetPageTaskPercent(0);}
			cout << "Page Tasks is now: " << v_tasks << endl;
			mutex_engineTab.unlock();
		} // Increments the number of tasks the page is performing.
		void RemovePageTask(){
			mutex_engineTab.lock();
			v_tasks--; 
			if(v_tasks < 0){v_tasks = 0;}
			cout << "Page Tasks is now: " << v_tasks << endl;
			mutex_engineTab.unlock();
		} // Decrements the number of tasks the page is performing.
		void SetPageTaskPercent(double p_progress){ v_taskProgress = p_progress; }; // Sets the task progress to the given value.
		 int GetPageTasks(){return v_tasks;} // Gets the current number of tasks the page is performing.
		double GetPageTaskProgress(){return v_taskProgress;} // Gets the current task progress.  Not used if more than one task is running.
	
//	void Update_updateLocalRepoBtn();
		
		unsigned int v_tasks = 0; // Number of tasks in progress; If higher than 1, pulse is used.
		double v_taskProgress = 0; // Used to update page progress bar.
		mutex mutex_engineTab;

	private:
		Gtk::FlowBox v_EngineFlowBox;
		Gtk::ScrolledWindow v_FlowboxScrolledWindowWrapper; // A Scrolled window wrapper for the Flowbox.
		Gtk::InfoBar v_pageInfoBar; // The Engine page info bar.
		Gtk::Label txt_pageInfoBarText; // Infobar text.
		Gtk::Button btn_pageInfoBar_okay; // "Okay" button.

	// Tool bar:
		Gtk::ActionBar v_EnginesToolbar;
		Gtk::Button btn_Filter, btn_EnginesTabOptions;
		Gtk::SearchEntry btn_EnginesSearchEntry;
		Gtk::Button btn_AddEngine;
		
	// Side Panel:
		Gtk::Revealer v_EngineTabSidePanel;
		Gtk::Grid v_sidePanelGrid; // Grid held inside the panel
		Gtk::Grid v_sidepanelSubGrid_Add; // Convenience grid, contains the Add wizard.
		Gtk::Grid v_sidepanelSubGrid_Details; // Convenience grid, contains Engine details.


	// Functions:
		void btn_AddEngine_clicked();
		
		// Info Bar:
		void btn_pageInfoBar_okay_clicked();

		void AddNewEngine(); // Opens side bar.
		void AddExistingEngines(); // Ran at construction; adds existing engines.
		void RemoveAddEngine(); // Removes the add engine wizard

/* Legacy Code...
		Gtk::Menu menu_AddEngine;
		Gtk::MenuItem menuItem_addExisting, menuItem_addNew, menuItem_oneClickAdd;
		void btn_TEST_clicked();
*/
	}; // END - Launcher_EngineTab class.




	class EngineBlock : public Gtk::Grid{
	public:
		EngineBlock(string p_installDir, string p_SourceDir, string p_customImageDir, string p_CustomLabel, string p_gitCommit);
		EngineBlock(string p_SettingsFileDir); // Create an engine block using existing settings.
		virtual ~EngineBlock();
		
		Launcher_EngineTab* v_TabReference;
		
	// Settings/Info
		string v_EngineInstallDir, // Engine installation directory. 
		v_EngineSourceDir,  // Engine Source directory.
		v_CustomEngineImageDir,  // Custom image directory, default used if null.
		v_EngineLabel, // The custom engine label.
		v_gitCommit; // The git commit the engine was built off.
		
		int v_InstallStatus; 
		/*-2: Being deleted. Prompts continuation of deletion if interrupted.
		-1: Ready to use.
		0: Engine block only.
		1: Source Downloaded.
		2: Make Ran & completed.
		3: Build ran & completed.
		Variable saved to file.
		*/
		bool v_BuiltFromSource, // Is the engine binary or built from source.
		// OPTIONS:
		option_CheckUpdates,
		option_safeUpdate;

	protected:
	// GTK Elements:
		Gtk::ButtonBox v_buttonBox; // Container for buttons.
		Gtk::Button btn_EngineLaunch; // Button to Launch the engine.
		Gtk::Image img_EngineImage; // Decorative image for the engine.
		Gtk::Menu v_EngineOptionMenu; // Used in conjunction with "btn_Options".
		Gtk::Label v_DisplayedEngineLabel; // The GTK label displayed on the engine block.
		Gtk::ProgressBar v_ProgressBar; // Displays progress of current operation.
		Gtk::LevelBar v_LevelBar; // Splits up a series of operations for graphical feedback.
		// InfoBar:
		Gtk::InfoBar v_InfoBar; // Shows status information about the block (not installed/confirm deletion/etc)
		Gtk::Button btn_infoBar_ContinueInstall, // Continues the installation if required.
		btn_infoBar_ConfirmDelete, // Confirms a deletion.
		btn_infoBar_CancelDelete, // Cancels a deletion.
		btn_infoBar_Okay; // Confirm/Okay/Exit.
		Gtk::Label txt_infoBarText; // Text used within an infobar.
		
		Gtk::MenuButton btn_Options;
		Gtk::Menu v_optionsMenu, v_manageMenu;
		Gtk::MenuItem 
		menuItem_openSettings, menuItem_manageMenu,
		menuItem_manage, menuItem_deleteEngine, menuItem_duplicateEngine, menuItem_archiveEngine;



	// Functions
		void EngineBlockSetup(); // Runs attchment & general setup used by all constructors.
		void PromptInfoBar(int p_typeCode, string p_message); /* 
		0: Info message (must include a string!). 
		1: Install not finished.
		2: Confirm deletion.
		*/
		void Infobar_Cancel(); // Closes the infobar.
		void InfoBarResponse(int p_response);
		//Buttons
		void btn_EngineLaunch_Clicked(); // Function connected to button.
		void menuItem_openPreferences_clicked();
		void menuItem_deleteEngine_clicked();
		void menuItem_duplicateEngine_clicked();
		void menuItem_archiveEngine_clicked();
		
		//Functionality:
		void InstallEngine();
		void LaunchEngine();
		void UpdateEngine();
		void DeleteEngine(); // Runs after confirmation
		void threadFunction_DeleteEngine(); // The function that's passed to the thread.
		void DeleteEngineDirectory(string p_directory); // Ran inside deleteEngine thread function, to recursively delete install directories.
		void CheckInstallStatus(); // Performs status checks, and handles sensitivity & visibility of the block items.
		
		
		// CHECKERS:
		bool checkImageExists(const string& p_imageDir);
		bool v_deleteThreadBusy;
	};




	class EngineAdd : public Gtk::Grid{
	public:
		EngineAdd();
		virtual ~EngineAdd();
		vector<EngineBlock*> v_engineBlockArray;
		
		Launcher_EngineTab* v_tabReference;
		
		// PUBLIC FUNCTIONS:
		void updateLocalRepo_updateProgbar(Glib::ustring p_message, double p_progress){
			if(v_statusProgBar.is_visible()){
//				if(v_mutex_progress.try_lock()){
				v_statusProgBar_text = p_message;
				v_statusProgBar_progress = p_progress;
//				v_mutex_progress.unlock();
//				} // END - Mutex try lock
			} // END - Progressbar visible
		} // End - Update progbar data.
		void updateLocalRepo_updatePageBar(double p_progress){ 
			v_tabReference->SetPageTaskPercent(p_progress);
		}
		char updateLocalRepo_getLoginUsername(){return *login_username.c_str();}
		char updateLocalRepo_getLoginUserpass(){return *login_password.c_str();}
		
		condition_variable v_waitingOnLogin_conditionVar; 
		bool v_waitingOnLogin; // Set by Credential callback, reveals the login entries by Monitor Function.
		mutex v_mutex_waitingOnLogin;
	private:
	// Protected by MUTEX:
		vector<string> vec_commitComment; // Stores the commit comments
		vector<string> vec_commitIDs; // Stores the commit IDs.
		mutex v_mutex_commits;
		
		double v_statusProgBar_progress = 0; // Stores the percentage; set by "updateProgbar", grabbed by monitor function
		string v_statusProgBar_text = ""; // Stores the text to display; set by "updateProgbar", grabbed by monitor function
		Gtk::ComboBoxText v_commitSelector;
		mutex v_mutex_progress;
		
		
	
	
		// GTK Elements:
		Gtk::Label txt_label_selectSource, txt_label_selectInstall, txt_label_sourceExample, txt_label_installExample,
		txt_label_engineLabel, txt_label_engineLabelStatus, txt_label_imageLabel;
		Gtk::Button btn_cancel, btn_confirm;
		Gtk::ButtonBox v_confirmCancelButtonBox, v_commitTypeRadioButtonBox;
		Gtk::Border v_border;
		Gtk::FileChooserButton btn_sourceFolder, btn_installFolder, btn_customImageChooser;
		Gtk::Entry v_engineLabel;
		
		
		// Online:
		bool gitInitialised = false; // Used to check status of git.
		unsigned int v_maxCommits = 1000; // Replaced with value from settings
		unsigned int v_currentCommitIndex = 0; // Temp variable.
		Gtk::ToggleButton btn_addExisting; // Doubles as bool; controls visibility of revealer.
		Gtk::Revealer v_onlineRevealer; // Holds the Online Grid
		Gtk::Grid v_onlineGrid; // Holds all the online related Widgets.
		Gtk::Button btn_updateLocalRepo, btn_gitLogin;
		Gtk::Label txt_label_version, txt_label_selectCommit;
		Gtk::RadioButton btn_showCommits, btn_showBranches;
		Gtk::ProgressBar v_statusProgBar;
		// Inter-thread Communication:
		bool v_OnlineThreadBusy = false; // Set at start and end of thread function; controls monitor function.
		
		const char *REPO_PATH = "git@github.com:EpicGames/UnrealEngine.git"; 
		string v_launcherRepoPath;
	
		// Login:
		Gtk::Revealer v_loginRevealer;
		Gtk::Grid v_loginGrid;
		Gtk::Entry btn_login_username, btn_login_password;
		Gtk::Label txt_label_loginUsername, txt_label_loginPassword, txt_label_loginStatus;
		string login_username;
		string login_password;
		
		// Functions: Buttons & Signal Responders
			// General:
		void btn_Cancel_clicked();
		void btn_Confirm_clicked();
		void btn_installFolder_changed();
		void btn_sourceFolder_changed();
		void btn_customImageChooser_changed();
		void v_engineSelector_changed();
		void v_engineLabel_changed();

			// Online
		void btn_addExisting_clicked();
		void btn_updateLocalRepo_clicked();
		void threadFunction_updateLocalRepo(); // Main function

		// Online: Subfunctions
		void localRepo_cleanup(); // Performs cleanup.
		bool localRepo_populateCommits(); // Populates the
		
			// Login:
		void btn_gitLogin_clicked();

		// Functions: Utility
		void CheckCanConfirm(); // Checks all input is valid before allowing Confirm to be sensitive.
		bool MonitorActivity(); // Idle function, monitors boolean and changes button state when finished.
		 

		// Idle Timeout:
		bool updateLocalRepo_finalStep();

		string utility_RemoveFileFromString(string p_stringToModify){ 
			return p_stringToModify.erase(0, 7); 
		} // END - Utility Remove File From String
		
		void updateLocalRepo_AddCommit(string p_commitID, string p_commitComment){ // Adds a commit to both vectors.
			vec_commitIDs.push_back(p_commitID);
			vec_commitComment.push_back(p_commitComment);
//			v_commitSelector.append(p_commitComment);
		} // END - Add commit
		

		int utility_checkDirectories(string p_directory){ /**
		 * Returns 0 if directory is not used. 
		 * 1 if it is used as an install dir.  
		 * 2 if it is used as a source dir.
		 **/
		 int returnCode = 0;
		 
			for(int index = 0; index < static_cast<int>(v_tabReference->v_EngineBlockArray.size()); index++){
				if(p_directory == v_tabReference->v_EngineBlockArray[index]->v_EngineInstallDir)returnCode = 1;
				if(p_directory == v_tabReference->v_EngineBlockArray[index]->v_EngineSourceDir)returnCode = 2;
			} // END - For Loop
		return(returnCode);
		} // END - Utility CheckDirs.
		void status_onlineTaskFailed(string p_message, string p_consoleMessage){ // p_Message: brief message put into the progress bar.  Console Message: More thorough message printed to console.
			v_OnlineThreadBusy = false;

			v_statusProgBar.set_text(p_message);
			cout << p_consoleMessage << endl; 
			cerr << " [GIT ERROR: " << giterr_last()->message << "]" << endl << endl;
			
			git_libgit2_shutdown();
		}  // END - Online task failed.
	};


} // END - Unrealated Launcher Namespace.

#endif
