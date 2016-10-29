import sys

#To show some messages:
import recsys.algorithm
recsys.algorithm.VERBOSE = True

from recsys.algorithm.factorize import SVD
from recsys.datamodel.data import Data
from recsys.evaluation.prediction import RMSE, MAE

#Dataset
PERCENT_TRAIN = int(sys.argv[2])
data = Data()
data.load(sys.argv[1], sep='::', format={'col':0, 'row':1, 'value':2, 'ids':int})
#Train & Test data
train, test = data.split_train_test(percent=PERCENT_TRAIN)

#Create SVD
K=100
if len(sys.argv) == 4:
    K = int(sys.argv[3])
svd = SVD()
svd.set_data(train)
svd.compute(k=K, min_values=5, pre_normalize=None, mean_center=True, post_normalize=True, savefile='/tmp/movielens')
