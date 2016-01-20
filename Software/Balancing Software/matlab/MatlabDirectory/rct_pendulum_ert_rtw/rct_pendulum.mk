###########################################################################
## Makefile generated for Simulink model 'rct_pendulum'. 
## 
## Makefile     : rct_pendulum.mk
## Generated on : Tue Jan 19 21:12:37 2016
## MATLAB Coder version: 2.8 (R2015a)
## 
## Build Info:
## 
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/rct_pendulum.elf
## Product type : executable
## Build type   : Top-Level Standalone Executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPUTER                Computer type. See the MATLAB "computer" command.

PRODUCT_NAME              = rct_pendulum
MAKEFILE                  = rct_pendulum.mk
COMPUTER                  = PCWIN64
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/MATLAB~1/R2015a
MATLAB_BIN                = C:/PROGRA~1/MATLAB/MATLAB~1/R2015a/bin
MATLAB_ARCH_BIN           = C:/PROGRA~1/MATLAB/MATLAB~1/R2015a/bin/win64
MASTER_ANCHOR_DIR         = 
START_DIR                 = C:/Users/Panoply/DOCUME~1/bot/Software/BALANC~1/matlab/MATLAB~1
ARCH                      = win64
SOLVER                    = 
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
TGT_FCN_LIB               = None
MODELREF_LINK_RSPFILE_NAME = rct_pendulum_ref.rsp
RELATIVE_PATH_TO_ANCHOR   = ..

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GNU Tools for ARM Embedded Processors v4.8 | gmake (64-bit Windows)
# Supported Version(s):    
# ToolchainInfo Version:   R2015a
# Specification Revision:  1.0
# 

-include codertarget_assembly_flags.mk
-include ../codertarget_assembly_flags.mk


#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# TARGET_LOAD_CMD_ARGS
# TARGET_LOAD_CMD

#-----------
# MACROS
#-----------

LIBGCC               = ${shell arm-none-eabi-gcc ${CFLAGS} -print-libgcc-file-name}
LIBC                 = ${shell arm-none-eabi-gcc ${CFLAGS} -print-file-name=libc.a}
LIBM                 = ${shell arm-none-eabi-gcc ${CFLAGS} -print-file-name=libm.a}
PRODUCT_BIN          = $(RELATIVE_PATH_TO_ANCHOR)/$(PRODUCT_NAME).bin
PRODUCT_HEX          = $(RELATIVE_PATH_TO_ANCHOR)/$(PRODUCT_NAME).hex
CPFLAGS              = -O binary
SHELL                = %SystemRoot%/system32/cmd.exe

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = -lm -lm

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# Assembler: GNU ARM Assembler
AS = arm-none-eabi-gcc

# C Compiler: GNU ARM C Compiler
CC = arm-none-eabi-gcc

# Linker: GNU ARM Linker
LD = arm-none-eabi-g++

# C++ Compiler: GNU ARM C++ Compiler
CPP = arm-none-eabi-g++

# C++ Linker: GNU ARM C++ Linker
CPP_LD = arm-none-eabi-g++

# Archiver: GNU ARM Archiver
AR = arm-none-eabi-ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_BIN)
MEX = $(MEX_PATH)/mex

# Binary Converter: Binary Converter
OBJCOPY = arm-none-eabi-objcopy

# Hex Converter: Hex Converter
OBJCOPY = arm-none-eabi-objcopy

# Executable Size: Executable Size
EXESIZE = arm-none-eabi-size

# Download: Download
DOWNLOAD = $(TARGET_LOAD_CMD)

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = $(MAKE_PATH)/gmake


#-------------------------
# Directives/Utilities
#-------------------------

ASDEBUG             = -g
AS_OUTPUT_FLAG      = -o
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
RM                  = @del /f/q
ECHO                = @echo
MV                  = @move
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              = ruvs
ASFLAGS              = -MD \
                       -Wall \
                       -x assembler-with-cpp \
                       $(ASFLAGS_ADDITIONAL) \
                       $(DEFINES) \
                       $(INCLUDES) \
                       -c
OBJCOPYFLAGS_BIN     = -O binary $(PRODUCT) $(PRODUCT_BIN)
CFLAGS               = -std=c99 \
                       -MD \
                       -ffunction-sections \
                       -fdata-sections \
                       -Wall \
                       -c \
                       -O0
