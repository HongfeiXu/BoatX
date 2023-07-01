import subprocess
import globals


def build_on_windows():
    subprocess.call(["cmd.exe", "/c", "premake\\premake5", "vs2022"])

def build_on_linux():
    raise NotImplementedError

def build_on_mac():
    raise NotImplementedError


if __name__ == "__main__":
    if globals.IsWindows():
        build_on_windows()
    elif globals.IsLinux():
        build_on_linux()
    elif globals.IsMac():
        build_on_mac()
    else:
        raise NotImplementedError
