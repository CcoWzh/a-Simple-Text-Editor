# Build your own X: a Simple Text Editor

这个库是一个指南，用于介绍如何使用`C++` ，从头开始动手去设计实现一个基于`FLTK`的文本编辑器。

## 使用

代码目录为：

```
E:.
├─include         // FLTK库的头文件
│  └─FL 
├─lib             // FLTK库的静态链接库
└─src             // 主函数
└─CMakeLists.txt  // cmake配置文件
```

使用方式：

```sh
md build
cd build
cmake ..
cmake --build .
# 运行结束后，可以在主目录下看到 bin 文件夹，里面有可运行的二进制文件
```

