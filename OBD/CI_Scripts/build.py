import subprocess
import re
import os
import sys


# Define Thresholds
ram_threshold_percent = 0
flash_threshold_percent = 0
Cmake_path=0

# Quality Gate: check if  Memory Usage exceeds Defined Limit
def Exceute_Quality_Gate_1( output:str,ram_threshold_percent:int,flash_threshold_percent):
   # Define regular expressions for RAM and Flash usage
  ram_usage_regex = r"RAM: +(\d+) B +(\d+) KB +(.+)%"
  flash_usage_regex = r"FLASH: +(\d+) B +(\d+) KB +(.+)%"

    # Search for usage information
  ram_match = re.search(ram_usage_regex, output)
  flash_match = re.search(flash_usage_regex, output)

   #  Extract and Compare Usage
  if ram_match:
    ram_usage_bytes, ram_usage_kb, ram_usage_percent = ram_match.groups()
    ram_usage_percent = float(ram_usage_percent.replace("%", ""))
    if ram_usage_percent > ram_threshold_percent:
      print(f"Quality Gate Failed: RAM usage ({ram_usage_percent:.2f}%) exceeds quality limit ({ram_threshold_percent}%)!")
      exit(1)
    else:
       print("Quality Gate Passed: RAM size is within Valid Range ")
  else:
    print("Warning: RAM usage information not found in output.")

  if flash_match:
    flash_usage_bytes, flash_usage_kb, flash_usage_percent = flash_match.groups()
    flash_usage_percent = float(flash_usage_percent.replace("%", ""))
    if flash_usage_percent > flash_threshold_percent:
      print(f"Quality Gate Failed: Flash usage ({flash_usage_percent:.2f}%) exceeds quality limit ({flash_threshold_percent}%)!")
      exit(1)
    else:
       print("Quality Gate Passed: Flash size is within Valid Range !")
  else:
    print("Warning: Flash usage information not found in output.")

#___________________________________________________________________________________#
# Quality Gate: check if there is any warnings or notes in build
def Execute_Quality_Gate_2( output:str):
   # Define regular expressions for RAM and Flash usage
  Warning_regex = "warning:"
  note_regex = "note:"
  Error_regex = "Error"
  Cmake_Error_regex = "Stop"


    # Search for usage information
  warning_match = re.search(Warning_regex, output)
  note_match= re.search(note_regex, output)
  error_match=re.search(Error_regex,output)
  Cmake_error_match=re.search(Cmake_Error_regex,output)

   #  Compare Warning Match, note that gate will fail if warnings are more than 1 warning as there is a fixed warning produced by linker with each build
  if error_match or Cmake_error_match :
      print("Quality Gate Failed: Build Includes an Error !")
      exit(1)
  else:
    print("Quality Gate Passed: No Errors in Build")
  
  
  if warning_match :
      print("Quality Gate Failed: Build Includes a Warning by Compiler !")
      exit(1)
  
  else:
    print("Quality Gate Passed: No warnings by compiler")

  if note_match :
      print("Quality Gate Failed: Build Includes a note by Compiler ! ")
      exit(1)
  else:
    print("Quality Gate Passed: No notes in Build")


#_______________________________________________________________________Script__________________________________________
if __name__=="__main__":
 
 #check for Arguments
 if len(sys.argv) < 4:
  print("Error: Missing argument. Please provide an argument when running the script.")
  exit(1)
  
 else:
  Cmake_path=sys.argv[1]
  ram_threshold_percent=float(sys.argv[2])
  flash_threshold_percent=float(sys.argv[3])

# Add Set(CI_BUILD_FLAG ON) flag in Cmakelist to enable CI_Build Configurations
 with open("CMakeLists.txt", 'r+') as file:
  content = file.read()
  content = f"Set(CI_BUILD_FLAG ON)\n{content}"
  file.seek(0)
  file.write(content)
  file.truncate()

  # Configure Cmake
  os.system("rm -rf CMakeCache.txt")
  os.system(f"{Cmake_path} -G \"Unix Makefiles\"")

# Compile the code and capture output stream
  print("Compiling code...")
  subprocess.run(["make", "clean"])
  output_stdout = subprocess.run(["make", "all"], capture_output=True, text=True).stdout

# Compile and capture error/warning stream
  subprocess.run(["make", "clean"])
  output_stderr = subprocess.run(["make", "all"], capture_output=True, text=True).stderr

 #print outputs on console
  print(output_stdout)
  print(output_stderr)

 # # Remove the line containing CI_BUILD_FLAG
  content = re.sub(r"^\s*Set\(CI_BUILD_FLAG\s+(.+?)\)"+ r"\n", '', content)

 # # Write the modified content back to the file
  file.seek(0)
  file.write(content)
  file.truncate()

 #Execute Quality Gates
 Execute_Quality_Gate_2(output_stderr)
 Exceute_Quality_Gate_1(output_stdout,ram_threshold_percent,flash_threshold_percent)





