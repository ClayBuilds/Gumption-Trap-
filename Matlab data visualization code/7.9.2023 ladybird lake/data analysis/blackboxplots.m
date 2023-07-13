clear vars;
m = readmatrix('blackbox truncated.txt');
time = m(:,1);
Isol = m(:,11);
Imot = m(:,9);
vbat = m(:,10);
vbat = vbat./1000;
pport = m(:,7);
pstar = m(:,8);
comp = m(:,5);

%f1 = figure;

figure('Name','Power');
tiledlayout(2,1);
nexttile
plot(time,Isol,'Color',[0 0 0]);
hold on;
plot(time,Imot,'Color',[0 0.4470 0.7410]);
title('Current Draw vs Time');
xlabel('Time (seconds)');
ylabel('Current (mA)');
legend('Panel Supply','System Draw');
nexttile
hold off;
plot(time,vbat,'Color',[0 0 0]);
hold on;
title('Battery Voltage Over Time')
xlabel('Time (seconds)');
ylabel('Battery Voltage (mV)');

ahconsumed = trapz(Imot);
ahproduced = trapz(Isol);

%f2 = figure;
figure('name','Pwm');
tiledlayout(2,1);
nexttile
hold on;
plot(time,pport,'Color',[0 0 0]);
plot(time,pstar,'Color',[0 0.4470 0.7410]);
title('Pulse Width Modulation');
legend('Port','Starboard');
xlabel('Time (seconds)');
ylabel('PWM Pulse Width (µS)');
nexttile
hold off;
plot(time,comp,'Color',[0 0 0]);
hold on;
title('Heading over Time');
xlabel('Time (seconds)');
ylabel('Compass Heading (degrees)');
