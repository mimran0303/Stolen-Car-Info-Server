##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=server
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/home/fatimaimran/OS2
ProjectPath            :=/home/fatimaimran/OS2/server
IntermediateDirectory  :=../build-$(ConfigurationName)/server
OutDir                 :=../build-$(ConfigurationName)/server
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=FatimaImran
Date                   :=30/03/23
CodeLitePath           :=/home/fatimaimran/.codelite
LinkerName             :=/usr/bin/g++-11
SharedObjectLinkerName :=/usr/bin/g++-11 -shared -fPIC
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
OutputFile             :=../build-$(ConfigurationName)/bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
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
CXX      := /usr/bin/g++-11
CC       := /usr/bin/gcc-11
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=../build-$(ConfigurationName)/server/server.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/server/.d $(Objects) 
	@mkdir -p "../build-$(ConfigurationName)/server"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@mkdir -p "../build-$(ConfigurationName)/server"
	@mkdir -p ""../build-$(ConfigurationName)/bin""

../build-$(ConfigurationName)/server/.d:
	@mkdir -p "../build-$(ConfigurationName)/server"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/server/server.cpp$(ObjectSuffix): server.cpp ../build-$(ConfigurationName)/server/server.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/fatimaimran/OS2/server/server.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/server/server.cpp$(DependSuffix): server.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/server/server.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/server/server.cpp$(DependSuffix) -MM server.cpp

../build-$(ConfigurationName)/server/server.cpp$(PreprocessSuffix): server.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/server/server.cpp$(PreprocessSuffix) server.cpp


-include ../build-$(ConfigurationName)/server//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


