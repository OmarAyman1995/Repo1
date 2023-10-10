from tkinter import *
from PIL import ImageTk,Image



root = Tk()
VarInc =0

#title and image of my app
root.title("Learn Embedded at ELECTRONICS FOR ALL")
root.iconbitmap('D:\electronics for all\IMGs\LOGO.ico')

#create Images
my_Img1 = ImageTk.PhotoImage(Image.open("E:\microcontrollers\Rev\/20H_Course\IMGs\Intel_8742_153056995.jpg"))
my_Img2 = ImageTk.PhotoImage(Image.open("E:\microcontrollers\Rev\/20H_Course\IMGs\AT89C51AC3.jfif"))
my_Img3 = ImageTk.PhotoImage(Image.open("E:\microcontrollers\Rev\/20H_Course\IMGs\ATmega32A.jfif"))
my_Img4 = ImageTk.PhotoImage(Image.open("E:\microcontrollers\Rev\/20H_Course\IMGs\PIC12f675.jfif"))
my_Img5 = ImageTk.PhotoImage(Image.open("E:\microcontrollers\Rev\/20H_Course\IMGs\PIC16f877a.jfif"))


#creat list of images
image_list = [my_Img1,my_Img2,my_Img3,my_Img4,my_Img5]

#creat a new lable
status = Label(root,text= "Image"+ str(VarInc+1) + " of " + str(len(image_list)), bd = 1,relief=SUNKEN,anchor=E)
#creat label to show images
my_label = Label(image = my_Img1)
my_label.grid(row=0,column=0,columnspan=3)

#APIs to control next and previous images showing
def forward():
    global my_label
    global button_forward
    global button_back
    global VarInc
    global status

    button_back=Button(root,text="<<",command=lambda: back())
    button_back.grid(row=1,column=0)  

    if VarInc == 4:
        my_label.grid_forget()
        my_label = Label(image=image_list[VarInc])
        my_label.grid(row=0,column=0,columnspan=3)
        status = Label(root,text= "Image "+ str(VarInc+1) + " of " + str(len(image_list)), bd = 1,relief=SUNKEN,anchor=E)
        status.grid(row=2,column=0,columnspan=3,sticky=W+E)
        button_forward.destroy()
    
    elif(VarInc >= 0 and VarInc < 5) :
        VarInc+=1
        my_label.grid_forget()
        my_label = Label(image=image_list[VarInc])
        my_label.grid(row=0,column=0,columnspan=3)
        status = Label(root,text= "Image "+ str(VarInc+1) + " of " + str(len(image_list)), bd = 1,relief=SUNKEN,anchor=E)
        status.grid(row=2,column=0,columnspan=3,sticky=W+E)

def back():
    global my_label
    global button_forward
    global button_back    
    global VarInc
    global status
    

    button_forward=Button(root,text=">>",command=lambda: forward())
    button_forward.grid(row=1,column=2)

    if(VarInc == 0):
        
        my_label.grid_forget()
        my_label = Label(image=image_list[VarInc])
        my_label.grid(row=0,column=0,columnspan=3)
        status = Label(root,text= "Image "+ str(VarInc+1) + " of " + str(len(image_list)), bd = 1,relief=SUNKEN,anchor=E)
        status.grid(row=2,column=0,columnspan=3,sticky=W+E)
        button_back.destroy()

    elif(VarInc >= 0 and VarInc < 5) :
        VarInc-=1
        my_label.grid_forget()
        my_label = Label(image=image_list[VarInc])
        my_label.grid(row=0,column=0,columnspan=3)
        status = Label(root,text= "Image "+ str(VarInc+1) + " of " + str(len(image_list)), bd =1,relief=SUNKEN,anchor=E)
        status.grid(row=2,column=0,columnspan=3,sticky=W+E)


#creat Buttons
button_back=Button(root,text="<<",command=lambda: back())
button_forward=Button(root,text=">>",command=lambda: forward())
button_Exit=Button(root,text="Exit Program",command=root.quit)

#show Buttons
button_back.grid(row=1,column=0)   
button_Exit.grid(row=1,column=1 , pady=10)
button_forward.grid(row=1,column=2)

#show status 
status.grid(row=2,column=0,columnspan=3,sticky=W+E)
#perform code periodically
root.mainloop()