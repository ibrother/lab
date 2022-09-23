--color magenta
--author ibrother
--color red
--date today
--color magenta
--title Ubuntu环境下的Linux内核编译
--footer ibrother.linux@gmail.com
--header Wlecome to Linux World

---
--color red
--heading 一、编译内核前的准备
--color cyan
--ulon
--horline
--uloff


---
--color blue
--beginslidetop
 1. 知道自己用的发行版的内核在哪,模块在哪
--endslidetop

---
--beginslideleft
--color yellow
  * linux内核放在/boot目录下面，可以在终端中查看
--endslideleft
--color cyan
--beginshelloutput
---
$ ls -l /boot
--color green
---
总用量 7312
-rw-r--r-- 1 root root   80144 10月 26 14:49 config-3.10.7-gentoo-r1
drwxr-xr-x 6 root root    1024 10月 26 14:50 grub
-rw-r--r-- 1 root root 1404688 10月 26 14:49 initramfs-genkernel-x86_64-3.10.7-gentoo-r1
drwx------ 2 root root   12288 10月 24 07:19 lost+found
-rw-r--r-- 1 root root 2309317 10月 26 14:49 System.map-3.10.7-gentoo-r1
-rw-r--r-- 1 root root 3677968 10月 26 14:49 vmlinuz-3.10.7-gentoo-r1
--endshelloutput
---
--beginslideleft
--color yellow
  * 内核的模块放在/lib/modules/$(uname -r)这个目录下
--endslideleft
--color cyan
--beginshelloutput
---
$ ls -l /lib/modules/$(uname -r)
--color green
---
总用量 3574
lrwxrwxrwx  1 root root     40 10月  9 16:56 build -> /usr/src/linux-headers-3.11.0-12-generic
drwxr-xr-x  2 root root     32 10月 16 19:01 initrd
drwxr-xr-x 11 root root    161 10月 16 19:01 kernel
....
--endshelloutput

--newpage 一、编译内核前的准备
--color red
--heading 一、编译内核前的准备
--color cyan
--ulon
--horline
--uloff


---
--beginslidetop
--color blue
 2. 硬件检测，了解自己机器的硬件，以及系统加载的驱动模块

---
--color yellow
  * 查看cpu信息
--endslidetop
---
--color cyan
--beginshelloutput
$ lscpu
---
$ cat /proc/cpuinfo
--endshelloutput
---
--beginslideleft
--color yellow
  * 查看pci信息
--endslideleft
---
--color cyan
--beginshelloutput
$ sudo apt-get install pciutils
---
$ lspci -vv
--endshelloutput
--color yellow
---
--beginslideleft
  * 查看usb信息
--endslideleft
---
--color cyan
--beginshelloutput
$ sudo apt-get install usbutils
---
$ lsusb
--endshelloutput
--color yellow
---
--beginslideleft
  * 查看当前系统加载的模块
--endslideleft
---
--color cyan
--beginshelloutput
$ lsmod
--endshelloutput
---
--beginslidebottom
--color yellow
  * 查看模块信息
--endslidebottom
--color cyan
--beginshelloutput
$ modinfo 模块名
--endshelloutput

--newpage 一、编译内核前的准备
--color red
--heading 一、编译内核前的准备
--color cyan
--ulon
--horline
--uloff


---
--color blue
--beginslideleft
 3. 安装编译工具链，搭建内核编译环境
--endslideleft

---
--color yellow
--beginslidetop
  * gnu工具集
--color green
  gcc,make,gdb,m4,bison,binutils,automake,autoconf,libtool
--endslidetop

---
--beginslideleft
--color yellow
  * 显示菜单的ncurses5库开发包
--color green
  libncurses5-dev
--endslideleft

---
--beginslideleft
--color yellow
  * dpkg开发工具包
--color green
  dpkg-dev
--endslideleft

---
--beginslideleft
--color yellow
  * ubuntu下的安装
--endslideleft
--color cyan
--beginshelloutput
$ sudo apt-get install build-essential libncurses5-dev
--endshelloutput

--color green
  至此你已经完成编译内核的准备工作:)

--newpage 二、编译内核的具体步骤
--color red
--heading 二、编译内核的具体步骤
--color cyan
--ulon
--horline
--uloff


---
--color blue
--beginslidetop
 1.获取linux内核源码 (以3.10.17为例)
--endslidetop

---
--color yellow
--beginslidetop
  * 从内核的官网获取源码，解压并进入工作目录
