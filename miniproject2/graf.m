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