CPPFLAGS             = -std=c++98 \
                       -fno-rtti \
                       -fno-exceptions \
                       -MD \
                       -ffunction-sections \
                       -fdata-sections \
                       -Wall \
                       -c \
                       -O0
CPP_LDFLAGS          = -Wl,--gc-sections \
                       -Wl,-Map="$(PRODUCT_NAME).map"
CPP_SHAREDLIB_LDFLAGS  =
DOWNLOAD_FLAGS       = $(TARGET_LOAD_CMD_ARGS) $(PRODUCT_HEX)
EXESIZE_FLAGS        = $(PRODUCT)
EXECUTE_FLAGS        =
OBJCOPYFLAGS_HEX     = -O ihex $(PRODUCT) $(PRODUCT_HEX)
LDFLAGS              = -Wl,--gc-sections \
                       -Wl,-Map="$(PRODUCT_NAME).map"
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    =

#--------------------
# File extensions
#--------------------

ASM_Type1_Ext       = .S
OBJ_EXT             = .o
ASM_EXT             = .s
H_EXT               = .h
OBJ_EXT             = .o
C_EXT               = .c
EXE_EXT             = .elf
SHAREDLIB_EXT       = .so
CXX_EXT             = .cxx
HPP_EXT             = .hpp
OBJ_EXT             = .o
CPP_EXT             = .cpp
UNIX_TYPE1_EXT      = .cc
UNIX_TYPE2_EXT      = .C
EXE_EXT             = .elf
SHAREDLIB_EXT       = .so
STATICLIB_EXT       = .lib
MEX_EXT             = .mexw64
MAKE_EXT            = .mk


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/rct_pendulum.elf
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Top-Level Standalone Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR)/rct_pendulum_ert_rtw -I$(START_DIR) -IC:/Users/Panoply/DOCUME~1/bot/Software/BALANC~1/matlab -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/rtw/c/ert -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/serial -IC:/MATLAB/SupportPackages/R2015a/armcortexm/toolbox/target/supportpackages/arm_cortex_m/scheduler/include -IC:/MATLAB/SupportPackages/R2015a/STM32F4-Discovery_FW_V1.1.0/Libraries/CMSIS/ST/STM32F4xx/Include -I$(CMSIS)/CMSIS/Include -IC:/MATLAB/SupportPackages/R2015a/STM32F4-Discovery_FW_V1.1.0/Project/Peripheral_Examples/SysTick -IC:/MATLAB/SupportPackages/R2015a/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc -IC:/MATLAB/SupportPackages/R2015a/stmicroelectronicsstm32f4discovery/toolbox/target/supportpackages/stm32f4discovery/@slCustomizer/../include -IC:/MATLAB/SupportPackages/R2015a/armcortexm/toolbox/target/supportpackages/arm_cortex_m/cmsis_rtos_rtx/include -I$(CMSIS)/CMSIS_RTX/INC -I$(CMSIS)/CMSIS_RTX/SRC

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -DMODEL=rct_pendulum -DNUMST=2 -DNCSTATES=2 -DHAVESTDIO -DONESTEPFCN=1 -DTERMFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DTID01EQ=1 -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__ -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY -DSTM32F4XX -DARM_MATH_CM4=1 -D__FPU_PRESENT=1 -D__FPU_USED=1 -DHSE_VALUE=8000000 -DNULL=0   -D__START=_start -DEXIT_FAILURE=1 -DEXTMODE_DISABLEPRINTF -DEXTMODE_DISABLETESTING -DEXTMODE_DISABLE_ARGS_PROCESSING=1 -DOS_ROBIN=0 -DOS_TIMERS=1 -DOS_TIMERPRIO=6 -DOS_TIMERSTKSZ=200 -DRT -DSTACK_SIZE=64
DEFINES_BUILD_ARGS = -DONESTEPFCN=1 -DTERMFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0
DEFINES_OPTS = -DTID01EQ=1
DEFINES_SKIPFORSIL = -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY -DSTM32F4XX -DARM_MATH_CM4=1 -D__FPU_PRESENT=1 -D__FPU_USED=1 -DHSE_VALUE=8000000 -DNULL=0   -D__START=_start -DEXIT_FAILURE=1 -DEXTMODE_DISABLEPRINTF -DEXTMODE_DISABLETESTING -DEXTMODE_DISABLE_ARGS_PROCESSING=1 -DOS_ROBIN=0 -DOS_TIMERS=1 -DOS_TIMERPRIO=6 -DOS_TIMERSTKSZ=200 -DRT -DSTACK_SIZE=64
DEFINES_STANDARD = -DMODEL=rct_pendulum -DNUMST=2 -DNCSTATES=2 -DHAVESTDIO

