# FreeClass

FreeClass 是一个开源的解除控制软件，旨在帮助用户摆脱极域的控制。

## 特性

- **简洁无广告**：专注于功能，无任何广告干扰。
- **开源**：源代码将会逐步开放。
- **模块化可定制**：该应用可以自行增加或减少模块，可定制性强。
- **主动防御能力强**：业界**独家**的主动防御能力，让您用的安心。

## 项目结构
```bash
FreeClass\
├─data //存放图片等数据
├─JiyuWindowsKiller  //存放主动防御模块
│  └─.vscode
├─release  //存放待发布版本
│  └─data
└─模块  //存放易语言模块
```

## 安装

### 通过官方网站安装
前往官方网站[freeclass.577622.xyz](https://freeclass.577622.xyz)或者[laosanjiekong.framer.website](https://laosanjiekong.framer.website/)按照提示进行下载安装


### 从源码安装

1. 克隆仓库：
    ```bash
    git clone https://github.com/laosan577622/FreeClass.git
    ```
2. 进入项目目录：
    ```bash
    cd FreeClass
    ```
3. 编译源码：
    - 使用易语言编译器编译易语言程序（`main.e`）。
    - 在同一目录下，使用适当的C编译器（如GCC）编译 `JiyuWindowsKiller.c` 文件：
      ```bash
      gcc -o JiyuWindowsKiller JiyuWindowsKiller.c
      ```

### 使用预编译版本

你也可以从发布页面下载预编译的版本，直接运行即可。

## 使用方法

1. 进入存放易语言和C语言编译产物的目录：
    ```bash
    cd release
    ```
2. 启动软件：
    ```bash
    start fcs.exe
    ```
3. 按照界面提示进行操作。

## 贡献

欢迎任何形式的贡献！你可以通过以下方式参与：

- 提交Issue
- 提交Pull Request
- 提出功能建议

## 许可证

本项目采用 GPLv2 许可证。

## 联系方式

如果你有任何问题或建议，请通过以下方式联系我们：

- 邮箱：laosan@577622.xyz
- GitHub Issues: [Github Issues](https://github.com/laosan577622/FreeClass/issues)
