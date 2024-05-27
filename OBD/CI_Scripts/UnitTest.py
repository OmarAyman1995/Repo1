import os
from xml.etree import ElementTree as ET
import re
import sys
import fileinput


Top_level_Directory=0
UT_path="Core/StandardFiles/typedefs.h"
JunitReportsList=[]
GcovReportsList=[]
JUnitArtifacte="JunitsReport.xml"
GcovArtifacte="GcovReport.txt"
JUnitQualityLimit=50
GcovQualityLimit=20


def replace_in_file(file_path, search_pattern, replacement):
    with open(file_path, 'r') as file:
        content = file.read()

    updated_content = content.replace(search_pattern, replacement)

    with open(file_path, 'w') as file:
        file.write(updated_content)

def delete_lines_in_file(file_path, pattern):
    with fileinput.FileInput(file_path, inplace=True, backup='.bak') as file:
        for line in file:
            if pattern not in line:
                print(line, end='')

def append_Reports(outputFile,reportsList):
 content:any
 
 with open(outputFile, 'a') as outfile:  # Open artifacte in append mode
    outfile.truncate(0)  # Truncate to zero bytes to clear content
    for report in reportsList:
      try:
        with open(report, 'r') as infile:
          if report==reportsList[0]:
            content= infile.readlines()[:-1]

          elif report!=reportsList[0] and report !=reportsList[-1]:
            content= infile.readlines()[2:-1]
          
          elif report==reportsList[-1]:
            content= infile.readlines()[2:]

          # Append content with double newline for separation
          outfile.writelines(content)
          outfile.write('\n\n')  # Append content with double newline for separation
      except FileNotFoundError:
        print(f"Error: File '{report}' not found. Skipping.")


def set_macro_ut(c_file_path):
  """
  This function reads the contents of a C file, searches for a macro named
  'UT', and if found, sets its value to 'ON'. It then writes the modified
  contents back to the file.

  Args:
      c_file_path (str): The path to the C file to modify.
  """
  with open(c_file_path, "r+") as file:
    content = file.read()
    # Replace '#ifndef UT' with '#define UT ON' if found
    content = content.replace("#define UT OFF", "#define UT ON")
    file.seek(0)  # Move the file pointer to the beginning
    file.write(content)
    file.truncate()  # Remove any extra content




def clear_macro_ut(c_file_path):
  """
  This function reads the contents of a C file, searches for a macro named
  'UT', and if found, sets its value to 'ON'. It then writes the modified
  contents back to the file.

  Args:
      c_file_path (str): The path to the C file to modify.
  """
  with open(c_file_path, "r+") as file:
    content = file.read()
    # Replace '#ifndef UT' with '#define UT ON' if found
    content = content.replace("#define UT ON", "#define UT OFF")
    file.seek(0)  # Move the file pointer to the beginning
    file.write(content)
    file.truncate()  # Remove any extra content


def run_ceedling_Job(project_yml_path):
  """
  Changes directory to the folder containing the project.yml file and runs
  the `ceedling` command, and Quality gates.

  Args:
      project_yml_path (str): The path to the project.yml file.
  """
  #change directory to ceedling project
  project_dir = os.path.dirname(project_yml_path)
  os.chdir(project_dir)
  
  #remove build file
  os.system("rm -rf /build") 

  # Execute the ceedling command
  os.system("ceedling gcov:all utils:gcov")# Execute the ceedling command

  # append Report paths
  jUnitReportPath = os.path.join(project_dir, "build", "artifacts","gcov","report.xml")
  GcovReportPath=os.path.join(project_dir, "build", "artifacts","gcov","Gcov.txt")

  JunitReportsList.append(jUnitReportPath)
  GcovReportsList.append(GcovReportPath)


def QualityGate1(reportsList):

 for jUnitReportPath in reportsList:

  with open(jUnitReportPath, 'r') as file:
   xml_data = file.read()
   root = ET.fromstring(xml_data)
   failures = int(root.attrib['failures'])

   if failures >= JUnitQualityLimit:
    print(f"Quality Gate Failed: Test failures detected in {jUnitReportPath} ! Exiting with error code 1.")
    os.chdir(Top_level_Directory)
    clear_macro_ut(UT_path)
    exit(1)  # Exit with error code 1



