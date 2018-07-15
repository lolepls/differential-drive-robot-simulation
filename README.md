# differential-drive-robot-simulation

Authors: Gioele Mombelli - Daniele Nicolò

--------
OVERVIEW
--------

Simulation of a robot with **differential drive kinematics**, equipped with an **encoder** in order to get angular velocity of left and right wheel at a frequency of 20Hz. The robot can be moved around by the user in GazeboSim environment using keyboard.

The robot is modeled after a real machine which we have studied in order to get an accurate approximation of its dynamic and inertial properties.

-----------------------------------
DESCRIPTION OF INCLUDED FILES
-----------------------------------

The project consists of two principal files: **robot.world** and **encoder_plugin.cc**.

**robot.world**: Gazebo .world file that contains the physic model of the robot. When loaded in Gazebo spawns the robot at the origin of the reference frame.

**encoder_plugin.cc**: Plugin for Gazebo written in C++. It's an encoder that provides angular velocity of left and right wheel at a frequency of 20Hz. This frequency is relative to the simulation time (i.e. velocity is measured every 0.05 seconds of SimTime and not real time), because we wanted to simulate the encoder as if it were a real physical element of the robot.

"Build" folder is also provided, and it contains already built files of the encoder. However, you can build your own version using CMake.

----------------
HOW TO PERFORM THE SIMULATION
---------------

REQUIREMENTS:

- Ubuntu operating system;
- GazeboSim;
- ROS (Robot Operating System);
- Turtlebot3.

------

1 - Open the terminal and launch $roscore;
2 - Open another terminal and type the following line:

`$export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:~/yourpath/build`

3 - Run Gazebo as a ROS node and load the robot's model with:

`$rosrun gazebo_ros gazebo -u ~/yourpath/robot.world`

4 - Once the robot is loaded, start the simulation by pressing "play". On the terminal, you should see the plugin starting its measurements.
5 - To control your robot with the keyboard you should type the following line:

`$roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch`

6 - Enjoy!

