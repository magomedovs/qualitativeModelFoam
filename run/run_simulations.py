import os
import shutil
import subprocess


def exec_script(dir_path, script_name):
    allrun_path = os.path.join(dir_path, script_name)
    if os.path.isfile(allrun_path):
        try:
            # Make Allrun executable
            os.chmod(allrun_path, 0o755)
            # Run Allrun in its directory
            subprocess.run([allrun_path], cwd=dir_path, check=True)
            print(f"Successfully executed {script_name} in {dir_path}")
        except subprocess.CalledProcessError as e:
            print(f"{script_name} failed in {dir_path}: {str(e)}")
    else:
        print(f"{script_name} script not found in {dir_path}")


def replace_string(file_path, str_to_replace, new_str):
    try:
        with open(file_path, 'r') as f:
            content = f.read()
        
        updated = content.replace(str_to_replace, str(new_str))
        
        with open(file_path, 'w') as f:
            f.write(updated)
        print(f"Updated {os.path.basename(file_path)} with h={new_str}")
        
    except FileNotFoundError:
        print(f"Error: {os.path.basename(file_path)} not found in {os.path.dirname(file_path)}")
    except Exception as e:
        print(f"Failed to modify {file_path}: {str(e)}")


template_dir_rel_path = "qualitativeModel_convergence_test" # Path to the dir with template
template_dir = os.path.basename(template_dir_rel_path)

cellNum     = [2**k for k in range(1, 3, 1)]                # Number of cells per unit length
time_steps  = [0.25 / 2**k for k in range(len(cellNum))]    # Time step is chosen for CFL to be < 1

blockMeshDict_file  = os.path.join("system", "blockMeshDict")
controlDict_file    = os.path.join("system", "controlDict")

blockMeshDict_search_str  = "cellsPerUnitSubs"
controlDict_search_str    = "timeStepSubs"

# Get absolute paths
template_abs = os.path.abspath(template_dir_rel_path)
parent_dir = os.path.dirname(template_abs)

for i in range(len(cellNum)):
    new_dir = os.path.join(parent_dir, f"{template_dir}_{cellNum[i]}")
    # print(new_dir)

    if os.path.exists(new_dir):
        print(f"Skipping existing directory: {new_dir}")
        continue
        
    # 1. Copy template directory
    shutil.copytree(template_abs, new_dir)
    print(f"Created: {new_dir}")
    
    # 2.1 Modify blockMeshDict
    blockMeshDict_file_path = os.path.join(new_dir, blockMeshDict_file)
    replace_string(blockMeshDict_file_path, blockMeshDict_search_str, cellNum[i])
    
    # 2.2 Modify controlDict
    controlDict_file_path = os.path.join(new_dir, controlDict_file)
    replace_string(controlDict_file_path, controlDict_search_str, time_steps[i])

    # 3. Execute Allrun script
    # exec_script(new_dir, "Allrun")
    exec_script(new_dir, "Allrun-parallel")
        