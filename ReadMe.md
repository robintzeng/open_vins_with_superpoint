### 1.Install dependence
```
git clone https://github.com/catkin/catkin_simple.git
git clone https://github.com/ethz-asl/tensorflow_catkin.git
git clone https://github.com/tradr-project/tensorflow_ros_cpp.git
```
Those three should put in the same folder as openvins (in src)

### 2. catkin build
Outside the src folder
```
source 'YOUR ROS PATH'
catkin build -j5
```
It will take a long time building the whole project.
For me, it takes 2 hrs.

### 3. Download the pretrain model
https://github.com/rpautrat/SuperPoint/tree/master/pretrained_models<br />

### Change a line in the SuperPointTF.h
```
const std::string& graph_fn = "/home/robin/work/src/tensorflow_ros_test/models/sp_v6";
```
