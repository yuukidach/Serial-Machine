# Serial Machine

[![Readme](https://img.shields.io/badge/Language-English-brightgreen)](./README.md) [![License](https://img.shields.io/badge/License-GPLv3-yellowgreen)](./LICENSE)

串口工具，主要是针对 MacOS 开发。因为 MacOS 上找不到好用的串口工具，APP Store 里收费也感觉一般般，就自己实现了一下

## 使用

打开串口工具，在左侧进行配置

![App Main GUI](./res/app_gui.png)

## 编译

如果你想在 MacOS 上自己编译打包的话，记得在使用 `macdeployqt` 的时候加上 `-qmldir` 选项，例如：

``` zsh
macdeployqt Serial-Machine-Quick.app -qmldir=<path to root qml folder> -no-strip -always-overwrite [-dmg]
```
