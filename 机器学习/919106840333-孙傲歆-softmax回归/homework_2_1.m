%递归下降法求解logistics回归
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
   for j=1:2
   x(i,j)=(x(i,j)-mean(j))/std(j);
   end
end
temp(1:80,1)=1;
x=[x,temp];
a = 0.1;
theta =[0;0;0];
loss = 0;
old_loss = 0;
temp_loss=[];
for i=1:m
     if (y(i) == 1)
         loss=loss+log(sigmoid(x(i,:)*theta));
     else
         loss=loss+log(1-sigmoid(x(i,:)*theta));
     end
end

while abs(loss-old_loss) > 0.001
    temp =x*theta;
    dew = [0,0,0];
    for i=1:m
        dew=dew+(y(i)-sigmoid(temp(i)))*x(i,:);
    end
    theta = theta+a*dew';
    old_loss = loss;
    loss = 0;
    for i=1:m
        if (y(i) == 1)  
            loss=loss+log(sigmoid(x(i,:)*theta));
        else 
            loss=loss+log(1-sigmoid(x(i,:)*theta));
        end
    end
    disp(-old_loss);
    temp_loss=[temp_loss,-old_loss];
end

plot_x2 =zeros(1,51);
plot_x1 =15:1:65;
for i=15:65
     plot_x2(i-14) = -(theta(3)+theta(1)*((i-mean(1))/std(1)))/theta(2);
     plot_x2(i-14) = plot_x2(i-14)*std(2)+mean(2);
end
hold on;
plot(plot_x1,plot_x2,'-');
figure(2);
plot(temp_loss,'-o');
