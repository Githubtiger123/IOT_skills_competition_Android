# 新大陆安卓MQTT通信

## 一、搭建MQTT服务器



#### 1.在EMQX官网下载

![image-20221214214256721](新大陆安卓MQTT通信.assets/image-20221214214256721.png)

![image-20221214214408022](新大陆安卓MQTT通信.assets/image-20221214214408022.png)

#### 2.下载解压后,找到bin目录

按下徽标加s搜索CDM,右键打开文件位置

![image-20221214214547408](新大陆安卓MQTT通信.assets/image-20221214214547408.png)

复制程序到bin目录

![image-20221214214621616](新大陆安卓MQTT通信.assets/image-20221214214621616.png)

#### 3.在bin目录下运行

输入

```java
emqx console
```

后出现下图后

![image-20221214214740158](新大陆安卓MQTT通信.assets/image-20221214214740158.png)

#### 4.在浏览器输入127.0.0.1端口1883

进入自己搭建的MQTT服务器

![image-20221214214859231](新大陆安卓MQTT通信.assets/image-20221214214859231.png)

默认用户admin

默认密码public



#### 5.更改语言为中文

![image-20221214214943488](新大陆安卓MQTT通信.assets/image-20221214214943488.png)



#### 6.说明



1. MQTT IP为本机IP
2. MQTT 用户名为注册时的用户名
3. MQTT 密码为注册时的密码

打开问题分析--->WebSocket 客户端

![image-20221214215414312](新大陆安卓MQTT通信.assets/image-20221214215414312.png)

可以添加订阅主题和发布主题以及查看订阅内容和发布内容



## 二、打开MQTT.fx

#### 1.填写登陆参数

![image-20221214215602463](新大陆安卓MQTT通信.assets/image-20221214215602463.png)

Broker Address 本机IP或者127.0.0.1

Broker Port1883

ClientID 随机生成

![image-20221214215705886](新大陆安卓MQTT通信.assets/image-20221214215705886.png)

用户名和密码是注册登陆的

#### 2.测试订阅功能

![image-20221214220250584](新大陆安卓MQTT通信.assets/image-20221214220250584.png)

![image-20221214220438983](新大陆安卓MQTT通信.assets/image-20221214220438983.png)

#### 3.测试发布功能



![image-20221214220648305](新大陆安卓MQTT通信.assets/image-20221214220648305.png)



![image-20221214220851325](新大陆安卓MQTT通信.assets/image-20221214220851325.png)

![image-20221214220910751](新大陆安卓MQTT通信.assets/image-20221214220910751.png)



## 三、通过安卓实现MQTT