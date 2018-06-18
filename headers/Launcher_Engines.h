// COPYRIGHT © 2018
// AUTHOR(S):	Lee Connor Williams
// All Rights Reserved


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
#include <sys/types.h>
#include <unistd.h>
//#include <filesystem>

#include <headers/LauncherUtility.h>
#include <headers/Launcher_Global.h>

// External:
#include <headers/external/simpleIni/SimpleIni.h>
#include <headers/external/git2.h>


//	typedef struct git_repository; // Not used...

namespace UnrealatedLauncher{
	using namespace std;
	
	class EngineBlock;
	class Launcher_EngineTab;
	class EngineAdd;
	class UnrealatedLauncherWindow;

	class Launcher_EngineTab : public Gtk::Grid{
	public:
		Launcher_EngineTab();
		virtual ~Launcher_EngineTab();
		vector<EngineBlock*> v_EngineBlockArray;
		EngineAdd* ref_EngineAdd;
		UnrealatedLauncherWindow* ref_mainWindow;	// reference to parent window.
		
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
		void middleMan_openRepoManager(); // Middle Man:  Called from tab references, which then calls a parent object function.
//	void Update_updateLocalRepoBtn();
		void AddNewEngine(); // Opens side bar.
		
		bool middleMan_openRepoManager_bool = false;	// Checked by timeout in parent window: if true, Add_Sidebar is insensitive and repo manager is shown.
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
		EngineBlock(string p_installDir, string p_customImageDir, string p_CustomLabel, string p_gitCommit, string p_codeEditor);
		EngineBlock(string p_SettingsFileDir); // Create an engine block using existing settings.
		virtual ~EngineBlock();
		
		Launcher_EngineTab* v_TabReference;
		
	// Settings/Info
		string v_EngineInstallDir, // Engine installation directory. 
		v_CustomEngineImageDir,  // Custom image directory, default used if null.
		v_EngineLabel,	// The custom engine label.
		v_gitCommit,	// The git commit the engine was built off.
		v_codeEditor;	// The code editor used with this engine.
		
		int v_InstallStatus; 
		/*-2: Being deleted. Prompts continuation of deletion if interrupted.
		-1: Ready to use.
		0: Engine block only.
		1: Source Downloaded.
		2: Make Ran & completed.
		3: Build ran & completed.
		Variable saved to file.
		*/
		
		
	// Public Functions:
		void EngineBlock_install(){
			v_TabReference->AddPageTask();
			v_ProgressBar.show();
			v_LevelBar.show();
			btn_Options.set_sensitive(false);
//			Glib::signal_timeout().connect(sigc::mem_fun(*this, &EngineBlock::installEngine_timeout), 50);
			InstallEngine();  // Function connects a timeout.
			}	// Public function proxy: Runs the installation function.
			void InfoBarResponse(int p_response);

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
		Gtk::Menu v_optionsMenu, v_manageMenu, menu_build;
		Gtk::MenuItem 
		menuItem_openSettings, menuItem_manageMenu, menuItem_build,
		menuItem_manage, menuItem_deleteEngine, menuItem_duplicateEngine, menuItem_archiveEngine,
		menu_build_generateFiles, menu_build_build, menu_build_rebuild;



	// Functions
		void EngineBlockSetup(); // Runs attchment & general setup used by all constructors.
		void PromptInfoBar(int p_typeCode, string p_message); /* 
		0: Info message (must include a string!). 
		1: Install not finished.
		2: Confirm deletion.
		*/
		void Infobar_Cancel(); // Closes the infobar.
		//Buttons
		void btn_EngineLaunch_Clicked(); // Function connected to button.
		void menuItem_openPreferences_clicked();
		void menuItem_deleteEngine_clicked();
		void menuItem_duplicateEngine_clicked();
		void menuItem_archiveEngine_clicked();
		
		void menu_build_generateFiles_clicked();
		void menu_build_build_clicked();
		void menu_build_rebuild_clicked();
		
		
		//Functionality:
		void LaunchEngine();
		void UpdateEngine();
		void CheckInstallStatus(); // Performs status checks, and handles sensitivity & visibility of the block items.
		void threadFunction_launchEngine(); // Starts the engine on a new thread to not lock the UI.
		bool threadFunction_DeleteEngine_idle();	// Timeout for deletion GUI.
		string threadComm_delete_taskText;		// Thread comm: Delete, text to be put in the progress bar.
		double threadComm_delete_taskPercent;	// Percentage of task completed.
		mutex threadComm_delete_mutex;
		
		// Install Engine:
		bool installEngine_threadBusy = false;	// Bool, used by timeout to re-run installEngine.
		bool installEngine_errorOccured = false;
		string installEngine_progressText;		// Text to be put into the progress bar.
		double installEngine_progress;			// Double used to update the progress bar.
		mutex installEngine_mutex;
		
		void InstallEngine();			// Main Function holding the switch.
		bool installEngine_timeout();	// GUI updated in here.
		bool installEngine_menuItem_timeout();	// GUI updated in here for Menu Item functions.
		void installEngine_thread_copySource();	// Thread: Copy source.
		void installEngine_thread_generateFiles();		
		void installEngine_thread_make();		// Make.
		void installEngine_passwordPrompt();	// POSSIBLY REDUNDANT.
		
