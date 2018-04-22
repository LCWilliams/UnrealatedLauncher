##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=UnrealatedLauncher
ConfigurationName      :=Debug
WorkspacePath          :=/mnt/1TB/Projects/UnrealatedLauncher
ProjectPath            :=/mnt/1TB/Projects/UnrealatedLauncher
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=lee
Date                   :=22/04/18
CodeLitePath           :=/home/lee/.codelite
LinkerName             :=/usr/bin/gcc-7.3/bin/g++
SharedObjectLinkerName :=/usr/bin/gcc-7.3/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="UnrealatedLauncher.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            := -pthread -lstdc++  $(shell pkg-config --libs gtkmm-3.0) 
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)headers/external $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)git2 $(LibrarySwitch)ssl 
ArLibs                 :=  "libgit2" "libssl" 
LibPath                := $(LibraryPathSwitch)/libraries $(LibraryPathSwitch)/lib/x86_64-linux-gnu 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/gcc-7.3/bin/g++
CC       := /usr/bin/gcc-7.3/bin/gcc
CXXFLAGS := -std=c++17 -g -O0 -Wall $(shell pkg-config --cflags gtkmm-3.0)  $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_Engines_Block.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Engines_Tab.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_UnrealatedLauncherSettings.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Project_Tab.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Engines_SidebarAdd.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Community_Tab.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_AccountManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Market_Tab.cpp$(ObjectSuffix) \
	



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_Engines_Block.cpp$(ObjectSuffix): src/Engines_Block.cpp $(IntermediateDirectory)/src_Engines_Block.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/Engines_Block.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Engines_Block.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Engines_Block.cpp$(DependSuffix): src/Engines_Block.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Engines_Block.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Engines_Block.cpp$(DependSuffix) -MM src/Engines_Block.cpp

$(IntermediateDirectory)/src_Engines_Block.cpp$(PreprocessSuffix): src/Engines_Block.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Engines_Block.cpp$(PreprocessSuffix) src/Engines_Block.cpp

$(IntermediateDirectory)/src_Engines_Tab.cpp$(ObjectSuffix): src/Engines_Tab.cpp $(IntermediateDirectory)/src_Engines_Tab.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/Engines_Tab.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Engines_Tab.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Engines_Tab.cpp$(DependSuffix): src/Engines_Tab.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Engines_Tab.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Engines_Tab.cpp$(DependSuffix) -MM src/Engines_Tab.cpp

$(IntermediateDirectory)/src_Engines_Tab.cpp$(PreprocessSuffix): src/Engines_Tab.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Engines_Tab.cpp$(PreprocessSuffix) src/Engines_Tab.cpp

$(IntermediateDirectory)/src_UnrealatedLauncherSettings.cpp$(ObjectSuffix): src/UnrealatedLauncherSettings.cpp $(IntermediateDirectory)/src_UnrealatedLauncherSettings.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/UnrealatedLauncherSettings.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_UnrealatedLauncherSettings.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_UnrealatedLauncherSettings.cpp$(DependSuffix): src/UnrealatedLauncherSettings.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_UnrealatedLauncherSettings.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_UnrealatedLauncherSettings.cpp$(DependSuffix) -MM src/UnrealatedLauncherSettings.cpp

$(IntermediateDirectory)/src_UnrealatedLauncherSettings.cpp$(PreprocessSuffix): src/UnrealatedLauncherSettings.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_UnrealatedLauncherSettings.cpp$(PreprocessSuffix) src/UnrealatedLauncherSettings.cpp

$(IntermediateDirectory)/src_Project_Tab.cpp$(ObjectSuffix): src/Project_Tab.cpp $(IntermediateDirectory)/src_Project_Tab.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/Project_Tab.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Project_Tab.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Project_Tab.cpp$(DependSuffix): src/Project_Tab.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Project_Tab.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Project_Tab.cpp$(DependSuffix) -MM src/Project_Tab.cpp

$(IntermediateDirectory)/src_Project_Tab.cpp$(PreprocessSuffix): src/Project_Tab.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Project_Tab.cpp$(PreprocessSuffix) src/Project_Tab.cpp

$(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(ObjectSuffix): src/UnrealatedLauncher.cpp $(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/UnrealatedLauncher.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(DependSuffix): src/UnrealatedLauncher.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(DependSuffix) -MM src/UnrealatedLauncher.cpp

$(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(PreprocessSuffix): src/UnrealatedLauncher.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(PreprocessSuffix) src/UnrealatedLauncher.cpp

$(IntermediateDirectory)/src_Engines_SidebarAdd.cpp$(ObjectSuffix): src/Engines_SidebarAdd.cpp $(IntermediateDirectory)/src_Engines_SidebarAdd.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/Engines_SidebarAdd.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Engines_SidebarAdd.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Engines_SidebarAdd.cpp$(DependSuffix): src/Engines_SidebarAdd.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Engines_SidebarAdd.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Engines_SidebarAdd.cpp$(DependSuffix) -MM src/Engines_SidebarAdd.cpp

$(IntermediateDirectory)/src_Engines_SidebarAdd.cpp$(PreprocessSuffix): src/Engines_SidebarAdd.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Engines_SidebarAdd.cpp$(PreprocessSuffix) src/Engines_SidebarAdd.cpp

$(IntermediateDirectory)/src_Community_Tab.cpp$(ObjectSuffix): src/Community_Tab.cpp $(IntermediateDirectory)/src_Community_Tab.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/Community_Tab.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Community_Tab.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Community_Tab.cpp$(DependSuffix): src/Community_Tab.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Community_Tab.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Community_Tab.cpp$(DependSuffix) -MM src/Community_Tab.cpp

$(IntermediateDirectory)/src_Community_Tab.cpp$(PreprocessSuffix): src/Community_Tab.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Community_Tab.cpp$(PreprocessSuffix) src/Community_Tab.cpp

$(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(ObjectSuffix): src/UnrealatedLauncherWindow.cpp $(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/UnrealatedLauncherWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(DependSuffix): src/UnrealatedLauncherWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(DependSuffix) -MM src/UnrealatedLauncherWindow.cpp

$(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(PreprocessSuffix): src/UnrealatedLauncherWindow.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(PreprocessSuffix) src/UnrealatedLauncherWindow.cpp

$(IntermediateDirectory)/src_AccountManager.cpp$(ObjectSuffix): src/AccountManager.cpp $(IntermediateDirectory)/src_AccountManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/AccountManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_AccountManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_AccountManager.cpp$(DependSuffix): src/AccountManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_AccountManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_AccountManager.cpp$(DependSuffix) -MM src/AccountManager.cpp

$(IntermediateDirectory)/src_AccountManager.cpp$(PreprocessSuffix): src/AccountManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_AccountManager.cpp$(PreprocessSuffix) src/AccountManager.cpp

$(IntermediateDirectory)/src_Market_Tab.cpp$(ObjectSuffix): src/Market_Tab.cpp $(IntermediateDirectory)/src_Market_Tab.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/Market_Tab.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Market_Tab.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Market_Tab.cpp$(DependSuffix): src/Market_Tab.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Market_Tab.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Market_Tab.cpp$(DependSuffix) -MM src/Market_Tab.cpp

$(IntermediateDirectory)/src_Market_Tab.cpp$(PreprocessSuffix): src/Market_Tab.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Market_Tab.cpp$(PreprocessSuffix) src/Market_Tab.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


