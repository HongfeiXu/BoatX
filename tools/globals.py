ENGINE_NAME = "boatx"
PROJECT_NAME = "boatxeditor"
TOOLS_DIR = "tools"

VERSION_MAJOR = 0
VERSION_MINOR = 1

import sys

PLATFORM = sys.platform

def IsWindows():
    return PLATFORM.startswith("win32")

def IsLinux():
    return PLATFORM.startswith("linux")

def IsMac():
    return PLATFORM.startswith("darwin")
