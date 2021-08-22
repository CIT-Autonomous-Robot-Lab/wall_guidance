[![ros-melodic-clang-tidy-review](https://github.com/CIT-Autonomous-Robot-Lab/wall_guidance/actions/workflows/wall_guidance-ci.yaml/badge.svg)](https://github.com/CIT-Autonomous-Robot-Lab/wall_guidance/actions/workflows/wall_guidance-ci.yaml)
# wall_guidance

### How to install

* `catkin build`を使用するためにインストール

```
sudo apt install python-catkin-tools
```

* ワークスペースの構築

```
mkdir -p ~/wall_guidance_ws/src
cd wall_guidance_ws
catkin build
```

* ソースコードのクローン&依存パッケージのインストール

```
cd ~/wall_guidance_ws/src  <--各自、変更をお願いします。
git clone https://github.com/CIT-Autonomous-Robot-Lab/wall_guidance.git
git clone https://github.com/CIT-Autonomous-Robot-Lab/turtlebot3
git clone https://github.com/CIT-Autonomous-Robot-Lab/turtlebot3_simulations.git
git clone https://github.com/CIT-Autonomous-Robot-Lab/turtlebot3_msgs.git
rosdep update
rosdep install -r -y --from-paths --ignore-src ./
```

### How to build

```
catkin build
```

* ターミナル起動時に自動で設定を読み込むように設定(適宜、書き換えお願いします)
```
echo "source ~/wall_guidance_ws/devel/setup.bash" >> ~/.bashrc
echo "export TURTLEBOT3_MODEL=burger" >> ~/.bashrc
source ~/.bashrc
```

### How to run
```
roslaunch turtlebot3_gazebo turtlebot3_house.launch
roslaunch turtlebot3_gazebo turtlebot3_gazebo_rviz.launch
rosrun wall_guidance simple_wall_guidance
```
