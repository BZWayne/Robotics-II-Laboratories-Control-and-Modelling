data_size = 5000;
[XTrain, YTrain] = create_dataset_fk(data_size);

XTrain = reshape(XTrain', [1, 1, size(XTrain,2),size(XTrain,1)]);


nFeatures = 5;
numClasses = 3;

layers = [ ...
    imageInputLayer([1 1 nFeatures])
    fullyConnectedLayer(2048)
    leakyReluLayer
    fullyConnectedLayer(1024)
    leakyReluLayer
    fullyConnectedLayer(512)
    leakyReluLayer
    fullyConnectedLayer(256)
    leakyReluLayer
    fullyConnectedLayer(128)
    reluLayer
    fullyConnectedLayer(numClasses)  
    regressionLayer  
    ]

maxEpochs = 25;
miniBatchSize = 250;

options = trainingOptions('adam', ...
    'ExecutionEnvironment','cpu', ...
    'GradientThreshold',1, ...
    'MaxEpochs',maxEpochs, ...
    'MiniBatchSize',miniBatchSize, ...
    'SequenceLength','longest', ...
    'Shuffle','never', ...
    'Verbose',0, ...
    'Plots','training-progress');


net_fk = trainNetwork(XTrain, YTrain,layers,options);


save net_fk