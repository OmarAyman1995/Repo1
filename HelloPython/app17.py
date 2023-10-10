# how to convert Jan -> January
#                Oct -> October
#                and so on! 
#solution is : use the Dectionary in python

monthConversions = {
    #key :  Value
    "Jan": "January" ,
    "Feb": "February",
    "Mar": "March" ,
    "Apr": "April" ,
    "May": "May" ,
    "Jun": "June" ,
    "Jul": "July" ,
    "Aug": "Augest" ,
    "Sep": "September" ,
    10: "October" ,
    "Nov": "November" ,
    "Dec": "December" ,
}

print(monthConversions["Apr"])
print(monthConversions.get("Dec"))
print(monthConversions.get("Luv")) #None
print(monthConversions.get("Luv" , " Not a valid key")) #Not a valid key
print(monthConversions.get(10))