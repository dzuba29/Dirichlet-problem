import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
%matplotlib inline

data = pd.read_csv('surface.csv',header=None)

Z=np.array(data)

X = np.arange(0, 7, 1)
Y = np.arange(0,7, 1)


X2D,Y2D = np.meshgrid(X,Y)

fig = plt.figure()
ax = Axes3D(fig)

ax.plot_surface(X2D,Y2D, Z)