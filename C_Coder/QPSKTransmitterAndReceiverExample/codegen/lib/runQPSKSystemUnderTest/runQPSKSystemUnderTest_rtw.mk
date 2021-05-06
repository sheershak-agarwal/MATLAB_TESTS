###########################################################################
## Makefile generated for component 'runQPSKSystemUnderTest'. 
## 
## Makefile     : runQPSKSystemUnderTest_rtw.mk
## Generated on : Tue Apr 27 13:23:11 2021
## Final product: ./runQPSKSystemUnderTest.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPILER_COMMAND_FILE   Compiler command listing model reference header paths
# CMD_FILE                Command file
# MODELLIB                Static library target

PRODUCT_NAME              = runQPSKSystemUnderTest
MAKEFILE                  = runQPSKSystemUnderTest_rtw.mk
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/R2021a
MATLAB_BIN                = C:/PROGRA~1/MATLAB/R2021a/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
START_DIR                 = C:/Users/SheershakAgarwal/Documents/MATLAB_COM/C_Coder/QPSKTransmitterAndReceiverExample/codegen/lib/runQPSKSystemUnderTest
TGT_FCN_LIB               = ISO_C++11
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = .
COMPILER_COMMAND_FILE     = runQPSKSystemUnderTest_rtw_comp.rsp
CMD_FILE                  = runQPSKSystemUnderTest_rtw.rsp
C_STANDARD_OPTS           = -fwrapv
CPP_STANDARD_OPTS         = -fwrapv
MODELLIB                  = runQPSKSystemUnderTest.lib

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          MinGW64 | gmake (64-bit Windows)
# Supported Version(s):    6.x
# ToolchainInfo Version:   2021a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# C_STANDARD_OPTS
# CPP_STANDARD_OPTS
# MINGW_ROOT
# MINGW_C_STANDARD_OPTS

#-----------
# MACROS
#-----------

WARN_FLAGS            = -Wall -W -Wwrite-strings -Winline -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Wcast-align
WARN_FLAGS_MAX        = $(WARN_FLAGS) -Wcast-qual -Wshadow
CPP_WARN_FLAGS        = -Wall -W -Wwrite-strings -Winline -Wpointer-arith -Wcast-align
CPP_WARN_FLAGS_MAX    = $(CPP_WARN_FLAGS) -Wcast-qual -Wshadow
MW_EXTERNLIB_DIR      = $(MATLAB_ROOT)/extern/lib/win64/mingw64
SHELL                 = %SystemRoot%/system32/cmd.exe

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = -lws2_32

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: GNU C Compiler
CC_PATH = $(MINGW_ROOT)
CC = "$(CC_PATH)/gcc"

# Linker: GNU Linker
LD_PATH = $(MINGW_ROOT)
LD = "$(LD_PATH)/g++"

# C++ Compiler: GNU C++ Compiler
CPP_PATH = $(MINGW_ROOT)
CPP = "$(CPP_PATH)/g++"

# C++ Linker: GNU C++ Linker
CPP_LD_PATH = $(MINGW_ROOT)
CPP_LD = "$(CPP_LD_PATH)/g++"

# Archiver: GNU Archiver
AR_PATH = $(MINGW_ROOT)
AR = "$(AR_PATH)/ar"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%/bin/win64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @del
ECHO                = @echo
MV                  = @move
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c $(MINGW_C_STANDARD_OPTS) -m64 \
                       -O3 -fno-loop-optimize -fno-aggressive-loop-optimizations
CPPFLAGS             = -c $(CPP_STANDARD_OPTS) -m64 \
                       -O3 -fno-loop-optimize -fno-aggressive-loop-optimizations
CPP_LDFLAGS          =  -static -m64
CPP_SHAREDLIB_LDFLAGS  = -shared -Wl,--no-undefined \
                         -Wl,--out-implib,$(basename $(PRODUCT)).lib
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              =  -static -m64
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared -Wl,--no-undefined \
                       -Wl,--out-implib,$(basename $(PRODUCT)).lib



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./runQPSKSystemUnderTest.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = 

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -D__USE_MINGW_ANSI_STDIO=1
DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=runQPSKSystemUnderTest

