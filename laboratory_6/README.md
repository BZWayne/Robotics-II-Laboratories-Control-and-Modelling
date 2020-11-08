# Lab 6
### Initial Conditions:
As we can observe, the error is 28.9%. 
![alt text](https://github.com/BZWayne/Robotics-II-Laboratory-Control-and-Modelling/blob/master/laboratory_6/Screenshots/init_error.png) 
The training of it looks as following:
![alt text](https://github.com/BZWayne/Robotics-II-Laboratory-Control-and-Modelling/blob/master/laboratory_6/Screenshots/init_train.png)

### 2048-1024-512-256-128 architecture:
It is 2048-1024-512-256-128 architecture, the error is 9.04%:
![alt text](https://github.com/BZWayne/Robotics-II-Laboratory-Control-and-Modelling/blob/master/laboratory_6/Screenshots/2048-1024-512-256-128_error.png)
The training of it looks as following:
![alt text](https://github.com/BZWayne/Robotics-II-Laboratory-Control-and-Modelling/blob/master/laboratory_6/Screenshots/2048-1024-512-256-128_train.png)

### Changing some Relu Layers to LeakyReluLayers
Some relu layers of 2048-1024-512-256-128 changed to leakyReluLayers, so the error is 8.91%:
![alt text](https://github.com/BZWayne/Robotics-II-Laboratory-Control-and-Modelling/blob/master/laboratory_6/Screenshots/some_leakyReluLayers_error.png)
The training of it looks as following:
![alt text](https://github.com/BZWayne/Robotics-II-Laboratory-Control-and-Modelling/blob/master/laboratory_6/Screenshots/some_leakyReluLayers_train.png)

### The Best Tuned value 
From the above architecture, maxEpochs changed to 15 and miniBatchSize is 150, so the error is 4.92%:
![alt text](https://github.com/BZWayne/Robotics-II-Laboratory-Control-and-Modelling/blob/master/laboratory_6/Screenshots/error_4.92.png)
The training of it looks as following:
![alt text](https://github.com/BZWayne/Robotics-II-Laboratory-Control-and-Modelling/blob/master/laboratory_6/Screenshots/error4.92_train.png)
