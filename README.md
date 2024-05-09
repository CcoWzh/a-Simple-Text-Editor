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

运行后的截图为：

## 项目说明

这个项目是根据**FLTK**库官方说明文档构建的C++项目，因此对于初次使用C++编写工程项目、学习C++语法、学习如何进行GUI编程等人员有较大帮助。通过本项目，我们要完成一个文本编辑器：

- 提供菜单栏和功能选项
- 编辑单个文本文件
- 加载（`open`）文件并编辑
- 保存（`save`）文件
- 具备`剪切/复制/删除/粘贴`等功能
- 具备`搜索`和`替换`功能
- 跟踪文件的更改时间

## 详细设计

待更新。。。





## 参考

- [FLTK 1.3.9: Designing a Simple Text Editor](https://www.fltk.org/doc-1.3/editor.html#editor_goals)，FLTK的官方案例说明

