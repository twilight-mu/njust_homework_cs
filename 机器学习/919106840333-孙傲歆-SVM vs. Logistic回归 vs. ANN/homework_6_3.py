from libsvm.svmutil import svm_predict, svm_save_model, svm_train
import numpy as np
import pandas as pd
from libsvm.svmutil import *
#width, height, x, y = loadData(DataPath)
x = np.loadtxt("ex4Data/ex4x.dat")
y = np.loadtxt("ex4Data/ex4y.dat")
accuracy=[0,0,0,0,0]
ave_accuracy=0
for j in range(5):
    xtrain=np.delete(x,range(j*16,(j+1)*16),0)
    ytrain=np.delete(y,range(j*16,(j+1)*16),0)
    xtest=x[j*16:(j+1)*16]
    ytest=y[j*16:(j+1)*16]
    model = svm_train(ytrain, xtrain, '-c 1 -t 0 -w1 1')
    label_predict, acc_predict, val_predict = svm_predict(ytest, xtest, model)
    accuracy[j]=acc_predict[0]
    ave_accuracy+=acc_predict[0]
    '''print("- - - - - - - - - - - -")
    print(acc_predict)
    print("- - - - - - - - - - - -")
    print(label_predict)
    print("- - - - - - - - - - - -")
    print(val_predict)'''
for j in range(5):
    print("第%d次准确率:%s" %(j+1,accuracy[j]))
print("平均准确率:", ave_accuracy/5)
