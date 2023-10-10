from tkinter import *


root = Tk()

# creating a Label Widget
myLabel1 = Label(root, text = "Hello World!")
myLabel2 = Label(root, text = "My name is Omar Ayman!")
# shoving it onto the screen
myLabel1.grid(row=0,column=0)
myLabel2.grid(row=1,column=0)
#myLabel2.grid(row=1,column=1)
#myLabel2.grid(row=1,column=5) #kinter wont put it in col5 instead it will put it in col1 because 2,3,4 are empty so it will ignore 5 and replace it with col1 

# Looping
root.mainloop()
