Modified from [raulmur's ORB_SLAM](https://github.com/raulmur/ORB_SLAM)

Follow ROS Indigo installation intructions to build and install from source.

To build, follow build instructions in the link above. Must build both folders in Thirdparty with `cmake .. -DCMAKE_BUILD_TYPE=Release` command. Then build the toplevel folder with `cmake .. -DROS_BUILD_TYPE=Release`.

Source code is in the src folder. Must rebuild the toplevel folder each time a change is made to the source code.
