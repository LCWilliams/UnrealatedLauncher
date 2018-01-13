#include <headers/Engines_Tab.h>
#include <headers/Engines_Block.h>

using namespace UnrealatedLauncher;

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