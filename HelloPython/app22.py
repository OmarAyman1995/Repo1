def translate(phrase):
    result = " "
    counter = 0
    for element in phrase:
        if element in "AEUOIaeuoi":
            result = result + "g"
        else:
            result = result + element
    return result

#print(translate("Hello You!"))

print(translate("Hello"))
    