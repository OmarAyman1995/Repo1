from tkinter import *
from PIL import ImageTk, Image

root = Tk()
root.title("Learn Embedded at ELECTRONICS FOR ALL")
root.iconbitmap('D:\electronics for all\IMGs\LOGO.ico')

My_frame = LabelFrame(root,text="This is My frame " , padx= 50, pady= 50)
My_frame.pack(padx= 10 , pady= 10)


Button1  = Button(My_frame,text= "Don Not click here !")
Button2  = Button(My_frame,text= "..or here !")

Button1.grid(row = 0, column = 0 )
Button2.grid(row = 1, column = 1 )


root.mainloop()