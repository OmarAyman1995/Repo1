x=0
while(x<10):
    no1 = input("no1 = ")
    no2 = input("no2 = ")
    op = input ("operation ? +,-,*,/,% : ")
    if(op=='+'):
        result = float(no1)+float(no2)
    elif(op=='-'):
        result = float(no1)-float(no2)
    elif(op=='*'):
        result = float(no1)*float(no2)
    elif(op=='/'):
        result = float(no1)/float(no2)
    elif(op=='%'):
        result = float(no1)%float(no2)
    x=x+1
    print(str(result))
print("DONE !")