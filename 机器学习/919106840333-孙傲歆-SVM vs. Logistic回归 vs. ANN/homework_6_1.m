clc;
clear;
% xtrainlist=[17:80; 1:16,33:80; 1:32,49:80; 1:48,65:80; 1:64];
% xtestlist=[1:16; 17:32; 33:48; 49:64; 65:80];
xtrainlist=[2:5:80,3:5:80,4:5:80,5:5:80;
            1:5:80,3:5:80,4:5:80,5:5:80;
            1:5:80,2:5:80,4:5:80,5:5:80;
            1:5:80,2:5:80,3:5:80,5:5:80;
            1:5:80,2:5:80,3:5:80,4:5:80
            ];
xtestlist=[1:5:80;2:5:80;3:5:80;4:5:80;5:5:80];
x=load("ex4Data/ex4x.dat");
y=load("ex4Data/ex4y.dat");
xp=x;
yp=y;

[m,n]=size(y);
mean=mean(x);
std=std(x);
for i=1:80
   for z=1:2
   x(i,z)=(x(i,z)-mean(z))/std(z);
   end
end
temp(1:80,1)=1;
x=[x,temp];
accuracy=[];

for p=1:5
a = 0.1;
theta =[0;0;0];
loss = 0;
old_loss = 0;
temp_loss=[];
xtrain=x(xtrainlist(p,:),:);
ytrain=y(xtrainlist(p,:),:);

xtest=x(xtestlist(p,:),:);
ytest=y(xtestlist(p,:),:);

xptrain=xp(xtrainlist(p,:),:);
yptrain=yp(xtrainlist(p,:),:);

xptest=xp(xtestlist(p,:),:);
yptest=yp(xtestlist(p,:),:);
for i=1:64
     if (ytrain(i) == 1)
         loss=loss+log(sigmoid(xtrain(i,:)*theta));
     else
         loss=loss+log(1-sigmoid(xtrain(i,:)*theta));
     end
end

while abs(loss-old_loss) > 0.001
    temp =xtrain*theta;
    dew = [0,0,0];
    z = round(rand(1,5)*63)+1;
    for i=1:5
        dew=dew+(ytrain(z(i))-sigmoid(temp(z(i))))*xtrain(z(i),:);
    end
    theta = theta+a*dew';
    old_loss = loss;
    loss = 0;
    for i=1:64
        if(ytrain(i) == 1)  
            loss=loss+log(sigmoid(xtrain(i,:)*theta));
        else
            loss=loss+log(1-sigmoid(xtrain(i,:)*theta));
        end
    end
    temp_loss=[temp_loss,-old_loss];
end

sumright=0;

for i=1:16
    test=xtest(i,:)*theta;
    if(test>0)
        if(ytest(i)==1)
            sumright=sumright+1;
        end
    else
        if(ytest(i)==0)
            sumright=sumright+1;
        end
    end     
end 

accuracy=[accuracy,sumright/16.0];
    
figure(p);
xlabel('Exam 1 score');
ylabel('Exam 2 score');
for i=1:64
    hold on;
    if(yptrain(i)==1)
        plot(xptrain(i,1),xptrain(i,2),'b+');
    else
        plot(xptrain(i,1),xptrain(i,2),'bo');
    end
end

for i=1:16
    hold on;
    if(yptest(i)==1)
        plot(xptest(i,1),xptest(i,2),'r+');
    else
        plot(xptest(i,1),xptest(i,2),'ro');
    end
end
    
plot_x2 =zeros(1,51);
plot_x1 =15:1:65;
for i=15:65
     plot_x2(i-14) = -(theta(3)+theta(1)*((i-mean(1))/std(1)))/theta(2);
     plot_x2(i-14) = plot_x2(i-14)*std(2)+mean(2);
end
hold on;
plot(plot_x1,plot_x2,'-');
figure(p+5);
hold on;
plot(temp_loss,'-o');

end

ave_accuracy=0;

for i=1:5
    fprintf('第%d次计算准确率为:%f\n',i,accuracy(i));
    ave_accuracy=ave_accuracy+accuracy(i);
end
fprintf('平均准确率为:%f\n',ave_accuracy/5);

