%Ganhos
figure(1)
plot(ganhos(:,1),ganhos(:,2))
hold on,plot(ganhos(:,1),ganhos(:,3))
%hold on,plot(ganhos(:,1),ganhos(:,4))
grid on;
xlabel('Tempo(s)');
ylabel('Ganhos');
legend('Saída de Kp','Saída de Ki');
title('Kp = 0.35 ki = 0.05')
ylim([-1,16]);

%Nível/Referencia
figure(2)
plot(NivelRefe(:,1),NivelRefe(:,3))
hold on,plot(NivelRefe(:,1),NivelRefe(:,2))
grid on;
xlabel('Tempo(s)');
ylabel('Nível(cm)');
legend('Nível', 'Referência');
ylim([-1,16]);

%Saturação
figure(3)
plot(Sat(:,1),Sat(:,2),'r')
hold on,plot(Sat(:,1),Sat(:,3),'b')
grid on;
xlabel('Tempo(s)');
ylabel('Tensão(volts)');
legend('Referência', 'Tensão aplicada');
ylim([-5,15]);

