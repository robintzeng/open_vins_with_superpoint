### 1. Get the libtorch  
```
wget https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-1.2.0.zip
```
### 2. Change the path in the CmakeList in both ov_msckf and ov_core folder to the place of your libtorch lib 
```
set(CMAKE_PREFIX_PATH /YOUR LIBTORCH/libtorch2)	
set(TORCH_LIBRARIES "/YOUR LIBTORCH/libtorch2/lib")
```
### 3. Change the path of the rosbag in /ov_msckf/launch/tutorial.launch
```
<param name="path_bag"    type="string" value="/home/robin/vin_data/V1_01_easy.bag" />
```
### 4. source and run
Outside the src folder
```
source devel/setup.bash
roslaunch ov_msckf tutorial.launch
```


