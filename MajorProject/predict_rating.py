import sys

#To show some messages:
import recsys.algorithm
recsys.algorithm.VERBOSE = True

from recsys.datamodel.data import Data
from recsys.algorithm.factorize import SVD
from recsys.evaluation.prediction import RMSE, MAE
import sys

#Dataset
#PERCENT_TRAIN = 80
data = Data()
data.load('./ml-1m/ratings.dat', sep='::', format={'col':0, 'row':1, 'value':2, 'ids':int})

#Load SVD from /tmp
svd2 = SVD(filename='/tmp/movielens') # Loading already computed SVD model

#Predict User rating for given user and movie:
USERID = 2   
ITEMID= 1 # Toy Story
rating1=svd2.predict(ITEMID, USERID, 0.0, 5.0)
print 'Predicted rating=%f'% rating1

flag=0
#Retrieve actual rating for given user and movie
for rating, item_id, user_id in data.get():
	if user_id == USERID and item_id == ITEMID:
		rat = rating
		#print 'Actual rating=%f' % rating
		flag=1
		break
		
if flag == 1:
	print 'Actual rating=%f'% rat
else :
	sys.exit("No actual rating available")

#Evaluating prediction
rmse = RMSE()
mae = MAE()
rmse.add(rating1, rat)
mae.add(rating1, rat)
print 'RMSE=%s' % rmse.compute()
print 'MAE=%s' % mae.compute()
