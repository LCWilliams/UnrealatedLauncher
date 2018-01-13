#ifndef PROJECTSTAB
#define PROJECTSTAB

#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/searchentry.h>
#include <gtkmm/actionbar.h>
#include <gtkmm/button.h>
#include <gtkmm/scrolledwindow.h>

namespace UnrealatedLauncher{

	class ProjectTabContainer : public Gtk::Grid{

	public:
		ProjectTabContainer();
		virtual ~ProjectTabContainer();

	protected:
	Gtk::ScrolledWindow v_ProjectScrolledWindow;

	//Search/Buttons:
	Gtk::Button btn_Filter;
	Gtk::Button btn_ProjectWindowOptions;
	Gtk::SearchEntry v_ProjectSearchEntry;
	Gtk::ActionBar v_ProjectToolbar;

	}; // END - Project Tab Container Class.

} // END - Unrealated Launcher namespace.
#endif