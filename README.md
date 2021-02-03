# MatrixFeatures
Extract Matrix features

## 文件与目录
文件与目录的含义为：
- `doc/`：该目录下包括一个 `features.pdf`文件，里面记录了需要提取的特征
- `sparsemat.cpp sparsemat.h`：定义基础数据结构的程序，包括稀疏矩阵基类，派生类`COO`和派生类`CSR`
- `features.cpp features.h`：基于稀疏矩阵类，定义的特征提取类程序
- `base.h`：定义了全局宏，目前只是用`INT`和`DOUBLE`来分别代替`int`和`double`，后续可能会加上一些公用函数
- `main.cpp`：程序的入口，进行具体操作
- `test.cpp`：测试部分功能的程序
- `Makefile`：编译的命令，使用`make main`即可编译出可执行程序
- `json.hpp`：实现`json`的相关程序，具体介绍在下面
- `matrix.dat`：小规模的`COO`矩阵数据，用于测试
- `main_features.json`：运行`./main`生成的`json`文件

## 编程规范
- 对于类名与函数名，使用驼峰命名法；对于变量名，使用下划线连接。比如，函数名为`PrintCSRByRow()`，变量名为`input_file`
- 特别地，对于特征提取的函数，因为要加上编号，所以可以通过下划线连接。比如程序中包括的一个示例程序`Features_1_1_Nrows()`，其中编号对应`features.pdf`文件中的特征`1.1`，后面的`Nrows`表示特征的名称
- 缩进统一使用`tab`，四个空格
- 括号的使用，尽量对齐。比如
```cpp
for(...)
{
	i++
}
```
不要使用下面这种方式
```cpp
for(...){
	i++
}
```
- 在头文件`*.h`中进行函数声明，在`*.cpp`中进行函数定义，尽量不要在头文件中进行函数实现

程序的主体已经写好，剩下的工作主要是：根据函数`Features_1_1_Nrows()`写法，基于`CSR`矩阵结构，编写出提取其它特征的函数。该函数的相关内容位于`features.cpp features.h`文件中。

## json 库
考虑到`STL`中`map`和`unordered_map`都没有输出到文件的功能，所以使用标准`json`库。可供选择的库有很多，例如：
- `rapidjson`：速度最快，但是接口难用，没必要选择它；
- `jsoncpp`：需要单独编译成库，再链接，麻烦；
- `nlohmann/json`：只需一个`hpp`文件，接口设计的比较易用，整体评价也不错。

对性能的要求不高，越易用越好，所以最终选择`nlohmann/json`。用法很简单，只需要在官方网站 [github:nlohmann/json](https://github.com/nlohmann/json) 中下载`json.hpp`文件到本地，放在本工程目录下，然后在相关文件中加上
```cpp
#include "json.hpp"
```
即可。

以上内容只是介绍，程序已经配置好的，不用再关心这部分内容。
