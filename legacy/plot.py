import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import glob

allFiles = glob.glob("*.csv")

time=[]
threads= [str(i) for i in range(1,5)]

for file in allFiles:
	temp_data=pd.read_csv(file,header=None)
	temp_time=temp_data[len(temp_data)][0]
	time.append(temp_time)


fig = plt.figure()


plt.plot(threads,time[::-1],label="Grid: 1000x1000")
plt.title('Runtime pc');plt.xlabel('Threads');plt.ylabel('Time')
plt.legend()
plt.tight_layout()
plt.savefig('runtime.png')
plt.show()


first_thread=time[3]
acc=[]
for item in time:
	acc.append(first_thread/item)

plt.plot(threads,acc[::-1],label="Grid: 1000x1000")
plt.title('Acceleration pc');plt.xlabel('Threads');plt.ylabel('Acceleration')
plt.legend()
plt.tight_layout()
plt.savefig('Acceleration.png')
plt.show()



eff=[]
t=threads[::-1]
for i,item in enumerate(time):
	eff.append(first_thread/item/float(t[i]))

print(eff)



plt.plot(t,eff,label="Grid: 1000x1000")
plt.title('Efficiency pc');plt.xlabel('Threads');plt.ylabel('Efficiency')
plt.legend()
plt.tight_layout()
plt.savefig('Efficiency.png')
plt.show()