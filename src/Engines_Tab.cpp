#include <headers/LauncherMainPages.h>
#include <headers/Engines_Block.h>

using namespace UnrealatedLauncher;

Launcher_EngineTab::Launcher_EngineTab(){
	// Configuration of container grid:
	set_row_homogeneous(false);
	set_column_homogeneous(false);
	set_hexpand();
	set_vexpand();

// ATTACHMENT: main window
	v_FlowboxScrolledWindowWrapper.add(v_EngineFlowBox);
	attach(v_FlowboxScrolledWindowWrapper, 0, 1, 1, 1);
	attach(v_EnginesToolbar, 0, 2, 1, 1);
	v_EnginesToolbar.set_hexpand();


// ATTACHMENT: Toolbar
	v_EnginesToolbar.pack_end(btn_EnginesTabOptions);
	v_EnginesToolbar.pack_end(btn_Filter);
	v_EnginesToolbar.pack_end(btn_EnginesSearchEntry);
	// Toolbar, left side:
	v_EnginesToolbar.pack_start(btn_AddEngine);

// FLOWBOX & SCROLL WINDOW: settings
	v_EngineFlowBox.set_column_spacing(10);
	v_EngineFlowBox.set_row_spacing(15);
	v_EngineFlowBox.set_valign(Gtk::ALIGN_START);
	v_EngineFlowBox.set_halign(Gtk::ALIGN_START);
	v_EngineFlowBox.set_min_children_per_line(3);
	
	v_FlowboxScrolledWindowWrapper.set_min_content_height(400);
	v_FlowboxScrolledWindowWrapper.set_min_content_width(1000);
	v_FlowboxScrolledWindowWrapper.set_margin_start(10);
	v_FlowboxScrolledWindowWrapper.set_margin_end(10);
	v_FlowboxScrolledWindowWrapper.set_hexpand();
	v_FlowboxScrolledWindowWrapper.set_vexpand();



// BUTTONS, LABELS & ICONS
	btn_AddEngine.add_label("ADD ENGINE", true, Gtk::ALIGN_CENTER);
	auto *filterIcon = Gtk::manage(new Gtk::Image("../img/icon/filter.svg"));
	btn_Filter.set_image(*filterIcon);
	btn_Filter.set_always_show_image();
	

// DEBUG TESTING:
	EngineBlock *testBlock = Gtk::manage(new EngineBlock("", "", "", "", 1, 0));
	EngineBlock *testBlock2 = Gtk::manage(new EngineBlock("/mnt/test", "/mnt/test/source", "", "MAH FANCY AWESOME VERSION", 17, 2));
	EngineBlock *testBlock3 = Gtk::manage(new EngineBlock("", "", "", "", 2, 3));
	EngineBlock *testBlock4 = Gtk::manage(new EngineBlock("", "", "", "", 5, 0));
	EngineBlock *testBlock5 = Gtk::manage(new EngineBlock("", "", "", "", 3, 0));
	EngineBlock *testBlock6 = Gtk::manage(new EngineBlock("", "", "", "GARBLE GARBLE GARBLE GARBLE GARBLE", 5, 0));
	EngineBlock *testBlock7 = Gtk::manage(new EngineBlock("", "", "", "VEEEEERY LOOOOOOONG NAAAAAAME TOOOO TEEEEEEESSSSSSTTTTT", 1, 0));
	EngineBlock *testBlock8 = Gtk::manage(new EngineBlock("", "", "", "", 1, 0));
	EngineBlock *testBlock9 = Gtk::manage(new EngineBlock("", "", "/home/lee/Pictures/test.jpg", "", 1, 2));
	EngineBlock *testBlock10 = Gtk::manage(new EngineBlock("", "", "/home/lee/Pictures/test.jpg", "Fancy Awesome Version with Image", 1, 3));
	EngineBlock *testBlock11 = Gtk::manage(new EngineBlock("", "", "/home/lee/Pictures/doesn'texist.jpeg", "Awesome version with broken image", 17, 0));
	EngineBlock *testBlock12 = Gtk::manage(new EngineBlock("", "", "/home/lee/Pictures/huehu.png", "", 1, 0));
	EngineBlock *testBlock13 = Gtk::manage(new EngineBlock("", "", "", "", 1, 0));
	v_EngineFlowBox.add(*testBlock);
	v_EngineFlowBox.add(*testBlock2);
	v_EngineFlowBox.add(*testBlock3);
	v_EngineFlowBox.add(*testBlock4);
	v_EngineFlowBox.add(*testBlock5);
	v_EngineFlowBox.add(*testBlock6);
	v_EngineFlowBox.add(*testBlock7);
	v_EngineFlowBox.add(*testBlock8);
	v_EngineFlowBox.add(*testBlock9);
	v_EngineFlowBox.add(*testBlock10);
	v_EngineFlowBox.add(*testBlock11);
	v_EngineFlowBox.add(*testBlock12);
	v_EngineFlowBox.add(*testBlock13);
// END DEBUG TESTING.
} // END - EngineTab Constructor.

