# understanding lists
MyInfo = ["Omar", 27, 185.0, "maadi", "cairo", 2]
print(MyInfo[2])
print(MyInfo[0])
print(MyInfo[-1])
print(MyInfo)
print(MyInfo[3:])

MyInfo.reverse()
print(MyInfo)

lucky_numbers = [4, 5, 7, 8, 4, 3]
MyInfo.extend(lucky_numbers)
print(MyInfo)

MyInfo.append("Creed")
print(MyInfo)

MyInfo.insert(1, "Cairo")
print(MyInfo)

MyInfo.remove(2)
print(MyInfo)

#remove just last element
MyInfo.pop()
print(MyInfo)  

print(MyInfo.index("Omar"))
