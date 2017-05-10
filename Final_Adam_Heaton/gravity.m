clear all
close all

fid1 = fopen('out.txt');
% fast1 = textscan(fid1, '%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f');
fast1 = textscan(fid1, '%f\t%f\t%f');

steps = 100000;
bodies = 10;
X = 'working';
Y = '---------';

for i = 0:steps-2
    for j=1:bodies
        Position(i+1,2*j-1) = fast1{2}(i*11 + j);
        Position(i+1,2*j) = fast1{3}(i*11 + j);
    end
    disp(X);
    energy(i+1) = fast1{1}(i*11 + 11);
    KE(i+1) = fast1{2}(i*11 + 11);
    PE(i+1) = fast1{3}(i*11 + 11);
    disp(Y);
end

figure(1);
hold on
title('Total Energy')
xlabel('Time (s)')
ylabel('Energy')

plot(0:steps-2, energy(1:steps-1), '--r')
plot(0:steps-2, KE(1:steps-1), ':m')
plot(0:steps-2, PE(1:steps-1), '-b')
legend('Total','KE','PE')

figure(2);
hold on
title('Potential Energy')
xlabel('Time (s)')
ylabel('Potential')

% plot(0:99998, energy(1:99999), '*r')
% plot(0:steps-2, KE(1:steps-1), '-b')
plot(0:99998, PE(1:99999), '-b')


% figure(3);
% hold on
% title('Position')
% xlabel('x (meters)')
% ylabel('y (meters)')
% xlim([-5*10^7, 5*10^7]);
% ylim([-5*10^7, 5*10^7]);
% 
% plot(particle1(:,1), particle1(:,2), '*r')
% plot(particle2(:,1), particle2(:,2), '-b')
% legend('Body 1', 'Body 2')

figure(3);
hold on
title('Position')
xlabel('x (meters)')
ylabel('y (meters)')
% xlim([-5*10^7, 5*10^7]);
% ylim([-5*10^7, 5*10^7]);

for j=1:bodies
    plot(Position(1,2*j-1),Position(1,2*j),'*r');
    plot(Position(2:end,2*j-1),Position(2:end,2*j),'--b');
end