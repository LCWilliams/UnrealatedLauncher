// Header consists of the classes responsible for the main pages of the launcher.
// Single header reduces multiple includes, allows usage of gtkmm in efficient manner.

#ifndef LAUNCHERMAINPAGES
#define LAUNCHERMAINPAGES

// INCLUDES:
#include <gtkmm.h>
#include <string>

using namespace std;

namespace UnrealatedLauncher{

// PROJECT TAB
	class Launcher_ProjectTab : public Gtk::Grid{
	public:
		Launcher_ProjectTab();
		virtual ~Launcher_ProjectTab();

	protected:
		typedef struct{
			const bool cppProject;
			const int enigneVersion;
		}STR_Projects; // END - Struct
	
	// Tool bar:
		Gtk::ActionBar v_ProjectsToolbar;
		Gtk::Button btn_Filter;
		Gtk::Button btn_ProjectTabOptions;
		Gtk::SearchEntry btn_ProjectSearchEntry;
	// Functions:
	
	}; // END - Launcher_ProjectTab class.


// ENGINE TAB
	class Launcher_EngineTab : public Gtk::Grid{
	public:
		Launcher_EngineTab();
		virtual ~Launcher_EngineTab();
	// Public Functions:
	
	protected:
//		Gtk::ListStore thingforFlowbox;
		Gtk::FlowBox v_EngineFlowBox;
		Gtk::ScrolledWindow v_FlowboxScrolledWindowWrapper; // A Scrolled window wrapper for the Flowbox.
		
		struct STR_Engine{
			int versionNumber; // The version number, ignoring the 4. prefix.
			int hotfixNumber; // The hotfix number of the version.
			int updatePolicy; // Updates the engine with the following policies:  0- Overwrite.  1- Duplicate Then Delete, 2- Duplicate, 3- Duplicate then Archive
			bool sourceBuild; // Is the engine a source build, or binary.
			bool archived; // Is the engine currently archived (compressed).
			string installDir; // The directory of the engine installation root.
			string sourceDir; // The directory of the engine source.
			string customLabel; // A custom label, if null- the engine version is used.
			Gtk::Image customImage; // A custom image, if null, the default is used.
		}ENGINE;
	
	// Tool bar:
		Gtk::ActionBar v_EnginesToolbar;
		Gtk::Button btn_Filter;
		Gtk::Button btn_EnginesTabOptions;
		Gtk::SearchEntry btn_EnginesSearchEntry;
		Gtk::Button btn_AddEngine;
	}; // END - Launcher_EngineTab class.


// MARKET TAB
	class Launcher_MarketTab : public Gtk::Grid{
	public:
		Launcher_MarketTab();
		virtual ~Launcher_MarketTab();
		
	protected:
		//
	}; // END - Launcher_MarketTab class


// COMMUNITY TAB
	class Launcher_CommunityTab : public Gtk::Grid{
	public:
		Launcher_CommunityTab();
		virtual ~Launcher_CommunityTab();
		
	protected:
		//
	}; // END - Launcher_CommunityTab class.


} // END - Unrealated Launcher NameSpace.

#endif