def QualityGate2(reportsList):
 """
  Parses the provided code coverage report text using regular expressions to
  extract the overall coverage percentage.

 Args:
      path: The text containing the code coverage report.
 """
 for gcovReportPath in reportsList:

  with open(gcovReportPath,"r+")as file:
    content = file.read()
    pattern = r"TOTAL\s+(\d+)\s+(\d+)\s+(\d+)%"
    match = re.search(pattern, content)

    if match:
     coverage_percentage = int(match.group(3))
     if coverage_percentage <= GcovQualityLimit:
      print(f"Quality Gate Failed: {gcovReportPath} is not 100% Covered")
      os.chdir(Top_level_Directory)
      clear_macro_ut(UT_path)
      exit(1)

def Handle_SWC_UT(paths):
 for path in paths:
    # Go To Top level Directory
    os.chdir(Top_level_Directory)

    # Construct correct path to folder
    search_path= os.path.join(Top_level_Directory, path)
    search_path = search_path.replace("\\", "/")

    #enter every sub-diretory in the folder and search for file project.yml, if found run ceedling
    for root,subdirs, files in os.walk(path):
      for file in files:
         if file == "project.yml":
           project_yml_path = os.path.join(root, file)
           run_ceedling_Job(project_yml_path)
           break  # Stop searching after finding the first project.yml


def Handle_MCAL_SWC_UT(paths,Header_list):
  for i, path in enumerate(paths):
    # Go To Top level Directory
    os.chdir(Top_level_Directory)

    # Construct correct path to folder
    search_path= os.path.join(Top_level_Directory, path)
    search_path = search_path.replace("\\", "/")

    #enter every sub-diretory in the folder and search for file project.yml, if found run ceedling
    for root,subdirs, files in os.walk(path):
      for file in files:
         if file == "project.yml":
           project_yml_path = os.path.join(root, file)
           replace_in_file(Header_list[i],
                '#include "stm32f1xx_hal_def.h"',
                '#include "stm32f1xx_hal_def.h"\r\n#include "stm32f1xx_hal_dma.h"')
           run_ceedling_Job(project_yml_path)
           os.chdir(Top_level_Directory)
           delete_lines_in_file(Header_list[i],
                     '#include "stm32f1xx_hal_dma.h"')
           break  # Stop searching after finding the first project.yml





if __name__=="__main__":

#  #check for Arguments
 if len(sys.argv) < 3:
  print("Error: Missing argument. Please provide an argument when running the script.")
  exit(1)
 
 else:

  JUnitQualityLimit=int(sys.argv[1])
  GcovQualityLimit=float(sys.argv[2])

  
   # Software Components Paths
  paths_1 = ["Core/HAL/Battery",
           "Core/HAL/LED_Driver",
           "Core/HAL/Mqtt_Driver",
           "Core/HAL/Buzzer_Driver",
           "Core/HAL/Bluetooth_Driver",
           "Core/HAL/CRS",
           "Core/App/AlarmApp",
           "Core/App/LowPowerApp",
           "Core/App/MonitroingApp",
           "Core/App/QueueInterface",
           "Core/App/Vehicle_App",
           "Core/Middleware/CAN_ISO_15765",
           "Core/Middleware/CANTp",
           "Core/Middleware/ISO_Uart_Protocols",
           "Core/Middleware/OBDIIHandler",
           "Core/Middleware/UDSHandler",
           "Core/MCAL/GPIO",
           "Core/MCAL/MCU",
           "Core/MCAL/WDT",
           "Core/MCAL/CanDriver"
           ]
  
   # Some MCAL Componenets that requires writing in generated STM files for UT to work
  paths_2 = [
           "Core/MCAL/ADC",
           "Core/MCAL/I2C",
           "Core/MCAL/UART"
           ]
  
  #
  Header_list=["Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"
               ,"Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h"
               ,"Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_uart.h"]

  # change directory to top level
  Top_level_Directory=os.getcwd()
  
  #enable UT macro in file typedefs.c
  set_macro_ut(UT_path)

  # Handle SWC UT
  Handle_SWC_UT(paths_1)

  #Handle MCAL SWC that requires writing in generated Files
  Handle_MCAL_SWC_UT(paths_2,Header_list)
  
  # Go To Top level Directory
  os.chdir(Top_level_Directory)
         
  #append files in one file for artifactes
  append_Reports(JUnitArtifacte,JunitReportsList)
  append_Reports(GcovArtifacte,GcovReportsList)
  
  #clear UT Macro for Unit testing
  clear_macro_ut(UT_path)

  #Quality gate for jUnit report 
  QualityGate1(JunitReportsList)

  #Quality gate for Gcov report
  QualityGate2(GcovReportsList)
  