		void DeleteEngine(); // Runs after confirmation
		void threadFunction_DeleteEngine(); // The parent function that's passed to the thread.
		void EngineBlock_thread_Delete(string p_directory); // Ran inside deleteEngine thread function, to recursively delete install directories.
		void EngineBlock_thread_Delete_count(string p_path);
		int	deleteEngine_filesTotal,
			deleteEngine_calledCount;
		float deleteEngine_filesDeleted;
		
		
		// CHECKERS:
		bool checkImageExists(const string& p_imageDir);
		bool v_deleteThreadBusy;
		bool engineBlock_run;	// Bool to determine if the engine block is running.
		mutex engineBlock_run_mutex;	// Mutex used for checking if the engine block is running.
		bool engineBlock_run_timeout();	// Timeout function.
	};




	class EngineAdd : public Gtk::Grid{
	public:
		EngineAdd();
		virtual ~EngineAdd();
//		vector<EngineBlock*> v_engineBlockArray;
		
		Launcher_EngineTab* v_tabReference; // Set by parent.

		void EngineAdd_reset();
		bool EngineAdd_startInstallAfterFinished;
		
		struct installData{
			string	engineLabel = "",
					installDir = "",
					customImage = "",
					commitID = "",
					codeEditor = "";
		}installData;
		
	private:
	
	Gtk::Revealer v_revealer_online; // Revealer for online (commits, manage repo).
	
	Gtk::Frame	section_initial_frame,		// Frame for initial section.
				section_commits_frame,		// Frame for commit options.
				section_directories_frame,	// Frame for directory options.
				section_labelAndImage_frame,// Frame for engine label & custom image.
				section_confirm_frame;		// Frame that houses a preview of the output.
	
	Gtk::Grid 	section_initial,		// Grid for initial objects.
				section_commits, 		// Grid for commit objects.
				commits_toggleGrid,		// Subgrid for commit_toggle option: placing in normal grid breaks homogonousness.
				section_directories,	// Grid for directories.
				section_labelAndImage,	// Grid for engine label & custom image selector.
				section_confirm;		// Grid for confirmation.
	
	Gtk::RadioButton	btn_toggle_showTags, 
						btn_toggle_showCommits; // Toggle button pair


	Gtk::CheckButton btn_addExisting,				// Checkbox, status of is used to update v_revealer_online.
					 btn_showCommitsAfterTaggedCommit,	// Checkbox, reveals branch selector and modifies shown commits.
					 btn_appendLabelToInstallDir,	// Checkbox, determines whether label is appended to install directory.
					 btn_makeCopyOfImage,			// Checkbox, determines whether to make a copy of the custom image.
					 btn_startInstallAfterFinished;
	
	Gtk::FileChooserButton	btn_chooser_installFolder,	// Folder chooser for install directory.
							btn_chooser_customImage;	// File chooser for custom image.
	
	Gtk::AppChooserButton	btn_chooser_codeEditor;		// Code editor chooser.
	
	Gtk::Button btn_cancel, btn_confirm,// Apply & Confirm buttons.
				btn_manageLauncherRepo,	// Opens launcher repo management.
				btn_initial_updateLists;// Resets the list currently used by branches/all. 
				
	Gtk::ComboBoxText btn_commitSelector, btn_taggedCommitSelector;
	
	Gtk::Entry btn_labelEntry; // Engine label entry.
	
	Gtk::Label	txt_chooser_taggedCommits,
				txt_chooser_commits,
				txt_chooser_installFolder,
				txt_chooser_customImage,
				txt_chooser_codeEditor,
				txt_confirm_commit_label,
				txt_confirm_installFolder_label,
				txt_confirm_commit, 		// The commit to be used.
				txt_confirm_installFolder,	// The install folder.
				txt_confirm_helper,			// Helper text, informs of issues.
				txt_confirm_codeEditor_label,
				txt_confirm_codeEditor;
				
	// TEMP/SAVE: Variables used to save values during state changes.
	string 	temp_lastInstallDirectory; // String, holds the directory of the last chosen directories.
	
	int		commits_taggedIterations,
			commits_normalIterations;	// The number of iterations (commits) to show in the selectors.
	
	
	// FUNCTIONS:
		void SetConfirmTextSettings(Gtk::Label* p_label);
		
		// Timeouts:
		bool setupTimeout(); // Runs setup.
		
		// Button Signals:
		void btn_addExisting_changed();
		void btn_initial_updateLists_clicked();
		void btn_showCommitsAfterBranch_changed();
		void btn_manageLauncherRepo_clicked();
		void btn_toggle_showCommitsFilter();
		void btn_chooser_installFolder_changed();
		void btn_cancel_clicked();
		void btn_confirm_clicked();
		void btn_labelEntry_changed();
		void btn_appendLabelToInstallDir_changed();
		void btn_taggedCommitSelector_changed();
		void btn_selectorChanged();
		void btn_chooser_customImage_changed();
		void btn_chooser_codeEditor_changed();
		
		void EngineAdd_CanContinue();	// Changes the state of the CONFIRM button.

		
		
		bool EngineAdd_populateSelector(Gtk::ComboBoxText* p_selector, int p_iterations, string p_path, bool p_removeTagPrefix); /*
		  * Populates a selector with the contents of the given file in Path.
		  * Removes TAG prefix if set.
		  * Iterations should be given from user preferences.
		  * */ 
	}; // END - EngineAdd namespace.
} // END - Unrealated Launcher Namespace.

#endif
