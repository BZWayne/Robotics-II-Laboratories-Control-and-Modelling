import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import Circle
from scipy.interpolate import CubicSpline
import math

# obstacles = np.array([20, 90],
#                     [40, 40],
#                     [70, 50],
#                     [80, 10]
#                     )

x_obstacles = [20, 30, 70, 90]
y_obstacles = [90, 50, 30, 10]
radius = 8
sensor_radius = 2

x_start = 7
y_start = 7    
theta_start = np.pi/4

dt = 0.1
animation = True

length = 12  
width = 6 
bcw = 6  
lenWheel = 2  
widWheel = 2 
tread = 5   

class Config():

    def __init__(self):
        self.circle = 0 
        # 0 is circle, 1 is rectangle 

def move(x_goal, y_goal, theta_goal):

    config = Config()
    x = x_start 
    y = y_start
    theta = theta_start

    x_diff = x_goal - x
    y_diff = y_goal - y
    vl = 5
    vr = 5

    dis = np.hypot(x_diff, y_diff)
    l = width+(2*widWheel)

    while dis > 0.01:

        if vr == vl:
            vr = vl + 0.000001

        w = (vr - vl)/l
        R = (l/2)*(vr+vl)/(vr-vl)

        ICCx = x - R*np.sin(theta)
        ICCy = y + R*np.cos(theta)

        [x_robt, y_robt] = [np.cos(w*dt)*(x-ICCx) - np.sin(w*dt)*(y-ICCy) + ICCx, np.sin(w*dt)*(x-ICCx) + np.cos(w*dt)*(y-ICCy) + ICCy]
        theta_robt = theta + w*dt

        x = x_robt
        y = y_robt
        theta = theta_robt
        dis = np.hypot(x_robt, y_robt)

        leftSensor = [x + width/2, y + length/2]
        rightSensor = [x + width/2, y - length/2]
        
        left_sensor_posX = x_goal - leftSensor[0]
        left_sensor_posY = y_goal - leftSensor[1]
        right_sensor_posX = x_goal - rightSensor[0]
        right_sensor_posY = y_goal - rightSensor[1]

        distl = np.hypot(left_sensor_posX, left_sensor_posY)
        distr = np.hypot(right_sensor_posX, right_sensor_posY)

        if config.circle == 0:
            config.cirle = 1
            templ = distl
            tempr = distr
        
        tl = distl/templ
        tr = distr/tempr

        for i in range(len(x_obstacles)):
            leftX = x_obstacles[i] - leftSensor[0]
            leftY = y_obstacles[i] - leftSensor[1]
            rightX = x_obstacles[i] - rightSensor[0]
            rightY = y_obstacles[i] - rightSensor[1]
            LEFT = np.hypot(leftX, leftY)
            RIGHT = np.hypot(rightX, rightY)

            if LEFT <= radius:
                vr = -vr
            if RIGHT < radius:
                vl = -vl

        if leftSensor[0] >= 100 or leftSensor[1] >= 100 or rightSensor[0] <= 0 or rightSensor[1] <= 0:
            vr = -vr
        
        if leftSensor[0] >= 100 or leftSensor[1] >= 100 or rightSensor[0] < 0 or rightSensor[1] <= 0:
            vl = -vl

        if animation:
            plt.cla()  
            obstacles()
            plt.plot([x, x_goal],[y, y_goal], 'go')               
            robot(x, y, theta)  

def obstacles():
    #obstacles
    o1 = circ(x_obstacles[0], y_obstacles[0], radius)
    o2 = circ(x_obstacles[1], y_obstacles[1], radius)        
    o3 = circ(x_obstacles[2], y_obstacles[2], radius)
    o4 = circ(x_obstacles[3], y_obstacles[3], radius)

    plt.gca().add_patch(o1)
    plt.gca().add_patch(o2)
    plt.gca().add_patch(o3)                      
    plt.gca().add_patch(o4)
    
def robot(x, y, theta):
    chassis = np.matrix([[-bcw, (length - bcw), (length - bcw), -bcw, -bcw],
                         [width / 2, width / 2, - width / 2, -width / 2, width / 2]])

    r_wheel = np.matrix([[-lenWheel, lenWheel, lenWheel, -lenWheel, -lenWheel],
                        [-widWheel - tread, -widWheel - tread, widWheel - tread, widWheel - tread, -widWheel - tread]])
    l_wheel = np.copy(r_wheel)
    l_wheel[1, :] *= -1

    r_wheel = (r_wheel.T * rotation(theta)).T
    l_wheel = (l_wheel.T * rotation(theta)).T
    chassis = (chassis.T * rotation(theta)).T

    chassis[0, :] += x
    chassis[1, :] += y
    r_wheel[0, :] += x
    r_wheel[1, :] += y
    l_wheel[0, :] += x
    l_wheel[1, :] += y

    plt.plot(np.array(chassis[0, :]).flatten(), np.array(chassis[1, :]).flatten(), "-k")
    plt.plot(np.array(r_wheel[0, :]).flatten(), np.array(r_wheel[1, :]).flatten(), "-k")
    plt.plot(np.array(l_wheel[0, :]).flatten(), np.array(l_wheel[1, :]).flatten(), "-k")
    plt.xlim(0,100)
    plt.ylim(0,100)
    plt.plot(x, y, "*")
    plt.gcf().canvas.mpl_connect('key_release_event', lambda event: [exit(0) if event.key == 'escape' else None])
    plt.pause(dt)

def rotation(theta):
    rot = np.matrix([[math.cos(theta), math.sin(theta)],
                    [-math.sin(theta), math.cos(theta)]])
    return rot

def circ(x, y, rad):
    return Circle((x, y), rad)

def main():
    x_goal = 90
    y_goal = 90      
    theta_goal = np.pi/3

    move(x_goal, y_goal, theta_goal)

if __name__ == '__main__':
    main()