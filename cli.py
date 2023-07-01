# cli build
# cli run
# cli gen
# cli version
# cli gen build run

import os
import subprocess
import sys
import time

import tools.globals


def run_cmd(cmd):
    tools_dir = os.path.join(os.getcwd(), tools.globals.TOOLS_DIR)
    cmd_script = cmd+".py"
    cmd_script_path = os.path.join(tools_dir, cmd_script)
    subprocess.call(["python3", cmd_script_path])


if __name__ == "__main__":
    for i in range(1, len(sys.argv)):
        cmd = sys.argv[i]

        print("\n-----------------------")
        print("Executing: ", cmd)
        time_start = time.time()
        run_cmd(cmd)
        time_used = time.time() - time_start
        print("Finish: {}, take {} secs".format(cmd, round(time_used, 3)))
        print("-----------------------")

