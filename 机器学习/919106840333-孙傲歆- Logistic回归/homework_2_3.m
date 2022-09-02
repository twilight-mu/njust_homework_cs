clc;
clear;
x=load("ex4Data/ex4x.dat");
y=load("ex4Data/ex4y.dat");
[m,n]=size(y);
figure(1);
xlabel('Exam 1 score');
ylabel('Exam 2 score');
for i=1:m
    hold on;
    if(y(i)==1)
        plot(x(i,1),x(i,2),'b+');
    else
        plot(x(i,1),x(i,2),'bo');
    end
end
mean=mean(x);
std=std(x);
for i=1:m
   for z=1:2
   x(i,z)=(x(i,z)-mean(z))/std(z);
   end
end
temp(1:80,1)=1;
x=[temp,x];
a = 0.1;
theta =[0;0;0];
loss = 0;
old_loss = 0;
temp_loss=[];
temp=-(x*theta);
result1(1:80,1)=0;
for i=1:m
    result1(i)=sigmoid(temp(i));
end
loss = get_loss(y,result1);

while (abs(old_loss-loss) > 0.000001)
    %h = 1.0/(1+np.exp(-(data_x*theda)))
    temp=-(x*theta);
    h(1:80,1)=0;
    for i=1:m
        h(i)=sigmoid(temp(i));
    end
    J = (1.0/m).*(x'*(h-y));
    temp=h.*(1-h);
    result2(80:80,1)=0;
    for i=1:m
        result2(i,i)=temp(i);
    end
    H = (1.0/m).*(x'*result2*x);
    theta = theta-inv(H)*J;
    old_loss = loss;
    temp_loss=[temp_loss,old_loss];
    loss = 0;
    loss = get_loss(y,h);
    
end

plot_x2 =zeros(1,51);
plot_x1 =15:1:65;
for i=15:65
     plot_x2(i-14) = -(theta(1)+theta(3)*((i-mean(1))/std(1)))/theta(2);
     plot_x2(i-14) = plot_x2(i-14)*std(2)+mean(2);
end
hold on;
plot(plot_x1,plot_x2,'-');
figure(2);
plot(temp_loss,'-o');

