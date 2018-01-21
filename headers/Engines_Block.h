// ENGINE BLOCKS ARE THE BLOCKS PLACED WITHIN AN _ENGINEBLOCKCONTAINER_, RECURSIVELY FOR EACH ENGINE INSTALLED.
#ifndef ENGINE_BLOCK
#define ENGINE_BLOCK

// INCLUDES:
#include <gtkmm/window.h>

#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include <gtkmm/menu.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/progressbar.h>

#include <gtkmm/dialog.h>

// MAYBE:
#include <gtkmm/border.h> // Maybe
#include <gtkmm/scrolledwindow.h> // Maybe
#include <gtkmm/notebook.h> // Maybe

#include <string>
#include <fstream>

using namespace std;

namespace UnrealatedLauncher{
	
	class EngineBlock : public Gtk::Grid{
	public:
		EngineBlock(string p_installDir, string p_SourceDir, string p_customImageDir, string p_CustomLabel, int p_versionNumber, int p_hotfixNumber);
		virtual ~EngineBlock();
	
	// Settings/Info ... probably pointless.
		string v_EngineInstallDir, // Engine installation directory. 
		v_EngineSourceDir,  // Engine Source directory.
		v_CustomEngineImageDir,  // Custom image directory, default used if null.
		v_EngineLabel; // The combined engine label.
		int v_EngineVersion, v_EngineSubVersion;
		bool v_EngineIsBinary,
		// OPTIONS:
		option_CheckUpdates,
		option_safeUpdate;
		;

	protected:
	// GTK Elements:
		Gtk::ButtonBox v_buttonBox; // Container for buttons.
		Gtk::Button btn_EngineLaunch;
		Gtk::Image img_EngineImage; // Decorative image for the engine.
		Gtk::Menu v_EngineOptionMenu; // Used in conjunction with "btn_Options".
		Gtk::Label v_DisplayedEngineLabel, txt_EngineVer; // The label displayed on the engine block; if null, the engine version number is used.
		Gtk::ProgressBar v_ProgressBar;

		Gtk::ScrolledWindow v_OptionsGridWrapper;
		Gtk::Grid v_OptionsGrid;
		Gtk::Notebook v_OptionsNotebook;
		
		Gtk::MenuButton btn_Options;
		Gtk::Menu v_optionsMenu;
		Gtk::MenuItem menuItem_openPreferences;


	// Functions
		//Buttons
		void btn_EngineLaunch_Clicked(); // Function connected to button.
		void menuItem_openPreferences_clicked();
		//Functionality:
		void InstallEngine();
		void LaunchEngine();
		void UninstallEngine();
		void UpdateEngine();
		
		
		// CHECKERS:
		bool checkImageExists(const string& p_imageDir);
	}; 
// END - EngineBlock Class


	class EngineBlockOptions : public Gtk::Window{
	public:
		EngineBlockOptions();
		virtual ~EngineBlockOptions();
		
	protected:
		// Gtk elements:
		Gtk::ScrolledWindow v_scrolledWindow;
		Gtk::Grid v_windowGrid;
		
		// FUNCTIONS:
	}; 
// END - Engine Block Options

} // END - Unrealated Launcher Namespace

#endif
//		void InstallAssistant();  Should probably be in Engines_TAB