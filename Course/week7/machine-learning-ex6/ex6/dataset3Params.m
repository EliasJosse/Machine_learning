function [C, sigma] = dataset3Params(X, y, Xval, yval, x1, x2)
%DATASET3PARAMS returns your choice of C and sigma for Part 3 of the exercise
%where you select the optimal (C, sigma) learning parameters to use for SVM
%with RBF kernel
%   [C, sigma] = DATASET3PARAMS(X, y, Xval, yval) returns your choice of C and 
%   sigma. You should complete this function to return the optimal C and 
%   sigma based on a cross-validation set.
%

% You need to return the following variables correctly.
C = 1;
sigma = 0.3;

% ====================== YOUR CODE HERE ======================
% Instructions: Fill in this function to return the optimal C and sigma
%               learning parameters found using the cross validation set.
%               You can use svmPredict to predict the labels on the cross
%               validation set. For example, 
%                   predictions = svmPredict(model, Xval);
%               will return the predictions on the cross validation set.
%
%  Note: You can compute the prediction error using 
%        mean(double(predictions ~= yval))
%
c_list = [0.01, 0.03, 0.1,0.3,1,3,10,30];

%c_list = [0.01, 0.03];
res = zeros(length(c_list)^2,3);
largeIndex = 0;
largeVal = 0;

for c = 1:length(c_list)
  for sig = 1:length(c_list)
    index = (c-1)*length(c_list) + sig;
    
    cVal = c_list(c);
    sigVal = c_list(sig);
    
    res(index,1) = cVal;  
    res(index,2) = sigVal;
    
    model = svmTrain(X, y, cVal, @(x1, x2) gaussianKernel(x1, x2, sigVal));
    predictions = svmPredict(model, Xval);
    val = mean(double(predictions == yval));
    
    res(index,3)  = val;
    if(val > largeVal)
      largeVal = val;
      largeIndex = index;
    endif
    
    
  endfor
endfor


C = res(largeIndex,1);
sigma = res(largeIndex,2); 

% =========================================================================

end