DEFINES = $(DEFINES_) $(DEFINES_BUILD_ARGS) $(DEFINES_OPTS) $(DEFINES_SKIPFORSIL) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/rct_pendulum_ert_rtw/ert_main.c $(START_DIR)/rct_pendulum_ert_rtw/rct_pendulum.c C:/MATLAB/SupportPackages/R2015a/stmicroelectronicsstm32f4discovery/toolbox/target/supportpackages/stm32f4discovery/@slCustomizer/../src/startup_stm32f4xx.c C:/MATLAB/SupportPackages/R2015a/stmicroelectronicsstm32f4discovery/toolbox/target/supportpackages/stm32f4discovery/@slCustomizer/../src/syscalls_stm32f4xx.c C:/MATLAB/SupportPackages/R2015a/stmicroelectronicsstm32f4discovery/toolbox/target/supportpackages/stm32f4discovery/@slCustomizer/../src/stm32f4xx_init_board.c C:/MATLAB/SupportPackages/R2015a/stmicroelectronicsstm32f4discovery/toolbox/target/supportpackages/stm32f4discovery/@slCustomizer/../src/system_stm32f4xx.c C:/MATLAB/SupportPackages/R2015a/armcortexm/toolbox/target/supportpackages/arm_cortex_m/scheduler/src/SysTickScheduler.c SkipForSil/arm_cortex_m_multitasking.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = rct_pendulum.o startup_stm32f4xx.o syscalls_stm32f4xx.o stm32f4xx_init_board.o system_stm32f4xx.o SysTickScheduler.o arm_cortex_m_multitasking.o

MAIN_OBJ = ert_main.o

ALL_OBJS = $(OBJS) $(MAIN_OBJ)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = $(CMSIS)/CMSIS/Lib/GCC/libarm_cortexM4lf_math.a $(CMSIS)/CMSIS_RTX/LIB/GCC/libRTX_CM4.a

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

CFLAGS_SKIPFORSIL = -mcpu=cortex-m4 -mthumb -mlittle-endian -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=hard -fsingle-precision-constant -include stm32f4xx.h
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_SKIPFORSIL) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_SKIPFORSIL = -mcpu=cortex-m4 -mthumb -mlittle-endian -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=hard -fsingle-precision-constant -include stm32f4xx.h
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_SKIPFORSIL) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_SKIPFORSIL = -mcpu=cortex-m4 -mthumb -mlittle-endian -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=hard --specs=nano.specs -T "C:\MATLAB\SupportPackages\R2015a\stmicroelectronicsstm32f4discovery\toolbox\target\supportpackages\stm32f4discovery\@slCustomizer\../src/arm-gcc-link.ld"

CPP_LDFLAGS += $(CPP_LDFLAGS_SKIPFORSIL)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_SKIPFORSIL = -mcpu=cortex-m4 -mthumb -mlittle-endian -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=hard --specs=nano.specs -T "C:\MATLAB\SupportPackages\R2015a\stmicroelectronicsstm32f4discovery\toolbox\target\supportpackages\stm32f4discovery\@slCustomizer\../src/arm-gcc-link.ld"

CPP_SHAREDLIB_LDFLAGS += $(CPP_SHAREDLIB_LDFLAGS_SKIPFORSIL)

#-----------
# Linker
#-----------

LDFLAGS_SKIPFORSIL = -mcpu=cortex-m4 -mthumb -mlittle-endian -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=hard --specs=nano.specs -T "C:\MATLAB\SupportPackages\R2015a\stmicroelectronicsstm32f4discovery\toolbox\target\supportpackages\stm32f4discovery\@slCustomizer\../src/arm-gcc-link.ld"

LDFLAGS += $(LDFLAGS_SKIPFORSIL)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_SKIPFORSIL = -mcpu=cortex-m4 -mthumb -mlittle-endian -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=hard --specs=nano.specs -T "C:\MATLAB\SupportPackages\R2015a\stmicroelectronicsstm32f4discovery\toolbox\target\supportpackages\stm32f4discovery\@slCustomizer\../src/arm-gcc-link.ld"

SHAREDLIB_LDFLAGS += $(SHAREDLIB_LDFLAGS_SKIPFORSIL)

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild postbuild download execute


