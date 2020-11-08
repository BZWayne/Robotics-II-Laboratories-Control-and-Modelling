# Lab 7
## The goal of this lab is to decrease the error, so that end-effector will reach the point. Before untuned NN show 45.64%. The tuned accuracy is 26.06%. This happened by changing the value 512-256-128 with maxEpochs 20 and miniBatchSize 200.
### Initial Conditions:
s we can observe, the error is 45.61%. 
![alt text](https://github.com/BZWayne/Robotics-II-Laboratory-Control-and-Modelling/blob/master/laboratory_7/screenshots/init.png) 
The training of it looks as following:
![alt text](https://github.com/BZWayne/Robotics-II-Laboratory-Control-and-Modelling/blob/master/laboratory_7/screenshots/init_train.png)

### The Best Tuned value:
The architecture is 512-256-128 with maxEpochs 20 and miniBatchSize 200, the error is 26.06%:
![alt text](https://github.com/BZWayne/Robotics-II-Laboratory-Control-and-Modelling/blob/master/laboratory_7/screenshots/512-256-128-64.png)
The training of it looks as following:
![alt text](https://github.com/BZWayne/Robotics-II-Laboratory-Control-and-Modelling/blob/master/laboratory_7/screenshots/512-256-128-64_train.png)
