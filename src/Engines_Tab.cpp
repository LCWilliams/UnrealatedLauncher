#include <headers/Launcher_Engines.h>

using namespace UnrealatedLauncher;

UnrealatedLauncher::Launcher_EngineTab::Launcher_EngineTab(){
	// Configuration of container grid:
	set_row_homogeneous(false);
	set_column_homogeneous(false);
	set_hexpand();
	set_vexpand();


// ATTACHMENT: main window
	v_FlowboxScrolledWindowWrapper.add(v_EngineFlowBox);
	attach(v_FlowboxScrolledWindowWrapper, 0, 1, 1, 1);
	attach(v_EnginesToolbar, 0, 2, 2, 1);
	v_EnginesToolbar.set_hexpand();


// ATTACHMENT: Toolbar
	v_EnginesToolbar.pack_end(btn_EnginesTabOptions);
	v_EnginesToolbar.pack_end(btn_Filter);
	v_EnginesToolbar.pack_end(btn_EnginesSearchEntry);
	// Toolbar, left side:
	v_EnginesToolbar.pack_start(btn_AddEngine);
	
// ATTACHMENT: SidePanel
//	v_EngineTabSidePanel.set_size_request(200, -1);
	attach(v_EngineTabSidePanel, 1, 1, 1, 1);
	v_sidePanelGrid.attach(v_sidepanelSubGrid_Add, 0, 0, 1, 1);
	v_sidePanelGrid.attach(v_sidepanelSubGrid_Details, 0, 1, 1, 1);
	v_EngineTabSidePanel.set_name("EngineTabSidePanel");
	
	v_EngineTabSidePanel.set_transition_type(Gtk::REVEALER_TRANSITION_TYPE_SLIDE_RIGHT);
	v_EngineTabSidePanel.set_transition_duration(750);
	v_EngineTabSidePanel.set_reveal_child(false);

	v_EngineTabSidePanel.add(v_sidePanelGrid);
	
	Gtk::ScrolledWindow *v_sidePanelScrollWindow = Gtk::manage(new Gtk::ScrolledWindow);
	Gtk::Frame *v_addNewFrame = Gtk::manage(new Gtk::Frame("Add Engine:"));
	EngineAdd *v_AddEngine = Gtk::manage(new EngineAdd);
	ref_EngineAdd = v_AddEngine;
	v_AddEngine->v_tabReference = this;
	v_AddEngine->set_hexpand(false);
	
	v_sidePanelScrollWindow->add(*v_addNewFrame);
	v_sidePanelScrollWindow->set_min_content_width(380);
	v_sidePanelScrollWindow->set_min_content_height(300);
	v_sidePanelScrollWindow->set_hexpand(false);
	v_sidePanelScrollWindow->set_vexpand(true);
	
	v_addNewFrame->add(*v_AddEngine);
	v_addNewFrame->set_border_width(5);
	v_addNewFrame->set_size_request(360, -1);
	v_addNewFrame->set_vexpand(true);
	v_addNewFrame->set_hexpand(false);

//	v_sidepanelSubGrid_Add.attach(*v_addNewFrame, 0, 0, 1, 1);
	v_sidepanelSubGrid_Add.attach(*v_sidePanelScrollWindow, 0, 0, 1, 1);
	v_sidepanelSubGrid_Add.set_hexpand(false);
//	v_EngineTabSidePanel.show_all();
	


// FLOWBOX & SCROLL WINDOW: settings
	v_EngineFlowBox.set_margin_top(26);
	v_EngineFlowBox.set_margin_start(10);
	v_EngineFlowBox.set_homogeneous(false);
	v_EngineFlowBox.set_column_spacing(8);
	v_EngineFlowBox.set_row_spacing(15);
	v_EngineFlowBox.set_valign(Gtk::ALIGN_START);
	v_EngineFlowBox.set_halign(Gtk::ALIGN_START);
	v_EngineFlowBox.set_min_children_per_line(3);

		// DEBUG:
	v_FlowboxScrolledWindowWrapper.set_min_content_height(400);
	v_FlowboxScrolledWindowWrapper.set_min_content_width(1000);
//	v_FlowboxScrolledWindowWrapper.set_margin_end(10);
//	v_FlowboxScrolledWindowWrapper.set_margin_bottom(10);
	v_FlowboxScrolledWindowWrapper.set_hexpand();
	v_FlowboxScrolledWindowWrapper.set_vexpand();


	btn_AddEngine.add_label("ADD ENGINE", true, Gtk::ALIGN_CENTER);
	btn_AddEngine.signal_clicked().connect(sigc::mem_fun(*this, &Launcher_EngineTab::btn_AddEngine_clicked));
	auto *img_filterIcon = Gtk::manage(new Gtk::Image("../img/icons/filter.svg"));
	btn_Filter.set_image(*img_filterIcon);
	btn_Filter.set_always_show_image();

	// Add existing engines.
	AddExistingEngines();
	
	// Hide:
	v_sidepanelSubGrid_Add.hide();
	v_sidepanelSubGrid_Details.hide();
} // END - EngineTab Constructor.

