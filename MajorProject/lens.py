import sys

#To show some messages:
import recsys.algorithm
recsys.algorithm.VERBOSE = True

from recsys.algorithm.factorize import SVD
from recsys.datamodel.data import Data
from recsys.utils.svdlibc import SVDLIBC
from recsys.evaluation.prediction import RMSE, MAE

#Dataset
PERCENT_TRAIN = int(sys.argv[2])
data = Data()
data.load(sys.argv[1], sep='::', format={'col':0, 'row':1, 'value':2, 'ids':int})
#Train & Test data
train, test = data.split_train_test(percent=PERCENT_TRAIN)

svdlibc = SVDLIBC('./ml-1m/ratings.dat')
svdlibc.to_sparse_matrix(sep='::', format={'col':0, 'row':1, 'value':2, 'ids': int})
svdlibc.compute(k=100)
svd = svdlibc.export()
svd.save_model('/tmp/svd-model', options={'k': 100})
#svd.similar(ITEMID1) # results might be different than example 4. as there's no min_values=10 set here


#Evaluation using prediction-based metrics
print 'Evaluating...'
rmse = RMSE()
mae = MAE()
for rating, item_id, user_id in test.get():
    try:
        pred_rating = svd.predict(item_id, user_id, 0.0, 5.0)
        rmse.add(rating, pred_rating)
        mae.add(rating, pred_rating)
    except KeyError:
        continue

print 'RMSE=%s' % rmse.compute()
print 'MAE=%s' % mae.compute()
