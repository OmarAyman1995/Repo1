from tkinter import *
from PIL import ImageTk, Image

root = Tk()
root.title("Learn Embedded at ELECTRONICS FOR ALL")
root.iconbitmap('D:\electronics for all\IMGs\LOGO.ico')

#r = IntVar()
#r.set(2)

def clicked(value):
    myLabel = Label(root,text=value)
    myLabel.pack()


MODES = [
    ("TIVAC" , "TIVAC"),
    ("ARDUINO MEGA" , "ARDUINO MEGA"),
    ("STM BLUE PILL" , "STM BLUE PILL"),
    ("MICROCHIP DEV BOARD" , "MICROCHIP DEV BOARD"),
]

MCU = StringVar()
MCU.set("TIVAC")

for text, mode in MODES:
    Radiobutton(root, text=text, variable=MCU, value=mode, command=lambda:clicked(MCU.get())).pack()


#Radiobutton(root,text="option1",variable=r,value=1,command= lambda:clicked(r.get())).pack()
#Radiobutton(root,text="option2",variable=r,value=2,command= lambda:clicked(r.get())).pack()



myLabel = Label(root,text=MCU.get())
myLabel.pack()

root.mainloop()