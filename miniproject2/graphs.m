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
legend({'Calibration data', 'Transfer function'})
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
legend({'Trasnfer function', 'Test data'})
title('Error Plot')

%{
clear

[X,Y] = meshgrid(linspace(0, 100), linspace(0, 100));
X = X(:)';
Y = Y(:)';
P = [X ; Y];

k = randperm(length(P), 7500);
X(:, k) = [];
Y(:, k) = [];
P(:, k) = [];
P = P + rand(size(P)) * 20;
Q = rand([2 30]) * 100;

left_out  = 4 * (X - 10);
left_in   = 4 * (X - 25);
middle    = 50;
right_in  = -4 * (X - 75);
right_out = -4 * (X - 90);

left  = Y < left_out  & Y > left_in;
right = Y < right_out & Y > right_in;
tall  = Y < left_out & Y < right_out & Y > middle;


inside = left | right | tall;
figure
hold on

scatter(P(1, inside), P(2, inside), 'filled', 'MarkerFaceColor', 'red')
scatter(Q(1, :), Q(2, :),  'filled', 'MarkerFaceColor', 'red')

hold off

%}