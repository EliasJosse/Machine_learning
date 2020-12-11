data = load('ex2data1.txt');
X = data(:, [1, 2]); y = data(:, 3);

plotData(X, y);

% Put some labels
hold on;

% Labels and Legend
xlabel('Not Admitted')
ylabel('Admitted')

% Specified in plot order
legend('y = 1', 'y = 0')
hold off;


X =  miniFeature(X(:,1), X(:,2));



initial_theta = zeros(size(X, 2), 1);

% Set regularization parameter lambda to 1 (you should vary this)
lambda = [0, 1, 100];

% Set Options
options = optimset('GradObj', 'on', 'MaxIter', 400);

% Optimize
[theta, J, exit_flag] = ...
	fminunc(@(t)(costFunctionReg(t, X, y, lambda(1))), initial_theta, options);
  
  
plotDecisionBoundary(theta,X,y);


hold on;