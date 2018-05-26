import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
import glob

grids=[1000,1500,600,100] # my grids for dirichlet
threads_pc= [i for i in range(1,5)] #threads of pc
threads_cluster= [1 ,2 ,4 ,8 ,10 ,18 ,20] #threads of cluster
gm={} #means for grids

def means_dic(grids,thread_count): # get mean value of grids for current count of threads,returns dictionary
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

def means_list(grid,thread_count): #same as previous, just tooooooooOOOOOOOOO lazy to optimize
	grids_means=[]
	temp_files=glob.glob("surface{}_{}_?.csv".format(thread_count,grid))
	temp_means=[]
	for file in temp_files:
		temp_data=pd.read_csv(file,header=None)
		temp_data=temp_data[len(temp_data)][0]
		temp_means.append(temp_data)
	grids_means.append(round(np.mean(temp_means),3))
	return grids_means

def draw_surf(dic,t): #draw surface for every grid + runtime + gridname
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
	fig.suptitle('Threads: {}'.format(t)) 
	plt.tight_layout();
	plt.savefig('surface{}.pdf'.format(t));
	plt.savefig('surface{}.svg'.format(t));
	plt.grid(True);plt.show()

def draw_plot(grids,threads):
	fig = plt.figure()
	for grid in grids:
		means=[]
		for thread in threads:
			temp_files=glob.glob("surface{}_{}_?.csv".format(thread,grid))
			temp_means=[]
			for file in temp_files:
				temp_data=pd.read_csv(file,header=None)
				temp_data=temp_data[len(temp_data)][0]
				temp_means.append(temp_data)
			means.append(np.mean(temp_means))
			ott=np.array(means_list(grid,1))
			m=np.array(means)
		rt = fig.add_subplot(221)
		ac = fig.add_subplot(222)
		eff = fig.add_subplot(223)
		rt.set_title('Runtime'); rt.set_xlabel('threads'); rt.set_ylabel('time')
		ac.set_title('Acceleration'); ac.set_xlabel('threads'); ac.set_ylabel('acceleration')
		eff.set_title('Efficiency'.format(grid,grid)); eff.set_xlabel('threads'); eff.set_ylabel('efficiency')	

		rt.plot(threads,m,marker='.',label="Grid {}x{}".format(grid,grid))
		rt.legend(loc=1, fontsize = 'x-small')
		ac.plot(threads,ott/m,marker='.',label="Grid {}x{}".format(grid,grid))
		ac.legend(loc=2, fontsize = 'x-small')
		eff.plot(threads,ott/m/np.array(threads),marker='.',label="Grid {}x{}".format(grid,grid))
		eff.legend(loc=4, fontsize = 'x-small')
		rt.grid(True);ac.grid(True);eff.grid(True)
	plt.tight_layout()
	plt.legend(fontsize = 'x-small')
	plt.savefig('eff_plots.pdf')
	plt.savefig('eff_plots.svg')
	plt.show()
	


gm=means_dic(grids,4)
draw_surf(gm,4)
# draw_plot(sorted(grids),sorted(threads_cluster))
# draw_plot(sorted(grids),sorted(threads_pc))