all : build postbuild
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS) $(LIBS)
	@echo "### Successfully generated all binary outputs."


prebuild : 


postbuild : build
	@echo "### Invoking postbuild tool "Binary Converter" ..."
	$(OBJCOPY) $(OBJCOPYFLAGS_BIN)
	@echo "### Done invoking postbuild tool."
	@echo "### Invoking postbuild tool "Hex Converter" ..."
	$(OBJCOPY) $(OBJCOPYFLAGS_HEX)
	@echo "### Done invoking postbuild tool."
	@echo "### Invoking postbuild tool "Executable Size" ..."
	$(EXESIZE) $(EXESIZE_FLAGS)
	@echo "### Done invoking postbuild tool."


download : postbuild
	@echo "### Invoking postbuild tool "Download" ..."
	$(DOWNLOAD) $(DOWNLOAD_FLAGS)
	@echo "### Done invoking postbuild tool."


execute : download
	@echo "### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	@echo "### Done invoking postbuild tool."


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS) $(LIBS) $(MAIN_OBJ)
	@echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(LD) $(LDFLAGS) -o $(PRODUCT) $(OBJS) $(MAIN_OBJ) $(LIBS) $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/rct_pendulum_ert_rtw/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/rct_pendulum_ert_rtw/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/rct_pendulum_ert_rtw/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/rct_pendulum_ert_rtw/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/rct_pendulum_ert_rtw/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/rct_pendulum_ert_rtw/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/rct_pendulum_ert_rtw/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : C:/MATLAB/SupportPackages/R2015a/armcortexm/toolbox/target/supportpackages/arm_cortex_m/scheduler/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : C:/MATLAB/SupportPackages/R2015a/armcortexm/toolbox/target/supportpackages/arm_cortex_m/scheduler/src/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : C:/MATLAB/SupportPackages/R2015a/armcortexm/toolbox/target/supportpackages/arm_cortex_m/scheduler/src/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : C:/MATLAB/SupportPackages/R2015a/armcortexm/toolbox/target/supportpackages/arm_cortex_m/scheduler/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : C:/MATLAB/SupportPackages/R2015a/armcortexm/toolbox/target/supportpackages/arm_cortex_m/scheduler/src/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : C:/MATLAB/SupportPackages/R2015a/armcortexm/toolbox/target/supportpackages/arm_cortex_m/scheduler/src/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : C:/MATLAB/SupportPackages/R2015a/armcortexm/toolbox/target/supportpackages/arm_cortex_m/scheduler/src/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : C:/MATLAB/SupportPackages/R2015a/stmicroelectronicsstm32f4discovery/toolbox/target/supportpackages/stm32f4discovery/@slCustomizer/../src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : C:/MATLAB/SupportPackages/R2015a/stmicroelectronicsstm32f4discovery/toolbox/target/supportpackages/stm32f4discovery/@slCustomizer/../src/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : C:/MATLAB/SupportPackages/R2015a/stmicroelectronicsstm32f4discovery/toolbox/target/supportpackages/stm32f4discovery/@slCustomizer/../src/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : C:/MATLAB/SupportPackages/R2015a/stmicroelectronicsstm32f4discovery/toolbox/target/supportpackages/stm32f4discovery/@slCustomizer/../src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : C:/MATLAB/SupportPackages/R2015a/stmicroelectronicsstm32f4discovery/toolbox/target/supportpackages/stm32f4discovery/@slCustomizer/../src/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : C:/MATLAB/SupportPackages/R2015a/stmicroelectronicsstm32f4discovery/toolbox/target/supportpackages/stm32f4discovery/@slCustomizer/../src/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : C:/MATLAB/SupportPackages/R2015a/stmicroelectronicsstm32f4discovery/toolbox/target/supportpackages/stm32f4discovery/@slCustomizer/../src/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : SkipForSil/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : SkipForSil/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : SkipForSil/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : SkipForSil/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : SkipForSil/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : SkipForSil/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : SkipForSil/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : $(MAKEFILE) rtw_proj.tmw


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
	@echo "### ASFLAGS = $(ASFLAGS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### OBJCOPYFLAGS_BIN = $(OBJCOPYFLAGS_BIN)"
	@echo "### EXESIZE_FLAGS = $(EXESIZE_FLAGS)"
	@echo "### OBJCOPYFLAGS_HEX = $(OBJCOPYFLAGS_HEX)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(RM) *Object
	$(ECHO) "### Deleted all derived files."


