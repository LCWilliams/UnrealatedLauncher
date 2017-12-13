#include <headers/LauncherMainButtons.h>
using namespace UnrealatedLauncher;

LauncherMainButton::LauncherMainButton(){
//	set_margin_bottom(0);
//	set_margin_top(0);
//	set_margin_start(0);
//	set_margin_end(0);
	set_border_width(0);
	v_ButtonGridContainer.set_border_width(0);
	v_ButtonGridContainer.set_hexpand(true);
	v_ButtonGridContainer.set_halign(Gtk::ALIGN_CENTER);
	v_ButtonProgressBar.set_hexpand(true);
	add(v_ButtonGridContainer);
	v_ButtonGridContainer.attach(v_ButtonLabel, 0, 0, 1, 1);
	v_ButtonGridContainer.attach(v_ButtonProgressBar, 0, 1, 1, 1);
} // END - Constructor

LauncherMainButton::~LauncherMainButton(){
	// Destructor
} // END - Destructor

void LauncherMainButton::SetButtonText(Glib::ustring p_Text){
	v_ButtonLabel.set_text(p_Text);
}