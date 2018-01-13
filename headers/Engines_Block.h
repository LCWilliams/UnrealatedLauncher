// ENGINE BLOCKS ARE THE BLOCKS PLACED WITHIN AN _ENGINEBLOCKCONTAINER_, RECURSIVELY FOR EACH ENGINE INSTALLED.
#ifndef ENGINE_BLOCK
#define ENGINE_BLOCK

// INCLUDES:
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include <gtkmm/menu.h>
#include <gtkmm/border.h>
#include <gtkmm/buttonbox.h>
#include <string>

using namespace std;

namespace UnrealatedLauncher{
	
	class EngineBlock : public Gtk::Grid{
	public:
		EngineBlock();
		virtual ~EngineBlock();
	
	protected:
	// GTK Elements:
		Gtk::Image img_EngineImage; // Decorative image for the engine.
		Gtk::Image img_EngineTypeIndicator; // Image semiotic to colourise enigne type; left side of engine block.
		Gtk::Button btn_EngineLaunch; // Button to launch the engine.
		Gtk::Button btn_Options; // Button to display options for this individual engine.
		Gtk::Menu v_EngineOptionMenu; // Used in conjunction with "btn_Options".
		Gtk::Label v_DisplayedEngineLabel; // The label displayed on the engine block; if null, the engine version number is used.

	// Settings/Info
		string v_EngineInstallDir; // Installation Directory
		string v_EngineSourceDir; // Directory of Source files (if not binary)
		string v_CustomEngineImageDir; // Custom engine image, if null the default is used.
		string v_EngineLabel; // Custom Engine Label, if null the engine version is used.
		bool v_EngineIsBinary; // Displays whether engine is built from tomato sauce, or binary.
		int v_EngineVersion; // The engine version number, ignoring the prefix 4.
		int v_EngineSubVersion; // The engine subversion number [hotfixex].
		bool v_EngineFlags[]; // A series of bool flags; future development shenanigans. 

	// Functions
		//Buttons
		void btn_EngineLaunch_Clicked(); // Function connected to button.
		//Functionality:
		void InstallEngine();
		void LaunchEngine();
		void UninstallEngine();
		void UpdateEngine();
	}; // END - EngineBlock Class
	
//	class EngineBlock_Short : public Gtk::Grid{
//	} // END - SHORT Engineblock.
	
} // END - Unrealated Launcher Namespace

#endif
//		void InstallAssistant();  Should probably be in Engines_TAB