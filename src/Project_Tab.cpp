#include <headers/Projects_Tab.h>


UnrealatedLauncher::ProjectTabContainer::ProjectTabContainer(){
	set_row_spacing(10);
	set_row_homogeneous(false);
	set_vexpand(true);
	
// SCROLL WINDOW
	attach(v_ProjectScrolledWindow, 0, 0, 1, 1);
	// Configuration:
	v_ProjectScrolledWindow.set_hexpand(true);
	v_ProjectScrolledWindow.set_vexpand(true);


// UTILITY BAR [Bottom]
	attach(v_ProjectToolbar, 0, 1, 1, 1);

	// Configuration:
	v_ProjectToolbar.set_hexpand(true);
	v_ProjectToolbar.set_valign(Gtk::ALIGN_BASELINE);
	
	v_ProjectToolbar.pack_end(btn_ProjectWindowOptions);
	v_ProjectToolbar.pack_end(btn_Filter);
	v_ProjectToolbar.pack_end(v_ProjectSearchEntry);
	
	// NEED IMAGES!
//	btn_Filter.set_image();
//	btn_ProjectWindowOptions.set_image();
	btn_Filter.set_label("Filter");
	btn_ProjectWindowOptions.set_label("Options");
	
} // END : Project Tab Container

UnrealatedLauncher::ProjectTabContainer::~ProjectTabContainer(){
} // END : Project Tab Container Destructor
