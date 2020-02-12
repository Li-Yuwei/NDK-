# NDK-
Android中NDK的使用，java与c之间的互相传值和代码处理

# 基于AndroidStudio2.2的NDK开发

项目中包含简单的

1.java中图片取反色在c语言中的处理，

2.Base64编码在c语言中实现，java调用

3.c语言中调用java代码的案例

4.c与java之间互相传递值撒



# 关于CMake

  CMake 形式:CLion C/C++编辑器器;AS2.2之后整合了了CLion代码,AS就支持CMake形式的NDK开发

  注意事项：


 1.当Java类中包含了了native的方方法,那么这个类必须写一一个静态初始化块: System.loadLibrary(“库名”）

 1. 如果Java方方法是成员方方法:那么C代码中第二个参数就是 jobject

 1. 如果Java方方法是一个静态的方方法:那么第二个参数jclass

##CMake注意事项

  1. CMakeList.txt 是脚本文文件,需要指定包含哪些源代码;
  1. 可以写一一些条件语句句,实现不不同的代码包含;
  1. 内部的说明add_library 代表编译一个代码库,内部包含了代码库的名称,以及源代码有哪些
