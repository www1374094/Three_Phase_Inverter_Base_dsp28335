Hi，很高兴你能看到这段文字，这个工程包含的是一套三相并网逆变器的代码，目前已经调试完成了，下面我将对这段代码做一下简单的介绍。
代码中包含三个层次，硬件抽象层（前缀HAL），算法抽象层（前缀AAL)，以及用户层。

1、硬件抽象层
硬件抽象层负责的是底层硬件的初始化以及软件与硬件的交互，这么做可以将底层寄存器抽象成易于应用的数据结构，目前已经封装起来的数据结构有EPWM和ADC。EPWM利用一个结构体EPWM_Structure来抽象，ADC数据采集则是送进了三相数据结构体ThreePhase_Data_Structure中，这样就可以专注于顶层控制算法的设计。
2、算法抽象层
算法抽象层将各类算法进行封装，留出与硬件抽象层进行对接的接口，算法全部来自于TI的Solar库，可以参考TI ControlSuite的文档，有详细说明。
http://www.ti.com.cn/tool/cn/controlsuite?keyMatch=ControlSuite&tisearch=Search-CN-Everything
3、用户层
用户层现在还比较粗糙，只有一个简单的中断函数（TPVSI_DSP28335_INT.c），所有的控制环节都在这个中断函数中配置。目前代码中的是有源阻尼内环+PR控制器的控制模式。我的毕业设计研究的是并网逆变器的鲁棒控制算法，因此代码中还包含了一个Hinf控制器的实现。

这是我第一次试着将面向对象思想应用到一个大项目中，有许多不足，欢迎批评指正！

Chuck Wang
2018.5.5
Email:www_l_z@outlook.com
