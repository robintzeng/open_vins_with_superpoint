### 1.Install dependence
```
git clone https://github.com/catkin/catkin_simple.git
git clone https://github.com/ethz-asl/tensorflow_catkin.git
git clone https://github.com/tradr-project/tensorflow_ros_cpp.git
```
Those three should put in the same folder as openvins (in src)

### catkin build
It will take a long time building the whole project

## The pretrain model should be download from here
https://github.com/rpautrat/SuperPoint/tree/master/pretrained_models<br />
Also you should change this line in the SuperPointTF.h
```
const std::string& graph_fn = "/home/robin/work/src/tensorflow_ros_test/models/sp_v6";
```