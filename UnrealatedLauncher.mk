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
User                   :=Lee Williams
Date                   :=13/12/17
CodeLitePath           :=/home/lee/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
LinkOptions            :=  $(shell pkg-config --libs gtkmm-3.0)
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)headers/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -Wall -O0 $(shell pkg-config --cflags gtkmm-3.0) $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_LauncherSettings.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_LauncherMainButtons.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Project_Tab.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(ObjectSuffix): src/UnrealatedLauncher.cpp $(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/UnrealatedLauncher.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(DependSuffix): src/UnrealatedLauncher.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(DependSuffix) -MM src/UnrealatedLauncher.cpp

$(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(PreprocessSuffix): src/UnrealatedLauncher.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_UnrealatedLauncher.cpp$(PreprocessSuffix) src/UnrealatedLauncher.cpp

$(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(ObjectSuffix): src/UnrealatedLauncherWindow.cpp $(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/UnrealatedLauncherWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(DependSuffix): src/UnrealatedLauncherWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(DependSuffix) -MM src/UnrealatedLauncherWindow.cpp

$(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(PreprocessSuffix): src/UnrealatedLauncherWindow.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_UnrealatedLauncherWindow.cpp$(PreprocessSuffix) src/UnrealatedLauncherWindow.cpp

$(IntermediateDirectory)/src_LauncherSettings.cpp$(ObjectSuffix): src/LauncherSettings.cpp $(IntermediateDirectory)/src_LauncherSettings.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/LauncherSettings.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_LauncherSettings.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_LauncherSettings.cpp$(DependSuffix): src/LauncherSettings.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_LauncherSettings.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_LauncherSettings.cpp$(DependSuffix) -MM src/LauncherSettings.cpp

$(IntermediateDirectory)/src_LauncherSettings.cpp$(PreprocessSuffix): src/LauncherSettings.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_LauncherSettings.cpp$(PreprocessSuffix) src/LauncherSettings.cpp

$(IntermediateDirectory)/src_LauncherMainButtons.cpp$(ObjectSuffix): src/LauncherMainButtons.cpp $(IntermediateDirectory)/src_LauncherMainButtons.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/LauncherMainButtons.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_LauncherMainButtons.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_LauncherMainButtons.cpp$(DependSuffix): src/LauncherMainButtons.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_LauncherMainButtons.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_LauncherMainButtons.cpp$(DependSuffix) -MM src/LauncherMainButtons.cpp

$(IntermediateDirectory)/src_LauncherMainButtons.cpp$(PreprocessSuffix): src/LauncherMainButtons.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_LauncherMainButtons.cpp$(PreprocessSuffix) src/LauncherMainButtons.cpp

$(IntermediateDirectory)/src_Project_Tab.cpp$(ObjectSuffix): src/Project_Tab.cpp $(IntermediateDirectory)/src_Project_Tab.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/1TB/Projects/UnrealatedLauncher/src/Project_Tab.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Project_Tab.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Project_Tab.cpp$(DependSuffix): src/Project_Tab.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Project_Tab.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Project_Tab.cpp$(DependSuffix) -MM src/Project_Tab.cpp

$(IntermediateDirectory)/src_Project_Tab.cpp$(PreprocessSuffix): src/Project_Tab.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Project_Tab.cpp$(PreprocessSuffix) src/Project_Tab.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/

