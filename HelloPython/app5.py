weight = input("Weight : ")
unit = input("(k)g or (L)bs ? ")
if((unit == 'k') or (unit == 'K') ):
    print("weight in Bounds = " + str(float(weight)*2.2))
elif((unit == 'l') or (unit == 'L') ):
    print("weight in Kilograms = " + str((float)(weight)/2.2))