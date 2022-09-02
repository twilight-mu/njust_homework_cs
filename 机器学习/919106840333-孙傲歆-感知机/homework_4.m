%SGD感知机算法
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
a = 0.5;
w=[0;0];
b=1;
yy=zeros(80,1);
for i=1:80
    if(y(i)==0)
        yy(i)=-1;
    else
        yy(i)=1;
    end
end
old_loss = 0;
loss=get_loss(x,yy,w,b);
temp_loss=[];
% for i=1:7000
%      for j=1:80
%          if((yy(j)*(w*x(j)+b))<=0)
%              w=w+a*yy(j)*x(j);
%              b=b+a*yy(j);
%          end
%      end
% end
while abs(old_loss-loss) > 0.0001

    tempnum=[];
     for j=1:80
         if((yy(j)*(w*x(j)+b))<=0)
            tempnum=[tempnum,j];
         end
     end
    k=randperm(length(tempnum));
    z=k(1:5);
    for i=1:5
        w=w+a*yy(z(i))*x(z(i));
        b=b+a*yy(z(i));
    end
    old_loss = loss;
    loss=get_loss(x,yy,w,b);
    temp_loss=[temp_loss,old_loss];
    %disp(old_loss);
end
theta=[w;b];

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

disp(theta);

