# Guessing Game 
secret_word = "Texas"
guess = ""
times = 1
while guess != secret_word and times<=3:
    guess  = input ("Enter guess : ")
    times = times+1
if(guess == secret_word):
    print("You Win! ")
else:
    print("You Lost")