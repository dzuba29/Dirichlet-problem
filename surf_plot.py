import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import glob

allFiles = glob.glob("*.csv")

data=[]
time=[]

for file in allFiles:
	temp_data=pd.read_csv(file,header=None)
	temp_time=temp_data[len(temp_data)][0]
	temp_data=temp_data.drop(len(temp_data),1)
	data.append(temp_data)
	time.append(temp_time)


fig = plt.figure(figsize=(8,12))


for ind,item in enumerate(data):

	ax = fig.add_subplot(len(data),len(data)/2,ind+1, projection='3d')
	Z=np.array(item)
	X = np.arange(0,item.shape[0], 1)
	Y = np.arange(0,item.shape[1], 1)
	Xgrid,Ygrid = np.meshgrid(X,Y)

	ax.plot_surface(Xgrid,Ygrid, Z)
	ax.set_xlabel('Z')
	ax.set_ylabel('X')
	ax.set_zlabel('Y')

plt.tight_layout()
plt.savefig('yolo.pdf')
plt.show()
