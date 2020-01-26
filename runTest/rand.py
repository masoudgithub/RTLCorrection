import random 

f=open("patch.pch", "r")
lines =f.readlines()
random.shuffle(lines)
print ("Reshuffled line : ",  lines)

#for line in lines:
#    print(line)
#    print(len(lines))
