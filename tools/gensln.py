import subprocess
import globals
import sys


def gen_on_windows():
    return subprocess.call(["cmd.exe", "/c", "premake\\premake5", "vs2022"])

def gen_on_linux():
    raise NotImplementedError

def gen_on_mac():
    raise NotImplementedError


if __name__ == "__main__":
    ret = 0
    if globals.is_windows():
        ret = gen_on_windows()
    elif globals.is_linux():
        ret = gen_on_linux()
    elif globals.is_mac():
        ret = gen_on_mac()
    else:
        raise NotImplementedError
    sys.exit(ret)
