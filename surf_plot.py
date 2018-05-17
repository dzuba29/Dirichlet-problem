import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

data = pd.read_csv('surface4.csv',header=None)



time=data[len(data)][0] #get time
data = data.drop(len(data), 1) #drop last 'time' column


Z=np.array(data)
X = np.arange(0, data.shape[0], 1)
Y = np.arange(0,data.shape[1], 1)

X2D,Y2D = np.meshgrid(X,Y)
fig = plt.figure()
ax = Axes3D(fig)

ax.plot_surface(X2D,Y2D, Z)
plt.title("Surface\n"+"Time:"+str(time))
plt.show()