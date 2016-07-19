%% 最速下降法图示
% 设置步长为0.1，f_change为改变前后的y值变化，仅设置了一个退出条件。
syms x;f=x^2;
step=0.1;x=2;k=0;         %设置步长,初始值,迭代记录数
f_change=x^2;              %初始化差值
f_current=x^2;              %计算当前函数值
ezplot(@(x,f)f-x^2)        %画出函数图像
axis([-2,2,-0.2,3])            %固定坐标轴
hold on
while f_change>0.000000001                %设置条件，两次计算的值之差小于某个数，跳出循环
    x=x-step*2*x;                         %-2*x为梯度反方向，step为步长，！最速下降法！
    f_change = f_current - x^2;           %计算两次函数值之差
    f_current = x^2 ;                     %重新计算当前的函数值
    plot(x,f_current,'ro','markersize',7) %标记当前的位置
    drawnow;pause(0.2);
    k=k+1;
end
hold off
fprintf('在迭代%d次后找到函数最小值为%e，对应的x值为%e\n',k,x^2,x)