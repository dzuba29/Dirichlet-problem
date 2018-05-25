import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
import glob

grids=[1000,1500,600,100] # my grids for dirichlet
threads_pc= [i for i in range(1,5)] #threads of pc
threads_cluster= [i for i in range(1,21)] #threads of cluster
gm={} #means for grids

def get_means(grids,thread_count): # get mean value of grids for current count of threads,returns dictionary
	grids_means={}
	for grid in grids:
		temp_files=glob.glob("surface{}_{}_?.csv".format(thread_count,grid))
		temp_means=[]
		for file in temp_files:
			temp_data=pd.read_csv(file,header=None)
			temp_data=temp_data[len(temp_data)][0]
			temp_means.append(temp_data)
		grids_means[grid]=round(np.mean(temp_means),3)
	return grids_means

def draw_plot(dic): #draw surface to every grid + runtime + gridname
	fig = plt.figure(figsize=(8,12))
	files=glob.glob("surface1_*_0.csv")
	data=[]
	grid, mean_time =list(dic.keys()), list(dic.values())

	for file in files:
		temp_data=pd.read_csv(file,header=None)
		temp_data=temp_data.drop(len(temp_data),1)
		data.append(temp_data)
	for ind,item in enumerate(data):
		ax = fig.add_subplot(len(data),len(data)/2,ind+1, projection='3d')
		Z=np.array(item)
		X = np.arange(0,item.shape[0], 1)
		Y = np.arange(0,item.shape[1], 1)
		Xgrid,Ygrid = np.meshgrid(X,Y)
		ax.plot_surface(Xgrid,Ygrid, Z,cmap=cm.Spectral)
		ax.set_xlabel('Z')
		ax.set_ylabel('X')
		ax.set_title('Grid {} \n Runtime:{} '.format(grid[-ind],mean_time[-ind]))
	fig.suptitle('Threads: 4') 
	plt.tight_layout();plt.savefig('surface4.png');plt.grid(True);plt.show()



gm=get_means(grids,4)
print(gm)

draw_plot(gm)

