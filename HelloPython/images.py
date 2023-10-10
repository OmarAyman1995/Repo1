from tkinter import *
from PIL import ImageTk,Image

root = Tk()
root.title("Learn Embedded at ELECTRONICS FOR ALL")
root.iconbitmap('D:\electronics for all\IMGs\LOGO.ico')

Button_quit = Button(root, text = "Exit Program",command=root.quit)
Button_quit.pack()

my_Img = ImageTk.PhotoImage(Image.open("E:\microcontrollers\Rev\/20H_Course\IMGs\Intel_8742_153056995.jpg"))
my_label = Label(image = my_Img)

my_label.pack()

root.mainloop()