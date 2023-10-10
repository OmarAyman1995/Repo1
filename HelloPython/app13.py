# use 'def' to give a name to a new function
def say_Hi(name, timeNow):
    print("Hi " + name + " its " + str(timeNow) + " Oclock")

def addTwoNumbers(no1,no2):
    return(no1+no2)

no1 = 234
no2 = 756
say_Hi("Omar", 11)
print("no1 + no2 = " + str(addTwoNumbers(no1,no2)))
