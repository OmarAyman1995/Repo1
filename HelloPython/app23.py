try:
    # value = 10/0
    number = int(input("Enter a number "))
    print(number)

except ZeroDivisionError:
    print("Divided By Zero Error!")

except ValueError:
    print("INVALID INPUT Error!")
