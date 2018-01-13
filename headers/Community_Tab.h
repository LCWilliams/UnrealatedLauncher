#ifndef COMMUNITY_TAB
#define COMMUNITY_TAB
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/searchentry.h>
#include <gtkmm/actionbar.h>
#include <gtkmm/button.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/flowbox.h>

namespace UnrealatedLauncher{
	
	class CommunityTabContainer : public Gtk::Grid{
	// THE CONTAINER USED TO HOUSE ALL ELEMENTS PERTAINING TO ENGINES.

	public:
		CommunityTabContainer();
		virtual ~CommunityTabContainer();

	protected:
	Gtk::ScrolledWindow v_CommunityScrolledWindow;
//	Gtk::Grid v_EngineBlockGrid; // Grid placed inside the scrolled window to house engine blocks; allows for easier filtering.

	//Toolbar Buttons:
	Gtk::ActionBar v_EnginesToolbar;
	Gtk::Button btn_Filter;
	Gtk::Button btn_EnginesWindowOptions;
	Gtk::SearchEntry v_EnginesSearchEntry;
	Gtk::Button btn_AddNew;
	
	// FUNCTIONS:
	void createExisting(); // Creates all existing
	void installEngine(); // Engine Installer

	
	}; // END - EngineTabContainer Class
	
} // END - Namespace: Unrealated Launcher

#endif