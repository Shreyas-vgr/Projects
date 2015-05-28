#To show some messages:
import recsys.algorithm
recsys.algorithm.VERBOSE = True

#from recsys.datamodel.data import Data
from recsys.algorithm.factorize import SVD
#from recsys.evaluation.prediction import RMSE, MAE

#Load SVD from /tmp
svd = SVD(filename='/tmp/movielens') # Loading already computed SVD model

#Display 10 recommended movies to a given user
ITEMID= 1 
list=[]
list=svd.recommend(ITEMID)
#print list

for i in range(0,10):
	print list[i][0]