--endslidetop
---
--color cyan
--beginshelloutput
$ cd /tmp
---
$ wget https://www.kernel.org/pub/linux/kernel/v3.x/linux-3.10.17.tar.xz
---
$ tar xvJf linux-3.10.17.tar.xz
---
$ cd /tmp/linux-3.10.17
--endshelloutput
---
--color blue
--beginslideleft
 2. 进入配置菜单，开始配置内核 (最繁琐也是最重要的一步)
--endslideleft

---
--color yellow
  * 清理源码树 (第一次编译可不执行，再编译时需执行)
---
--color cyan
--beginshelloutput
$ sudo make mrproper
--endshelloutput
---
--color yellow
  * 根据当前的硬件环境生成配置
---
--color cyan
--beginshelloutput
$ sudo make defconfig
--endshelloutput
---
--color yellow
  * 使用菜单继续配置
---
--color green
  ** 这一步推荐参考金步国大侠的配置选项详解
--beginoutput
 http://www.jinbuguo.com/kernel/longterm-3_10-options.html
--endoutput
--color cyan
--beginshelloutput
$ sudo make nconfig
--endshelloutput
---
--color yellow
  * 开始编译,等待编译完成
---
--color cyan
--beginshelloutput
$ sudo make deb-pkg
--endshelloutput

--newpage 三、安装新内核
--color red
--heading 三、安装新内核
--color cyan
--ulon
--horline
--uloff


---
--color blue
--beginslidetop
 1. 进入上层目录，并安装内核
--endslidetop
---
--color cyan
--beginshelloutput
$ cd ..
---
$ sudo dpkg -i *.deb
--endshelloutput
---
--color blue
--beginslideleft
 2. 重启并选择用新内核启动系统
--endslideleft
---
--color cyan
--beginshelloutput
$ sudo reboot
--endshelloutput
---
--color blue
--beginslideleft
 3. 验证新内核
--endslideleft
---
--color green
--beginoutput
  * 不要想一次就能编译出让自己满意的内核
---
  * 当新内核有问题时，要细心找到问题的原因，不怕麻烦，继续重新编译
--endoutput

---
--color blue
--beginslideleft
 4. 卸载自定义的内核
--endslideleft
--color green
--beginoutput
 由于用的是ubuntu的方式编译的内核，内核有关的文件已经纳入了包管理系统
 这样就可以像卸载普通软件包一样卸载自定义的内核
 只是需要注意最好不要卸载当前正在使用的内核
 可以重启到其他内核（例如官方内核）再卸载不需要或有问题的内核
--endoutput
---
--color cyan
--beginshelloutput
$ sudo apt-get --purge remove 内核名
--endshelloutput

--newpage 四、自定义内核的升级
--color red
--heading 四、自定义内核的升级
--color cyan
--ulon
--horline
--uloff


---
--color blue
--beginslidetop
 1. 获取最新的内核源码
--endslidetop

---
--color yellow
--beginslideleft
  * 当遇小版本升级时
--endslideleft
--color green
--beginoutput
 例如现在官方内核升级到了3.10.18 而你有3.10.17的源码包，这样就不需要重新下载
 只需要下载patch-3.10.18.xz
 然后为3.10.17的源码打补丁，这样3.10.17的源码就升级到3.10.18
--endoutput
---
--color cyan
--beginshelloutput
$ wget https://www.kernel.org/pub/linux/kernel/v3.x/patch-3.10.18.xz
---
$ tar xvJf linux-3.10.17.tar.xz
---
$ cd linux-3.10.17
---
$ xz -dc ../patch-3.10.18.xz | patch -p1
--endshelloutput
---
--color yellow
--beginslideleft
  * 当遇大版本升级时
--endslideleft
--color green
--beginoutput
 老老实实重新下载吧 :(
--endoutput
---
--color blue
--beginslideleft
 2. 导入老版本内核的配置
--endslideleft
--color green
--beginoutput
 导入配置时需要通过回答Y/N/M来配置新的内核选项
 绝大多数属于新添加的驱动，可以选N，少数新特性可以选Y
--endoutput
---
--color cyan
--beginshelloutput
$ sudo cp /boot/config-3.10.17 linux-3.10.18/.config
---
$ sudo make oldconfig
---
$ sudo make nconfig
--endshelloutput
---
--color blue
 3. 继续之前的编译安装步骤
--color green
--center Good luck to you :)
