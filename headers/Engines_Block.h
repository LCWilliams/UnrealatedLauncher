// DEPRECATED: TO BE REMOVED!!


// ENGINE BLOCKS ARE THE BLOCKS PLACED WITHIN AN _ENGINEBLOCKCONTAINER_, RECURSIVELY FOR EACH ENGINE INSTALLED.
#ifndef ENGINE_BLOCK
#define ENGINE_BLOCK

// INCLUDES:
#include <gtkmm/window.h>

#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include <gtkmm/menu.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/levelbar.h>
#include <gtkmm/infobar.h>

#include <gtkmm/dialog.h>

// MAYBE: (Options window)
#include <gtkmm/border.h> // Maybe
#include <gtkmm/scrolledwindow.h> // Maybe
#include <gtkmm/notebook.h> // Maybe

#include <string>
#include <fstream>
#include <dirent.h>
#include <cstdio>
#include <iostream>

#include <sys/stat.h>
#include <thread>

//#include <headers/LauncherMainPages.h>
// External:
#include <headers/external/simpleIni/SimpleIni.h>

class Launcher_EngineTab;

namespace UnrealatedLauncher{
using namespace std;
	
//	class EngineBlock : public Gtk::Grid{
//	public:
//		EngineBlock(string p_installDir, string p_SourceDir, string p_customImageDir, string p_CustomLabel, string p_gitCommit);
//		EngineBlock(string p_SettingsFileDir); // Create an engine block using existing settings.
//		virtual ~EngineBlock();
//		
//		int v_containerIndex; // Given by an external function, holds the index of the EngineBlock.
//		
//	// Settings/Info
//		string v_EngineInstallDir, // Engine installation directory. 
//		v_EngineSourceDir,  // Engine Source directory.
//		v_CustomEngineImageDir,  // Custom image directory, default used if null.
//		v_EngineLabel, // The custom engine label.
//		v_gitCommit; // The git commit the engine was built off.
//		
//		int v_InstallStatus; 
//		/*-2: Being deleted. Prompts continuation of deletion if interrupted.
//		-1: Ready to use.
//		0: Engine block only.
//		1: Source Downloaded.
//		2: Make Ran & completed.
//		3: Build ran & completed.
//		Variable saved to file.
//		*/
//		bool v_BuiltFromSource, // Is the engine binary or built from source.
//		// OPTIONS:
//		option_CheckUpdates,
//		option_safeUpdate;
//
//	protected:
//	// GTK Elements:
//		Gtk::ButtonBox v_buttonBox; // Container for buttons.
//		Gtk::Button btn_EngineLaunch; // Button to Launch the engine.
//		Gtk::Image img_EngineImage; // Decorative image for the engine.
//		Gtk::Menu v_EngineOptionMenu; // Used in conjunction with "btn_Options".
//		Gtk::Label v_DisplayedEngineLabel; // The GTK label displayed on the engine block.
//		Gtk::ProgressBar v_ProgressBar; // Displays progress of current operation.
//		Gtk::LevelBar v_LevelBar; // Splits up a series of operations for graphical feedback.
//		// InfoBar:
//		Gtk::InfoBar v_InfoBar; // Shows status information about the block (not installed/confirm deletion/etc)
//		Gtk::Button btn_infoBar_ContinueInstall, // Continues the installation if required.
//		btn_infoBar_ConfirmDelete, // Confirms a deletion.
//		btn_infoBar_CancelDelete, // Cancels a deletion.
//		btn_infoBar_Okay; // Confirm/Okay/Exit.
//		Gtk::Label txt_infoBarText; // Text used within an infobar.
//		
//		Gtk::MenuButton btn_Options;
//		Gtk::Menu v_optionsMenu, v_manageMenu;
//		Gtk::MenuItem 
//		menuItem_openSettings, menuItem_manageMenu,
//		menuItem_manage, menuItem_deleteEngine, menuItem_duplicateEngine, menuItem_archiveEngine;
//		
//		// Put Ini thing here
//
//
//	// Functions
//		void EngineBlockSetup(); // Runs attchment & general setup used by all constructors.
//		void PromptInfoBar(int p_typeCode, string p_message); /* 
//		0: Info message (must include a string!). 
//		1: Install not finished.
//		2: Confirm deletion.
//		*/
//		void Infobar_Cancel(); // Closes the infobar.
//		void InfoBarResponse(int p_response);
//		//Buttons
//		void btn_EngineLaunch_Clicked(); // Function connected to button.
//		void menuItem_openPreferences_clicked();
//		void menuItem_deleteEngine_clicked();
//		void menuItem_duplicateEngine_clicked();
//		void menuItem_archiveEngine_clicked();
//		
//		//Functionality:
//		void InstallEngine();
//		void LaunchEngine();
//		void UpdateEngine();
//		void DeleteEngine(); // Runs after confirmation
//		void threadFunction_DeleteEngine(); // The function that's passed to the thread.
//		void DeleteEngineDirectory(string p_directory); // Ran inside deleteEngine thread function, to recursively delete install directories.
//		void CheckInstallStatus(); // Performs status checks, and handles sensitivity & visibility of the block items.
//		
//		
//		// CHECKERS:
//		bool checkImageExists(const string& p_imageDir);
//		bool v_deleteThreadBusy;
//	};
//// END - EngineBlock Class

// END - Engine Block Options

} // END - Unrealated Launcher Namespace

#endif
//		void InstallAssistant();  Should probably be in Engines_TAB
