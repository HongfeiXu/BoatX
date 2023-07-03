import subprocess
import globals


def build_on_windows(building_config):
    VS_BUILD_PATH = r"F:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
    sln_name = globals.ENGINE_NAME + ".sln"
    return subprocess.call(["cmd.exe", "/c", VS_BUILD_PATH, sln_name, "/property:Configuration={}".format(building_config)])


if __name__ == "__main__":
    import sys
    args = globals.process_arguments(sys.argv[1:])
    building_config = globals.get_argument_value(args, "config", "debug")

    print("Building config: {}\n".format(building_config))
    ret = 0
    if globals.is_windows():
        ret = build_on_windows(building_config)

    sys.exit(ret)
