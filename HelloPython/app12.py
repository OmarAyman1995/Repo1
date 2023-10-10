#tuples
#tuples are immutables (you can NOT modify them), this is a difference between tuples and lists

coordinate = (12.3, 3.0)
print(coordinate[0])
print(coordinate[1])
print(coordinate)
# this will give you an error, because tuple is immutable, you can not change its values ---> coordinate[0] = 1.4

#list of tubles 
listX = [(1,4),(3,4),(4,67)]
listX[0]=(2.3,4)
print(listX)
