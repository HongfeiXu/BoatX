ENGINE_NAME = "boatx"
PROJECT_NAME = "boatxeditor"

TOOLS_DIR = "tools"

VERSION_MAJOR = 0
VERSION_MINOR = 1


# ---------------------------------------------- #
# platform

import sys
PLATFORM = sys.platform

def is_windows():
    return PLATFORM.startswith("win32")

def is_linux():
    return PLATFORM.startswith("linux")

def is_mac():
    return PLATFORM.startswith("darwin")


# ---------------------------------------------- #
# arguments

def process_arguments(argv):
    """
    Example:
        Input: ['config=release']
        Output: {"config": "release"}
    """
    ret = {}
    for arg in argv:
        try:
            k = arg[0:arg.index("=")]
            v = arg[arg.index("=")+1:]
        except:
            k = arg
            v = 0
        ret[k] = v
    return ret

def get_argument_value(args, name, default):
    return args.get(name, default)
