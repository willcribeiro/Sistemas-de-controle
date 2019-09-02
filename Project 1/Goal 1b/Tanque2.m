clc
clear
h = [5:5:25];
tensao = [0.839 1.556 2.304 3.007 3.719];
plot(tensao,h,'rx')
n = 5;
x = sum(tensao);
x2 = sum(tensao.^2);
y = sum(h);
xy = sum(h.*tensao);

matx = [n, x; x, x2];
maty = [y; xy];
inv = inv(matx);

coe = inv*(maty);


z = 0:0.1:4;
k = coe(2)*z + coe(1);
title('Tanque 02')
hold on,plot(z,k)
legend('Tensão Média')
grid on;
ylabel('Altura(cm)')
xlabel('Tensão(Volt)')