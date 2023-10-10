from tkinter import *
from PIL import ImageTk, Image
from tkinter import messagebox

root = Tk()
root.title("Learn Embedded at ELECTRONICS FOR ALL")
root.iconbitmap('D:\electronics for all\IMGs\LOGO.ico')


def popup():
    #messagebox.showinfo("Notification", "Hello World")
    #messagebox.showwarning("Notification", "Hello World")
    #messagebox.showerror("Notification", "Hello World")
    #messagebox.askquestion("Notification", "Hello World")
    #messagebox.askokcancel("Notification", "Hello World")
    response = messagebox.askyesno("Notification", "Hello World")
    #Label(root, text=response).pack()
    if response == 1:
         Label(root, text="You clicked yes").pack()
    else :
        Label(root, text="You clicked No").pack()


Button(root,text="Popup",command=popup).pack()
 

root.mainloop()