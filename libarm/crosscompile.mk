#
# Common for every unix flavour (any changes will be reflected on all platforms)
#

SYSROOT := /home/user/Qt/6.8.0/Boot2Qt/raspberrypi-armv8/toolchain/sysroots/cortexa53-poky-linux

TargetCPU  :=arm_v7
OS         :=linux
CXXFLAGS   := -O3 -g -fPIC -pedantic --sysroot=$(SYSROOT) -I$(SYSROOT)/usr/include

##
## Common variables (CXXFLAGS varies across platforms)
##
AR       := ar rcus
CXX      := /home/user/Qt/6.8.0/Boot2Qt/raspberrypi-armv8/toolchain/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++
CC       := /home/user/Qt/6.8.0/Boot2Qt/raspberrypi-armv8/toolchain/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-gcc
CFLAGS   :=


Platform               :=$(TargetCPU)-$(OS)
ConfigurationName      :=Release
IntermediateDirectory  :=../temp/$(TargetCPU)
OutDir                 := $(IntermediateDirectory)
LinkerName             :=g++
SharedObjectLinkerName :=$(CXX) -shared -fPIC
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../bin/$(Platform)/libsnap7.so
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="filelist.txt"
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -O3 --sysroot=$(SYSROOT)
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../../src/sys $(IncludeSwitch)../../src/core $(IncludeSwitch)../../src/lib 
Libs                   := $(LibrarySwitch)pthread $(LibrarySwitch)rt 
LibPath                := -L$(SYSROOT)/usr/lib -L$(SYSROOT)/usr/lib/aarch64-poky-linux/13.3.0 #-L.
LibInstall             := /usr/lib




##
## User defined environment variables
##
Objects0=$(IntermediateDirectory)/sys_snap_msgsock.o $(IntermediateDirectory)/sys_snap_sysutils.o $(IntermediateDirectory)/sys_snap_tcpsrvr.o $(IntermediateDirectory)/sys_snap_threads.o $(IntermediateDirectory)/core_s7_client.o $(IntermediateDirectory)/core_s7_isotcp.o $(IntermediateDirectory)/core_s7_partner.o $(IntermediateDirectory)/core_s7_peer.o $(IntermediateDirectory)/core_s7_server.o $(IntermediateDirectory)/core_s7_text.o \
	$(IntermediateDirectory)/core_s7_micro_client.o $(IntermediateDirectory)/lib_snap7_libmain.o 

Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean install PreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@$(MakeDirCommand) $(IntermediateDirectory)
	@echo $(Objects0)  > $(ObjectsFileList)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)
	$(RM) $(ObjectsFileList)

$(IntermediateDirectory)/.d:
	@test -d ../temp/$(TargetCPU) || $(MakeDirCommand) ../temp/$(TargetCPU)

PreBuild:

PostBuild:

##
## Objects
##
$(IntermediateDirectory)/sys_snap_msgsock.o: 
	$(CXX) $(SourceSwitch) "../../src/sys/snap_msgsock.cpp" $(CXXFLAGS) -o $(IntermediateDirectory)/sys_snap_msgsock.o $(IncludePath)

$(IntermediateDirectory)/sys_snap_sysutils.o:
	$(CXX) $(SourceSwitch) "../../src/sys/snap_sysutils.cpp" $(CXXFLAGS) -o $(IntermediateDirectory)/sys_snap_sysutils.o $(IncludePath)

$(IntermediateDirectory)/sys_snap_tcpsrvr.o:
	$(CXX) $(SourceSwitch) "../../src/sys/snap_tcpsrvr.cpp" $(CXXFLAGS) -o $(IntermediateDirectory)/sys_snap_tcpsrvr.o $(IncludePath)

$(IntermediateDirectory)/sys_snap_threads.o:
	$(CXX) $(SourceSwitch) "../../src/sys/snap_threads.cpp" $(CXXFLAGS) -o $(IntermediateDirectory)/sys_snap_threads.o $(IncludePath)

$(IntermediateDirectory)/core_s7_client.o:
	$(CXX) $(SourceSwitch) "../../src/core/s7_client.cpp" $(CXXFLAGS) -o $(IntermediateDirectory)/core_s7_client.o $(IncludePath)

$(IntermediateDirectory)/core_s7_isotcp.o:
	$(CXX) $(SourceSwitch) "../../src/core/s7_isotcp.cpp" $(CXXFLAGS) -o $(IntermediateDirectory)/core_s7_isotcp.o $(IncludePath)

$(IntermediateDirectory)/core_s7_partner.o:
	$(CXX) $(SourceSwitch) "../../src/core/s7_partner.cpp" $(CXXFLAGS) -o $(IntermediateDirectory)/core_s7_partner.o $(IncludePath)

$(IntermediateDirectory)/core_s7_peer.o:
	$(CXX) $(SourceSwitch) "../../src/core/s7_peer.cpp" $(CXXFLAGS) -o $(IntermediateDirectory)/core_s7_peer.o $(IncludePath)

$(IntermediateDirectory)/core_s7_server.o:
	$(CXX) $(SourceSwitch) "../../src/core/s7_server.cpp" $(CXXFLAGS) -o $(IntermediateDirectory)/core_s7_server.o $(IncludePath)

$(IntermediateDirectory)/core_s7_text.o:
	$(CXX) $(SourceSwitch) "../../src/core/s7_text.cpp" $(CXXFLAGS) -o $(IntermediateDirectory)/core_s7_text.o $(IncludePath)

$(IntermediateDirectory)/core_s7_micro_client.o:
	$(CXX) $(SourceSwitch) "../../src/core/s7_micro_client.cpp" $(CXXFLAGS) -o $(IntermediateDirectory)/core_s7_micro_client.o $(IncludePath)

$(IntermediateDirectory)/lib_snap7_libmain.o:
	$(CXX) $(SourceSwitch) "../../src/lib/snap7_libmain.cpp" $(CXXFLAGS) -o $(IntermediateDirectory)/lib_snap7_libmain.o $(IncludePath)

##
## Clean / Install
##
clean:
	$(RM) $(IntermediateDirectory)/*.o
	$(RM) $(OutputFile)

install: all
	cp -f $(OutputFile) $(LibInstall)

