import globals
import subprocess
import os
import sys

def run():
    args = globals.process_arguments(sys.argv[1:])
    building_config = globals.get_argument_value(args, "config", "debug")

    backup_woking_dir = os.getcwd()
    exe_workding_dir = os.path.join(os.getcwd(), "bin", building_config, globals.PROJECT_NAME)
    exe_path = os.path.join(exe_workding_dir, globals.PROJECT_NAME)

    os.chdir(exe_workding_dir)
    ret = subprocess.call(exe_path)
    os.chdir(backup_woking_dir)

    return ret

if __name__ == "__main__":
    ret = run()
    sys.exit(ret)
    