DEFINES = $(DEFINES_) $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/runQPSKSystemUnderTest_data.cpp $(START_DIR)/rt_nonfinite.cpp $(START_DIR)/rtGetNaN.cpp $(START_DIR)/rtGetInf.cpp $(START_DIR)/runQPSKSystemUnderTest_initialize.cpp $(START_DIR)/runQPSKSystemUnderTest_terminate.cpp $(START_DIR)/runQPSKSystemUnderTest.cpp $(START_DIR)/Scrambler.cpp $(START_DIR)/QPSKBitsGenerator.cpp $(START_DIR)/QPSKModulator.cpp $(START_DIR)/FIRInterpolator.cpp $(START_DIR)/RaisedCosineTransmitFilter.cpp $(START_DIR)/QPSKTransmitter.cpp $(START_DIR)/FIRDecimator.cpp $(START_DIR)/RaisedCosineReceiveFilter.cpp $(START_DIR)/CoarseFrequencyCompensator.cpp $(START_DIR)/PhaseFrequencyOffset.cpp $(START_DIR)/CarrierSynchronizer.cpp $(START_DIR)/SymbolSynchronizer.cpp $(START_DIR)/PreambleDetector.cpp $(START_DIR)/FrameSynchronizer.cpp $(START_DIR)/QPSKDemodulator.cpp $(START_DIR)/Descrambler.cpp $(START_DIR)/ErrorRate.cpp $(START_DIR)/QPSKDataDecoder.cpp $(START_DIR)/QPSKReceiver.cpp $(START_DIR)/runQPSKSystemUnderTest_rtwutil.cpp

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = runQPSKSystemUnderTest_data.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj runQPSKSystemUnderTest_initialize.obj runQPSKSystemUnderTest_terminate.obj runQPSKSystemUnderTest.obj Scrambler.obj QPSKBitsGenerator.obj QPSKModulator.obj FIRInterpolator.obj RaisedCosineTransmitFilter.obj QPSKTransmitter.obj FIRDecimator.obj RaisedCosineReceiveFilter.obj CoarseFrequencyCompensator.obj PhaseFrequencyOffset.obj CarrierSynchronizer.obj SymbolSynchronizer.obj PreambleDetector.obj FrameSynchronizer.obj QPSKDemodulator.obj Descrambler.obj ErrorRate.obj QPSKDataDecoder.obj QPSKReceiver.obj runQPSKSystemUnderTest_rtwutil.obj

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES) @$(COMPILER_COMMAND_FILE)

CFLAGS += $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES) @$(COMPILER_COMMAND_FILE)

CPPFLAGS += $(CPPFLAGS_BASIC)

#---------------------
# MEX C++ Compiler
#---------------------

MEX_CPP_Compiler_BASIC =  @$(COMPILER_COMMAND_FILE)

MEX_CPPFLAGS += $(MEX_CPP_Compiler_BASIC)

#-----------------
# MEX Compiler
#-----------------

MEX_Compiler_BASIC =  @$(COMPILER_COMMAND_FILE)

MEX_CFLAGS += $(MEX_Compiler_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################


MINGW_C_STANDARD_OPTS = $(C_STANDARD_OPTS)


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS)  $(PRODUCT) @$(CMD_FILE)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.obj : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.obj : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.obj : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.obj : C:/Users/SheershakAgarwal/Documents/MATLAB_COM/C_Coder/QPSKTransmitterAndReceiverExample/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.obj : C:/Users/SheershakAgarwal/Documents/MATLAB_COM/C_Coder/QPSKTransmitterAndReceiverExample/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


runQPSKSystemUnderTest_data.obj : $(START_DIR)/runQPSKSystemUnderTest_data.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rt_nonfinite.obj : $(START_DIR)/rt_nonfinite.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rtGetNaN.obj : $(START_DIR)/rtGetNaN.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rtGetInf.obj : $(START_DIR)/rtGetInf.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


runQPSKSystemUnderTest_initialize.obj : $(START_DIR)/runQPSKSystemUnderTest_initialize.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


runQPSKSystemUnderTest_terminate.obj : $(START_DIR)/runQPSKSystemUnderTest_terminate.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


runQPSKSystemUnderTest.obj : $(START_DIR)/runQPSKSystemUnderTest.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


Scrambler.obj : $(START_DIR)/Scrambler.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


QPSKBitsGenerator.obj : $(START_DIR)/QPSKBitsGenerator.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


QPSKModulator.obj : $(START_DIR)/QPSKModulator.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


FIRInterpolator.obj : $(START_DIR)/FIRInterpolator.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


RaisedCosineTransmitFilter.obj : $(START_DIR)/RaisedCosineTransmitFilter.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


QPSKTransmitter.obj : $(START_DIR)/QPSKTransmitter.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


FIRDecimator.obj : $(START_DIR)/FIRDecimator.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


RaisedCosineReceiveFilter.obj : $(START_DIR)/RaisedCosineReceiveFilter.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


CoarseFrequencyCompensator.obj : $(START_DIR)/CoarseFrequencyCompensator.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


PhaseFrequencyOffset.obj : $(START_DIR)/PhaseFrequencyOffset.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


CarrierSynchronizer.obj : $(START_DIR)/CarrierSynchronizer.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


SymbolSynchronizer.obj : $(START_DIR)/SymbolSynchronizer.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


PreambleDetector.obj : $(START_DIR)/PreambleDetector.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


FrameSynchronizer.obj : $(START_DIR)/FrameSynchronizer.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


QPSKDemodulator.obj : $(START_DIR)/QPSKDemodulator.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


Descrambler.obj : $(START_DIR)/Descrambler.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


ErrorRate.obj : $(START_DIR)/ErrorRate.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


QPSKDataDecoder.obj : $(START_DIR)/QPSKDataDecoder.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


QPSKReceiver.obj : $(START_DIR)/QPSKReceiver.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


runQPSKSystemUnderTest_rtwutil.obj : $(START_DIR)/runQPSKSystemUnderTest_rtwutil.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(COMPILER_COMMAND_FILE) $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(ECHO) "### Deleted all derived files."


