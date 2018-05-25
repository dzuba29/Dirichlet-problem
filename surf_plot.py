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

def divide_dic(d1,d2,threads=1): #why?
	return dict((k, float(d1[k]) / d2[k]/threads) for k in d1)

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

def draw_surf(dic): #draw surface for every grid + runtime + gridname
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
	fig.suptitle('Threads: 1') 
	plt.tight_layout();
	plt.savefig('surface1.png');plt.grid(True);plt.show()

# gm=get_means(grids,1)
# draw_surf(gm)
def draw_plot(grids,threads):
	ott=get_means(grids,1) # one thread time for every grid
	means={}
	fig = plt.figure()
	g=sorted(grids)[::-1]
	for i,thread in enumerate(threads):
		means=get_means(grids,thread) 
		plt.plot(threads[::-1],sorted(list(means.values())),label="Grid: {}x{}".format(g[i],g[i]))
	plt.legend()
	plt.show()




draw_plot(grids,threads_pc)

# ott={}
# ott=get_means(grids,1) # one thread time for every grid
# def draw_plot(ott,grids,thread_count,threads): #draw runtime,acc,eff plots
# 	grid_means={};acc_dic={};eff_dic={}
# 	grid_means=get_means(grids,thread_count) 
# 	acc_dic=divide_dic(ott,grid_means)
# 	eff_dic=divide_dic(ott,grid_means,thread_count)
# 	print(ott)
# 	print(grid_means)
# 	print(acc_dic)
# 	print(eff_dic)

# 	fig = plt.figure()
# 	runtime = fig.add_subplot(212);acc = fig.add_subplot(221);eff= fig.add_subplot(222)

# 	runtime.set_title('Runtime');runtime.set_xlabel('Threads');runtime.set_ylabel('Time')
# 	acc.set_title('Acceleration');acc.set_xlabel('Threads');acc.set_ylabel('Acceleration')
# 	eff.set_title('Efficiency');eff.set_xlabel('Threads');eff.set_ylabel('Efficiency')

# 	runtime.plot(threads,list(grid_means.values()))
# 	acc.plot(threads,list(acc_dic.values()))
# 	eff.plot(threads,list(eff_dic.values()))
# 	plt.subplots_adjust(wspace=0.5, hspace=0.6)
# 	plt.show()



# draw_plot(ott,grids,1,threads_pc[::-1])

