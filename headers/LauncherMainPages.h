#ifndef LAUNCHERMAINPAGES
#define LAUNCHERMAINPAGES

// INCLUDES:
#include <gtkmm.h>

namespace UnrealatedLauncher{

// PROJECT TAB
	class Launcher_ProjectTab : public Gtk::Grid{
	public:
		Launcher_ProjectTab();
		virtual ~Launcher_ProjectTab();
	
	protected:
	
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
	
	// Tool bar:
	Gtk::ActionBar v_EnginesToolbar;
	Gtk::Button btn_Filter;
	Gtk::Button btn_EnginesTabOptions;
	Gtk::SearchEntry btn_EnginesSearchEntry;
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
		virtual ~Launcher_ProjectTab();
		
	protected:
		//
	}; // END - Launcher_CommunityTab class.


} // END - Unrealated Launcher NameSpace.

#endif