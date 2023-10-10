#print(2**8)

#how to use for loop to creat function like exponent by your own 

def raiseToPower(base_number,power_number):
    counter=power_number
    retVal = base_number
    counter-=1
    while counter>0:
        retVal*=base_number
        counter-=1
    return retVal

print(raiseToPower(2,32))