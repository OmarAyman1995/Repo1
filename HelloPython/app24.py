# to open the file

employee_file = open("names.txt", "r")

#to Read a file
# print(employee_file.read())

#to read lines in the files
#print(employee_file.readline())
#print(employee_file.readline())
#print(employee_file.readline())
#print(employee_file.readline())

print(employee_file.readlines())

employee_file.close()

