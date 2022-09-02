#神经网络算法
import numpy as np
import matplotlib.pyplot as plt

def sigmods(x):
    return 1/(np.exp(-x)+1)


data_x = np.loadtxt("ex4Data/ex4x.dat")
data_y = np.loadtxt("ex4Data/ex4y.dat")
mean = data_x.mean(axis=0)
variance = data_x.std(axis=0)
data_x = (data_x-mean)/variance
data_y = data_y.reshape(-1, 1)          
temp = np.ones(data_y.size)
data_x = np.c_[data_x, temp]

y = np.zeros([data_y.size, 2])
for i in range(data_y.size):
    if data_y[i] == 0:
        y[i][0] = 1
    if data_y[i] == 1:
        y[i][1] = 1
 
learn_rate = 0.05


data_sets = list()
for i in range(data_y.size):
    if i % 8 == 0 and i != 0:
        data_sets.append(data_x[i-8:i, :])
    if i == data_y.size-1:
        data_sets.append(data_x[i-7:i+1, :])
positive_x = data_x[0:40, :]
positive_label = y[0:40, :]
negative_x = data_x[40:80, :]
negative_label = y[40:80, :]
total = 0
for j in range(5):
    x_ = np.r_[np.delete(positive_x, range(j*8, (j+1)*8), 0), np.delete(negative_x, range(j*8, (j+1)*8), 0)]
    y_ = np.r_[np.delete(positive_label, range(j*8, (j+1)*8), 0), np.delete(negative_label, range(j*8, (j+1)*8), 0)]
    test_x = np.r_[data_sets[j], data_sets[j+5]]
    test_label = np.r_[data_y[j*8:(j+1)*8], data_y[(j+5)*8:(j+6)*8]]
    data_x = np.mat(x_)
    temp = np.ones(data_y.size-16)
    weight_input = np.mat(np.random.normal(size=(data_x.shape[1], 7)))
    weight_hidden = np.mat(np.random.normal(size=(8,2)))
    steps = 600
    loss_values = list()
    for i in range(steps):
        hidden_input = data_x*weight_input   
        hidden_out = sigmods(hidden_input)           
        hidden_out_ = np.c_[hidden_out, temp]
        output_input = hidden_out_*weight_hidden
        output = sigmods(output_input)
        loss = 0.5*np.sum(np.multiply(output-y_,  output-y_))
        loss_values.append(loss)
 
        output_error = np.multiply(np.multiply(output-y_, output), 1-output)
        dew_hidden = hidden_out_.T*output_error
        output_error_ = dew_hidden[7]
        weight_hidden_ = np.delete(weight_hidden, 7, axis=0)
        hidden_error = np.multiply(np.multiply(output_error_*weight_hidden_.T, hidden_out), 1-hidden_out)
        dew_input = data_x.T*hidden_error
 
        weight_hidden = weight_hidden-learn_rate*dew_hidden
        weight_input = weight_input-learn_rate*dew_input
 
    plt.plot(loss_values)
    plt.show()
 
    temp = np.ones(test_label.size)
    hidden_input=test_x*weight_input
    hidden_out=sigmods(hidden_input)
    hidden_out_ = np.c_[hidden_out, temp]
    output_input = hidden_out_*weight_hidden
    output =sigmods(output_input)
 
    count = 0
    output = np.array(output)
    for i in range(test_label.size):
        outs = output[i].ravel()
        outs = outs.tolist()
        if int(test_label[i]) == outs.index(max(outs)):
            count = count+1
    print("第%d次准确率:%s" %(j+1,count/test_label.size))
    total = total+count/test_label.size
print("平均准确率:", total/5)