# JointTG

This repository contains the implementation of "<i>Joint Texture and Geometry Optimization for RGB-D Reconstruction (CVPR2020)</i>" based on [Open3D](https://github.com/intel-isl/Open3D). Due to the agreement with other company, some parts can only be released in the form of .so files. More information and the paper can be found on [our group website](http://graphvision.whu.edu.cn/) and [Qingan's homepage](https://yanqingan.github.io/).

# Publication
If you find this code useful for your research, please cite our work:

> Yanping Fu, Qingan Yan, Jie Liao, Chunxia Xiao. <i>Joint Texture and Geometry Optimization for RGB-D Reconstruction</i>. In CVPR. 2020.

<pre><code>@inproceedings{fu2020joint,
  title={Joint Texture and Geometry Optimization for RGB-D Reconstruction},
  author={Fu, Yanping and Yan, Qingan and Liao, Jie and Xiao, Chunxia},
  booktitle={Proceedings of the IEEE/CVF Conference on Computer Vision and Pattern Recognition},
  pages={5950--5959},
  year={2020}
}</code></pre>

# How to use

## 1. Run
To test our algorithm. run G2LTex in command line:
```
./bin/JointTG [IAMGESDIR] [PLY] [TRAJECTORY] 
```
Params explanation:
```
-`IAMGESDIR`:The texture image directory, include rgb images, depth images.
-`PLY`: The reconstructed model for texture mapping.
-`TRAJECTORY`:  The camera pose of each key-frame.
```

The parameters of the camera and the system can be set in the config file.
```
Config/config.yml
```

How to install and run this code.
```
git clone https://github.com/fdp0525/JointTG.git
cd JointTG/bin
./JointTG ./bricks/images ./bricks/bricks-fusion.ply ./bricks/traj.log
```
We need to modify the configuration file ```config.yml``` before running the other datasets.

## 2. Dependencies
The code has following prerequisites:
- ubuntu 16.04
- gcc (5.4.0)
- OpenCV (2.4.10)
- Eigen (>3.0)
- Boost (1.65)

