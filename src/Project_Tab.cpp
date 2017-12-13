#include <headers/Projects_Tab.h>

UnrealatedLauncher::ProjectTabContainer::ProjectTabContainer(){
	Gtk::Label *v_TestLabel = Gtk::manage(new Gtk::Label);
	v_TestLabel->set_text(Glib::ustring("Test label, fuck you!"));
	add(*v_TestLabel);
//	show_all_children();
	
} // END : Project Tab Container

UnrealatedLauncher::ProjectTabContainer::~ProjectTabContainer(){
} // END : Project Tab Container Destructor
