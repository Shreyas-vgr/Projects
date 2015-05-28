#To show some messages:
import recsys.algorithm
recsys.algorithm.VERBOSE = True

#from recsys.datamodel.data import Data
from recsys.algorithm.factorize import SVD
#from recsys.evaluation.prediction import RMSE, MAE

#Load SVD from /tmp
svd = SVD(filename='/tmp/movielens') # Loading already computed SVD model

#Display top 10 movies similar to given movie
ITEMID= 1 # Toy Story
list=[]
list=svd.similar(ITEMID)

tup=();

		

#Extracting the 10 MovieIDs
for i in range(0,10):
	#print list[i][0]
	#mystring = str(list[i][0])+"::" 
	mystring = str(list[i][0])	
	with open('ml-1m/movies.dat', 'r') as searchfile:
   		 for line in searchfile:
            		tup=tuple(line.split('::'))
			mystring1 = str(tup[0])
			if mystring == mystring1:
	    			print tup[1]



	#with open('ml-1m/movies.dat', 'r') as searchfile:
   #		 for line in searchfile:
   #     		if "1::" in line:
   #         			tup=tuple(line.split('::'))
#	    			print tup[1]
