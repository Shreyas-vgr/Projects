#import timeit
#start = timeit.default_timer()
#Your statements here


from recsys.utils.svdlibc import SVDLIBC
from recsys.evaluation.prediction import RMSE, MAE

svdlibc = SVDLIBC('./ml-1m/ratings.dat')
svdlibc.to_sparse_matrix(sep='::', format={'col':0, 'row':1, 'value':2, 'ids': int})
svdlibc.compute(k=100)
svd = svdlibc.export()
svd.save_model('/tmp/svd-model', options={'k': 100})
#svd.similar(ITEMID1) # results might be different than example 4. as there's no min_values=10 set here

#stop = timeit.default_timer()
#print stop - start 
