from tkinter import *

root = Tk()
root.title("Simple Calculator")

# text-box
e = Entry(root, width=35,  borderwidth=5)
e.grid(row=0, column=0, columnspan=3, padx=10, pady=10)

#functions 
def buttonClick(number):
    current = e.get()
    e.delete(0, END)
    e.insert(0,  str (current) + str(number))
    
def buttonClear():
    e.delete(0, END)    

def buttonAdd():
    global number1
    global operation
    operation = '+'
    number1 = e.get()
    e.delete(0, END)

def buttonSubstract():
    global number1
    global operation
    operation = '-'
    number1 = e.get()
    e.delete(0, END)

def buttonEqual():
    global number2
    global operation
    number2 = e.get()
    e.delete(0, END)
    if operation == '+':
        number2 = float(number2) + float(number1)
    if operation == '-':
        number2 = float(number1) - float(number2)
    elif operation == '*':
        number2 = float(number2) * float(number1)
    elif operation == '/':
        number2 = float(number1) / float(number2)  
    e.insert(0,str(number2))

def buttonMultiply():
    global number1
    global operation
    operation = '*'
    number1 = e.get()
    e.delete(0, END)

def buttonDivision():
    global number1
    global operation
    operation = '/'
    number1 = e.get()
    e.delete(0, END)
# buttons 
button1 = Button(root, padx=40, pady=20, text="1", command=lambda: buttonClick(1))
button2 = Button(root, padx=40, pady=20, text="2", command=lambda: buttonClick(2))
button3 = Button(root, padx=40, pady=20, text="3", command=lambda: buttonClick(3))
button4 = Button(root, padx=40, pady=20, text="4", command=lambda: buttonClick(4))
button5 = Button(root, padx=40, pady=20, text="5", command=lambda: buttonClick(5))
button6 = Button(root, padx=40, pady=20, text="6", command=lambda: buttonClick(6))
button7 = Button(root, padx=40, pady=20, text="7", command=lambda: buttonClick(7))
button8 = Button(root, padx=40, pady=20, text="8", command=lambda: buttonClick(8))
button9 = Button(root, padx=40, pady=20, text="9", command=lambda: buttonClick(9))
button0 = Button(root, padx=40, pady=20, text="0", command=lambda: buttonClick(0))


buttonClear = Button(root, padx=125, pady=20, text="Clear", command=buttonClear)
buttonDiv   = Button(root, padx=39, pady=20, text="/", command=buttonDivision)
buttonBlus  = Button(root, padx=39, pady=20, text="+", command=buttonAdd)
buttonSub   = Button(root, padx=39, pady=20, text="-", command=buttonSubstract)
buttonMult  = Button(root, padx=39, pady=20, text="*", command=buttonMultiply)
buttonEqual = Button(root, padx=39, pady=20, text="=", command=buttonEqual)


# put the buttons on the screen
button1.grid(row=3, column=0)
button2.grid(row=3, column=1)
button3.grid(row=3, column=2)

button4.grid(row=2, column=0)
button5.grid(row=2, column=1)
button6.grid(row=2, column=2)

button7.grid(row=1, column=0)
button8.grid(row=1, column=1)
button9.grid(row=1, column=2)

button0.grid(row=4, column=0)

buttonSub.grid(row=4, column=2)
buttonDiv.grid(row=4, column=1)
buttonBlus.grid(row=5, column=0)
buttonMult.grid(row=5,column=1)
buttonEqual.grid(row=5, column=2)
buttonClear.grid(row=6, column=0,columnspan=3)
# button1.pack()


# Labels (Result)

# Looping
root.mainloop()
