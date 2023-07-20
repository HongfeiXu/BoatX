import subprocess
import globals
import os


def build_on_windows(building_config):
    default_path = r"F:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
    VS_BUILD_PATH = os.getenv("VS_BUILD_PATH", default_path)
    sln_name = globals.ENGINE_NAME + ".sln"
    return subprocess.call(["cmd.exe", "/c", VS_BUILD_PATH, sln_name, "/property:Configuration={}".format(building_config)])

def post_build_on_windows(building_config):
    # 1. link resource to bin
    bin_folder_path = os.path.join("bin", building_config, globals.PROJECT_NAME)
    bin_folder_path = os.path.realpath(bin_folder_path)
    resource_path = "resource"
    resource_path = os.path.realpath(resource_path)
    target_resource_path = os.path.join(bin_folder_path, "resource")
    cmd = f"rmdir /s /q {target_resource_path}"
    subprocess.call(cmd, shell=True)
    cmd = f"mklink /D /J {target_resource_path} {resource_path}"
    subprocess.call(cmd, shell=True)
    # 2. copy dll to bin
    import shutil
    sdl2_dll_path = os.path.join("external", "sdl2", "dll", "SDL2.dll")
    sdl2_dll_path = os.path.realpath(sdl2_dll_path)
    target_dll_folder_path = bin_folder_path
    shutil.copy(sdl2_dll_path, target_dll_folder_path)

if __name__ == "__main__":
    import sys
    args = globals.process_arguments(sys.argv[1:])
    building_config = globals.get_argument_value(args, "config", "debug")

    print("Building config: {}\n".format(building_config))
    ret = 0
    if globals.is_windows():
        ret = build_on_windows(building_config)
        post_build_on_windows(building_config)
    sys.exit(ret)
