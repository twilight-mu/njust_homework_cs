%随机梯度下降法求解softmax回归
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
theta =zeros(3,2);
const=zeros(80,2);
for i=1:80
    const(i,round(y(i)+1)) = 1;
end
old_loss = 0;
temp_loss=[];
loss=get_loss(x,y,theta);


while abs(old_loss-loss) > 0.001
    temp = exp(x*theta);
    tempsum=sum(temp,2);
    for i=1:80
        temp(i,1)=temp(i,1)/tempsum(i);
        temp(i,2)=temp(i,2)/tempsum(i);
    end
    temps =const-temp;
    z = round(rand(1,1)*79)+1;
    tempx = x(z,:);
    temps=temps(z,:);
    theta=theta+a*(temps'*tempx)';
    old_loss = loss;
    loss=get_loss(x,y,theta);
    temp_loss=[temp_loss,-old_loss];
    disp(old_loss);
end

plot_x2 =zeros(1,51);
plot_x1 =15:1:65;
for i=15:65
     plot_x2(i-14) = -(theta(1,1)+theta(3,1)*((i-mean(1))/std(1)))/theta(2,1);
     plot_x2(i-14) = plot_x2(i-14)*std(2)+mean(2);
end
hold on;
plot(plot_x1,plot_x2,'-');

plot_x2 =zeros(1,51);
plot_x1 =15:1:65;
for i=15:65
     plot_x2(i-14) = -(theta(1,2)+theta(3,2)*((i-mean(1))/std(1)))/theta(2,2);
     plot_x2(i-14) = plot_x2(i-14)*std(2)+mean(2);
end
hold on;
plot(plot_x1,plot_x2,'-');

figure(2);
plot(temp_loss,'-o');


