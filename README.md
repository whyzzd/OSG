# 项目介绍
## 1.简介
这是基于Qt+OSG的项目，可支持在局域网内多机器上同步进行操作地球(目前仅支持鼠标对球面的点击和缩放操作)，可在球面上绘制点、线、面(可调整线宽)，选择节点可对绘制的图形进行删除、撤销等操作，另外可在球面上展示特效(下雪，下雨，火焰等等)，可在球表面上播放视频，可连接网络上的数据在球面展示。**本项目已经开源，有兴趣的童鞋可对本项目**提出建议**或**提交修改**(bug，优化等)，看到了我会第一时间进行反馈。😊
（目前仅支持Windows系统）

## 2.环境搭建
**开发环境：**
💻Windows10+VS2017+Qt5.12.3
🌏OpenSceneGraph-3.6.5+OSGEarth-2.10+CMake-3.22.1
编译参考教程链接已经放在文末尾，过程可能还有细微的不同，有问题可在评论区讨论。
**注意**：VS编译前后的版本一定要保持一致，不然可能出现各种莫名奇妙的问题

## 3.设计思路

 - 将OSGEarth嵌入到Qt的MainWindow当中，创建停靠窗口，在停靠窗口当中进行做绝大多数的功能，在底下的状态栏中以展示球面的经纬度坐标。
 - 在进行同步时所用的思路是：在球面上进行鼠标操作时，实际上，点击(缩放)并不能第一时间到达球体，而是通过一个中转的服务器程序到达，服务器程序功能目前非常简单，只负责接收和广播，这时，如不考虑丢包的情况，到达每个球体的操作的时序都是一致的。
 - 在使用网络数据时，为了防止没网的时候出现界面卡顿的情况使用了多线程加载。


# 功能演示
 - **主要(核心)功能**

 	1.同步旋转
![同步旋转](https://cdn.jsdelivr.net/gh/whyzzd/pic-Bed/images/2023/20230318010605.gif)

	2.同步绘制点线面
![绘制点线面](https://cdn.jsdelivr.net/gh/whyzzd/pic-Bed/images/2023/20230318010658.gif)

	3.删除撤销重做
![删除、撤销、重做](https://cdn.jsdelivr.net/gh/whyzzd/pic-Bed/images/2023/20230318010722.gif)
 - **其它功能**

	 1.播放视频
![播放视频](https://cdn.jsdelivr.net/gh/whyzzd/pic-Bed/images/2023/20230318010739.gif)
	2.几个特效显示特效
![几个特效](https://cdn.jsdelivr.net/gh/whyzzd/pic-Bed/images/2023/20230318010756.gif)

	3.连接网络数据
![连接网络数据](https://cdn.jsdelivr.net/gh/whyzzd/pic-Bed/images/2023/20230318010836.gif)

# 地址
## 1.CSDN地址

https://blog.csdn.net/qq_39618959/article/details/129606109


## 2.编译OSG参考博文地址
[osgEarth源码编译（Win10+VS2019+OSG3.6.5+osgEarth2.10.0）](https://blog.csdn.net/Alexabc3000/article/details/118882997)
[OSG源码编译](https://www.codenong.com/cs106744269/)
[OSG教程：：基于VS2013的64位OSGEarth编译](https://www.pianshen.com/article/7226767336/)
[osg、osgearth教程VS2017_aspiretop的博客-程序员资料](https://www.i4k.xyz/article/ljjjjjjjjjjj/113389229)
*再次提醒：最后使用的VS版本一定要和编译出来的库版本保持一致*
