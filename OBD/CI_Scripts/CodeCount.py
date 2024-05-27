import os
import subprocess
import csv
import sys


#Global Variables 
cloc_report= "cloc_report.csv"
clocQuaityLimit=0
cloc_path=0


# CppCheck Function
def run_cloc(folders, output_file):
  """
  Runs cppcheck on the provided folders (relative to the script's location) and saves the report to the specified file.

  Args:
      folders: List of folder names relative to the script (strings).
      output_file: Path to save the cppcheck report (string).

  """

  script_dir = os.path.dirname(os.path.abspath(__file__))  # Get script directory
  cloc_cmd = [f"{cloc_path}"]
  cloc_cmd.extend([
      "--by-file",
      "--csv",
      f"--out={output_file}"
  ])

  #Iterate on all folders
  for folder in folders:
   # create a list of components names
   script_dir = os.path.dirname(os.path.abspath(__file__))  # Get script directory (optional for relative paths)
   subdirs = os.path.join(script_dir, folder) if not os.path.isabs(folder) else folder  # Handle relative paths
   subdirs = [d for d in os.listdir(subdirs) if os.path.isdir(os.path.join(subdirs, d))]
   
   #iterate on all components in folders
   for subdir in subdirs:
     relative_folders = [os.path.join(script_dir, folder,subdir,"src")]
     cloc_cmd.extend(relative_folders)
     
  try:
    subprocess.run(cloc_cmd, check=True)
  except subprocess.CalledProcessError as e:
    print(f"Cloc failed with exit code: {e.returncode}")
    

def ExecuteQualityGate1(outputReport,ClocQualityLimit):

  with open(outputReport, 'r') as csvfile:
    reader = csv.reader(csvfile)
    # Skip the header row (assuming first row contains column names)
    next(reader)

    for row in reader:
      # Check if it's the last line (containing "SUM")
      if row[0].upper() == 'SUM':
        continue

      # Assuming no delimiter separates filename and metrics, split on spaces
      # Extract filename and code lines (last element)
      file_info = row[4].split()
      file_name=  row[1].split()
      code_lines = int(file_info[-1])

      if code_lines > ClocQualityLimit:
        print(f"Quality Gate Failed: File '{file_name}' exceeds code limit ({ClocQualityLimit}) with {code_lines} lines.")
        exit(1)


    print(f"Quality Gate Passed: all Components are under {ClocQualityLimit} lines.")
           

   



if __name__=="__main__":

 #check for Arguments
 if len(sys.argv) < 3:
  print("Error: Missing argument. Please provide an argument when running the script.")
  exit(1)
  
 else:
  cloc_path=sys.argv[1] 
  clocQuaityLimit=int(sys.argv[2])
 folders_to_lint = ["../Core/App",
                    "../Core/HAL",
                    "../Core/MCAL",
                    "../Core/Middleware",
                    "../Core/StandardFiles"]  # Folder names relative to script
# run cppcheck
 print("Running Linting Tool For all Files ")
 run_cloc(folders_to_lint, cloc_report)
 ExecuteQualityGate1(cloc_report,clocQuaityLimit)