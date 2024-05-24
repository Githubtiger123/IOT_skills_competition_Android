# 新大陆物联网竞赛-Android开发-导入JAR包与添加依赖



## 一、工具准备

- ​    Android studio 3.2
- ​    物联网竞赛JAR包

## 二、导入JAR

### 1.打开Android studio，并新建工程项目。

![img](新大陆物联网竞赛-Android开发-导入JAR包与添加依赖.assets/6ea3f4a0abc14df7b81aeb3425596230-1670460452870.png)



### 2.以我们所用到的SerialPort包为例，打开其存放的目录。 

![img](新大陆物联网竞赛-Android开发-导入JAR包与添加依赖.assets/d6848a4a457c4daca6f7f8e724d245b5.png)



### 3.选中armeabi文件夹与ioSerialPort.jar文件并复制。

![img](新大陆物联网竞赛-Android开发-导入JAR包与添加依赖.assets/16ee469750cf4c118e57bd0f7b0019a9.png)



### 4.将Android切换到Project视图。

![img](新大陆物联网竞赛-Android开发-导入JAR包与添加依赖.assets/e7d72e2ee9bf4bd2b027c26ec9b4da85.png)



### 5.按下图选中libs目录,并将所复制的jar包复制进入。

![img](新大陆物联网竞赛-Android开发-导入JAR包与添加依赖.assets/2e4d7ca1a268485aab3f59fe8196d3f1.png)



### 6.打开libs目录，选中jar文件，右键Add As Library，随后点击OK。

![img](新大陆物联网竞赛-Android开发-导入JAR包与添加依赖.assets/c6c925339f064b208e991789cfc7cd2c.png)



### 至此，JAR的导入已经完成。



## 三、依赖添加

​    由于架构不同，我们常需要在依赖中添加一些代码。

​    打开图中所示的build.gradle文件：

![img](新大陆物联网竞赛-Android开发-导入JAR包与添加依赖.assets/7caf848257934428bfaccaa1dd0019f3.png)

###     添加如下两端代码：

```java
ndk{
    abiFilters 'armeabi'
}
```

```java
sourceSets{
    main{
        jniLibs.srcDirs=['libs']
    }
}
```

###     随后执行Sync Now

![img](新大陆物联网竞赛-Android开发-导入JAR包与添加依赖.assets/443584495eb64a7091ea9f7a17650bb9.png)

​     可以看到编译通过，此时我们已经可以调用JAR包中的方法啦！