from tkinter import *

root = Tk()

def myClick():
    myLabel = Label(root, text = "Look I clicked a button!")
    myLabel.pack()
#creat
#MyButton = Button(root, text = "Click Me!",state = DISABLED)
#fg = foreground color , bg = background color
MyButton = Button(root, text = "Click Me!",fg="red" ,bg="black" , padx=50,pady=50,command=myClick)

#put it on the root
MyButton.pack()
# Looping
root.mainloop()