Launcher_EngineTab::~Launcher_EngineTab(){
} // END - Destructor.

// FUNCTIONS:



// LEGACY CODE:
/*
EngineTabContainer::EngineTabContainer(){
// Configuration of EnginesTabContainer:
//	set_row_spacing(0);
	set_row_homogeneous(false);
	set_column_homogeneous(false);

// FLOW BOX: Create & Attach to grid
	Gtk::FlowBox *v_EngineBlockContainer = Gtk::manage(new Gtk::FlowBox);
	v_EngineBlockContainer->set_border_width(0);
	v_EngineBlockContainer->set_homogeneous();
	v_EngineBlockContainer->set_max_children_per_line(5);
	v_EngineBlockContainer->set_row_spacing(5);
	v_EngineBlockContainer->set_column_spacing(0);


// SCROLL WINDOW
	attach(v_EngineScrolledWindow, 0, 0, 1, 1);
//	v_EngineScrolledWindow.add(*v_EngineBlockGrid);
	// Configuration:
	v_EngineScrolledWindow.set_hexpand(true);
	v_EngineScrolledWindow.set_vexpand(true);
	v_EngineScrolledWindow.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	v_EngineScrolledWindow.add(*v_EngineBlockContainer);
	// Pack EngineBlockGrid into widnow:

// UTILITY BAR [Bottom]
	attach(v_EnginesToolbar, 0, 1, 1, 1);
	// Configuration:
	v_EnginesToolbar.set_hexpand(true);
		//  RIGHT SIDE
	v_EnginesToolbar.pack_end(btn_EnginesWindowOptions);
	v_EnginesToolbar.pack_end(btn_Filter);
	v_EnginesToolbar.pack_end(v_EnginesSearchEntry);
	
		// LEFT SIDE:
	v_EnginesToolbar.pack_start(btn_AddNew);
	
// NEED IMAGES!
//	btn_Filter.set_image();
//	btn_EnginesWindowOptions.set_image();
	btn_AddNew.set_label("Add");
	btn_Filter.set_label("Filter");
	btn_EnginesWindowOptions.set_label("Options");


// ENGINE POPULATION:
	// Function: Add Existing
	
	// Iterate blanks for testing:
	for(int index = 0; index < 10; index++ ){
		
		Gtk::FlowBoxChild *engineBoxFlowBox = Gtk::manage(new Gtk::FlowBoxChild);
		engineBoxFlowBox->set_vexpand(false);
		
		
		auto engineBlock = Gtk::manage(new EngineBlock);
		
		engineBoxFlowBox->add(*engineBlock);
		
		v_EngineBlockContainer->add(*engineBoxFlowBox);
	}
} // END - Constructor

EngineTabContainer::~EngineTabContainer(){
//null
} // END - Destructor


// FUNCTIONS:

void EngineTabContainer::launchEngine(){
	
} // END - Launch enigne.
*/