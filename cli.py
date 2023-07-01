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


def run_cmd(cmd_args):
    """
    run a command with one or more args
    """
    tools_dir = os.path.join(os.getcwd(), tools.globals.TOOLS_DIR)
    cmd_script = cmd_args[0] + ".py"
    cmd_args[0] = os.path.join(tools_dir, cmd_script)
    if os.path.exists(cmd_args[0]):
        cmd_args.insert(0, "python3")
        ret = subprocess.call(cmd_args)
    else:
        print("Invalid command: {}".format(cmd_args[0]))
        ret = -1
    return ret


if __name__ == "__main__":
    """
    Example:
        Input:
        cli buildsln -config=release
        Output:
        cmd_args = ["buildsln", "config=release"]
    """
    argc = len(sys.argv)

    i = 1
    while i < argc:
        cmd_args = [sys.argv[i]]
        while True:
            if i < argc - 1 and sys.argv[i+1][0] == "-":
                cmd_args.append(sys.argv[i+1][1:])
                i = i + 1
            else:
                break

        print("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("Executing: ", " ".join(cmd_args))
        time_start = time.time()
        if run_cmd(cmd_args) != 0:
            print(f"Error: run cmd \"{cmd_args}\" failed")
            break
        time_used = time.time() - time_start
        print("Finish: {}, take {} secs".format(cmd_args[0], round(time_used, 3)))
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
        i = i + 1

