def raiseToPower(base_number,power_number):
    counter=power_number
    retVal = base_number
    counter-=1
    while counter>0:
        retVal*=base_number
        counter-=1
    return retVal

def max_num(num1,num2,num3):
    if ( (num1 >= num2) and (num1 >= num3) ):
        return num1
    elif ( (num2 >= num1) and (num2 >= num3) ):
        return num2
    elif ( (num3 >= num1) and (num3 >= num2) ):
        return num3