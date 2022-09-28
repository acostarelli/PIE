a = 134.391;
b = -0.00427218;
t = @(x) a * exp(b * x);

figure
hold on

cal = [440 20 ; 360 30 ; 280 40 ; 230 50 ; 190 60];
xs = 0:1024;
ys = t(xs);

plot(cal(:,2), cal(:,1), 'o')
plot(ys, xs)

hold off
xlim([0 70])
ylim([0 1024])
xlabel('Distance (cm)')
ylabel('Sensor reading')
legend({'Calibration data'})
title('Calibration Plot')

figure
hold on

test = [410 25 ; 320 35 ; 250 45 ; 210 55];

plot(test(:,1), test(:,2), 'o')
plot(test(:,1), t(test(:,1)), 'x')

hold off
xlim([0 1024])
ylim([0 70])
xlabel('Sensor reading')
ylabel('Distance (cm)')
legend({'Test data', 'Transfer function'})
title('Error Plot')