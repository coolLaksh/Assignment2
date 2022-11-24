import matplotlib.pyplot as plt
import numpy as np

list_OTHER = []
list_FIFO = []
list_RR = []

f1 = open("OTHER.txt", "r")

Times = f1.readlines()

Times_String = Times[0].split(" ")

for i in range(0,10):
    list_OTHER.append(float(Times_String[i]))
    
f1.close()

f1 = open("FIFO.txt", "r")

Times = f1.readlines()

Times_String = Times[0].split(" ")

for i in range(0,10):
    list_FIFO.append(float(Times_String[i]))
    
f1.close()

f1 = open("RR.txt", "r")

Times = f1.readlines()

Times_String = Times[0].split(" ")

for i in range(0,10):
    list_RR.append(float(Times_String[i]))
    
f1.close()
 
    
n = 10
r = np.arange(n)
width = 0.25

# for i in range(0,10):
#     print(list_FIFO[i])
#     print(list_OTHER[i])
#     print(list_RR[i])
    

plt.bar(r,list_OTHER,color='b',width = width,edgecolor = 'black',label = 'OTHER')
plt.bar(r + width,list_FIFO,color = 'g', width = width,edgecolor = 'black', label = 'FIFO')
plt.bar(r + 2 * width,list_RR,color= 'y',width = width, edgecolor = 'black', label = 'RR')
    

plt.xlabel("Policy --->")
plt.ylabel("Time in sec --->")

plt.title("Scheduling Time of diffrent policy")

plt.xticks(r+width/2,['1 ','2', '3', '4', '5' ,'6' ,'7' ,'8', '9', '10'])
plt.legend()

plt.show()