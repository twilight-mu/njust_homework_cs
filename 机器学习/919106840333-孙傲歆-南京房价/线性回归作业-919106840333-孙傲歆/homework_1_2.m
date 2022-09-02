clc;
clear;
theta_0=1;
theta_1=1;
x=[2000;2001;2002;2003;2004;2005;2006;2007;2008;2009;2010;2011;2012;2013];
y=[2.000;2.500;2.900;3.147;4.515;4.903;5.365;5.704;6.853;7.971;8.561;10.000;11.280;12.900];
a=0.1;
mean=mean(x);
std=std(x);
for i=1:14
   x(i)=(x(i)-mean)/std; 
end
old_loss=0;
loss=0;
for i=1:14
    loss=loss+(x(i)*theta_1+theta_0-y(i))*(x(i)*theta_1+theta_0-y(i));
end 
sum=0;
while (abs(loss - old_loss) > 0.00001)
    dew=0;
    for i=1:14                
        dew= dew+(x(i)*theta_1-y(i))*x(i);
    end
    theta_1=theta_1-dew*a;
    dew=0;
    for i=1:14                
        dew=dew+(x(i)*theta_1+theta_0-y(i));
    end
    theta_0=theta_0-dew*a;
    old_loss=loss;
    loss=0;
    for i=1:14
        loss=loss+(x(i)*theta_1+theta_0-y(i))*(x(i)*theta_1+theta_0-y(i));
    end
    sum=sum+1;
end
Y_2014=((2014-mean)/std)*theta_1+theta_0;
disp("梯度下降法求线性回归");
disp("迭代次数"+sum+"次");
disp("2014年房价为:"+Y_2014);
figure(1);
plot(x,y','bo');
xlabel('年');
ylabel('房价');
title('南京房价预测');
hold on;
x2=[x;(2014-mean)/std];
y2=[x*theta_1+theta_0;Y_2014];
plot(x2,y2,'-');
hold on;
plot((2014-mean)/std,Y_2014,'ro');