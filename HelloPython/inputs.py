from tkinter import *

root = Tk()

e = Entry(root,width = 50 , fg = "blue" , borderwidth=5)
e.pack()
e.insert(0,"Enter your Name")    

def myClick():
    myLabel = Label(root, text =  "Hello " + e.get())
    myLabel.pack()

MyButton = Button(root, text = "Enter your name",fg="red" , padx=10,pady=10,command=myClick)

#put it on the root
MyButton.pack()
# Looping
root.mainloop()
