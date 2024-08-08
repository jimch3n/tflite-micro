TARGET_OS?=Win32
TARGET_PF?=MSC

ifneq ($(TARGET_OS), Win32)
	ifneq ($(TARGET_OS), Linux)
$(error Unsupported Operating System)
	endif
endif

ifneq ($(TARGET_PF), MSC)
	ifneq ($(TARGET_PF), Xtensa)
		ifneq ($(TARGET_PF), GCC)
$(error Unsupported Platform or Core)
		endif
	endif
endif

ifeq ($(TARGET_OS), Linux)
	ifeq ($(TARGET_PF), MSC)
$(error Unsupported Build in Visual Studio for Linux)
	endif
endif

ifeq ($(TARGET_OS), Win32)
	ifeq ($(TARGET_PF), GCC)
$(error Unsupported Build in GCC for Win32)
	endif
endif