UnrealatedLauncher::Launcher_EngineTab::~Launcher_EngineTab(){
} // END - Destructor.


void UnrealatedLauncher::Launcher_EngineTab::btn_AddEngine_clicked(){
	v_sidepanelSubGrid_Add.show();
	v_sidepanelSubGrid_Details.hide();
	v_EngineTabSidePanel.set_reveal_child(true);
	btn_AddEngine.set_sensitive(false);
	v_EngineFlowBox.set_sensitive(false);
	ref_EngineAdd->EngineAdd_reset();
}



void UnrealatedLauncher::Launcher_EngineTab::AddNewEngine(){
	
	// Create new engine block.
	EngineBlock *newBlock = Gtk::manage(new EngineBlock(
												ref_EngineAdd->installData.installDir,
												ref_EngineAdd->installData.customImage, 
												ref_EngineAdd->installData.engineLabel,
												ref_EngineAdd->installData.commitID, 
												ref_EngineAdd->installData.codeEditor ));

	// SET ENGINE TAB REFERENCE [Important!]
	newBlock->v_TabReference = (Launcher_EngineTab*)this;
	
	// Add to array.
	v_EngineBlockArray.push_back(newBlock);

	// Add to Flowbox.
	v_EngineFlowBox.add(*newBlock);

	// Run show all.
	v_EngineFlowBox.show_all();
	
	// Reset Add Panel.
	ref_EngineAdd->EngineAdd_reset();
	
	// Run Installation:
	if(ref_EngineAdd->EngineAdd_startInstallAfterFinished){
//		newBlock->EngineBlock_install();	// Run install.
		newBlock->InfoBarResponse(1); 		// Hide the info bar; and "continues" install.
	}

} // END - Add New Engine.



void UnrealatedLauncher::Launcher_EngineTab::AddExistingEngines(){
// CREATE ENGINEBLOCKS FOR EACH INI FOUND IN CONFIG:
	string configFolderString = "./config/engines";
	DIR *configFolder = opendir(configFolderString.c_str());
	struct dirent *next_file;
	char v_filePath[PATH_MAX];
	
	while ( (next_file = readdir(configFolder)) != NULL){
		if(strcmp(next_file->d_name, ".") && strcmp(next_file->d_name, "..")){
			sprintf(v_filePath, "%s/%s", configFolderString.c_str(), next_file->d_name);
			
			char resolvedPath[PATH_MAX];
			string temp_AbsolutePath = realpath(v_filePath, resolvedPath);
			
			std::string::size_type temp_stringType;
			temp_stringType = temp_AbsolutePath.rfind(".ini");
			
			if( temp_stringType != string::npos){
				EngineBlock *currentBlock = Gtk::manage(new EngineBlock(resolvedPath));
				v_EngineBlockArray.push_back(currentBlock);
			} else{
				cerr << "WARN:	Non .ini file found in engine folder: " << resolvedPath << endl;
			}
		} // END - If Filename
		// Set next file:
		sprintf(v_filePath, "%s/%s", configFolderString.c_str(), next_file->d_name);
	} // END - while loop
	
	for(int index = 0; index < static_cast<int>(v_EngineBlockArray.size()); index++ ){
		// Set references:
		v_EngineBlockArray[index]->v_TabReference = (Launcher_EngineTab*)this;
				
		// Add to flowbox:
		v_EngineFlowBox.insert(*v_EngineBlockArray[index], -1);
	} // END - For loop
	
	v_EngineFlowBox.show_all();
} // END - Add Existing.

void UnrealatedLauncher::Launcher_EngineTab::DeleteEngineBlock(EngineBlock* p_blockReference){
	string v_engineIniFile = "./config/engines/" +p_blockReference->v_EngineLabel + ".ini";
	
	// Remove .ini file.
	std::remove(v_engineIniFile.c_str());
		
	// Hide the block
	delete p_blockReference;
//	remove(p_blockReference);
//	p_blockReference->hide();
} // END - Delete Engine Block


void UnrealatedLauncher::Launcher_EngineTab::CloseAddWizard(){
	btn_AddEngine.set_sensitive(true);
	v_EngineTabSidePanel.set_reveal_child(false);
	v_EngineFlowBox.set_sensitive(true);
}

//void UnrealatedLauncher::Launcher_EngineTab::middleMan_openRepoManager(){
//	ref_mainWindow->repoManager_open();
//}