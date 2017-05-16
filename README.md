# C51
- 这篇文章是现代控制理论课程设计的前半部分，主要研究了单自由度弹性关节系统的工程背景，动力学建模；控制系统方面包括状态方程建立，状态转移矩阵计算，零输入给定初值`MATLAB`与`Python Tkinter`模型仿真，状态方程与传递函数之间的转换，系统能观性和能控性的讨论。 
- 单自由度弹性关节示意图如下：
![单自由度弹性关节](https://ws1.sinaimg.cn/large/005WMcFzly1ffn2m7gikuj30by06pq3b.jpg) 

*P.S.* 这篇文章的原排版系统为`LaTeX`，在[ShareLaTeX](https://www.sharelatex.com/project/5915c87ed1d7c39a6d050f86)上可以导出`PDF`格式的报告，同时`LaTeX Source`也开放了公共阅读权限。
<!--more-->  

## 工程背景
### 工业机器人概述
工业机器人按照ISO8373定义`\footnote{ISO Standard 8373:1994, Manipulating Industrial Robots – Vocabulary}`，它是面向工业领域的多关节机械手或多自由度的机器人。工业机器人是自动执行工作的机器装置，是靠自身动力和控制能力来实现各种功能的一种机器。它可以接受人类指挥，也可以按照预先编排的程序运行，现代的工业机器人还可以根据人工智能技术制定的原则纲领行动。  
工业机器人的重要特性是三维空间运动的空间机构，这也是其区别与数控机床的特征。机器人的机构本质上为空间多体系统。当考虑系统元件的弹性时，为多柔性体系统。机器人的主要机构有：关节、连杆、伺服电机、减速机等。  

- **关节：**机器人系统中将运动副称为关节。在关节之中，凡单独驱动的称为主动关节，反之称从动关节。工业机器人手臂的关节常为单自由度主动关节，即每一个关节均有一个驱动器驱动。
- **连杆：**连杆机构是传递机械能的一种装置，通常是由刚体构件用转动副、移动副、球面副、球销副、圆柱副或螺旋副中的一种或几种联结而成的机械机构，因为上述联接副均属于低副，连杆机构也称为低副机构。通过不同的设计与计算，连杆机构可实现转动、直线移动、往复运动和平面或空间的复杂函数运动轨迹。
- **伺服电机：**伺服电机是对用于使用伺服机构的电动机总称。伺服系统，就是依照指示命令动作所构成的控制装置，应用于马达的伺服控制，将感测器装在马达与控制对象机器上，侦测结果会返回伺服放大器与指令值做比较。伺服马达的动作特性是进行位置定位控制和动作速度控制，其主要特点为转速可以精确控制，速度控制范围广。
- **减速机：**减速机一般用于低转速大扭矩的传动设备，把电动机，内燃机或其它高速运转的动力通过减速机的输入轴上的齿数少的齿轮啮合输出轴上的大齿轮来达到减速的目的，减速机是一种动力传达机构，利用齿轮的速度转换器，将马达的回转数减速到所要的回转数，并得到较大转矩的机构。

### 机器人柔性设计
机器人的柔顺性是实现未知约束环境下人机安全物理交互，开展复杂作业的
重要前提。针对机器人关节的顺应性控制问题，传统工业中普遍应用“刚性设计，控制实现安全”的模式，然而这种设计会造成操作者的不适，且有可能对操作者或机器人接触的物体造成损伤。为了解决这个问题，可以在驱动机构和负载端之间串联弹性元件，将负载输出和电机惯量隔离。在人机物理交互的场合中，可确保接触力控制在合理范围内，其实现模式为“设计实现安全，控制提高性能`\footnote{浙江大学硕士学位论文：串联弹性关节控制与交互刚度辨识 吕铖杰 2015}`”。但是弹性介质的引入增加了系统动态结构的复杂度，设计稳定和可靠的控制算法成为使用该类驱动器的挑战之一。

## 动力学建模
单自由度弹性关节的使用场景一般是低速大力矩情形下，往往电机和负载之间会安装减速器，为了分析方便，在理想状态下不考虑减速器摩擦与额外转动惯量的影响，以下为单自由度弹性关节示意图：
![单自由度弹性关节](https://ws1.sinaimg.cn/large/005WMcFzly1ffn2m7gikuj30by06pq3b.jpg) 
其中：$J_m$为电动机的转动惯量，$J_l$为负载的转动惯量，$\beta_m$为电动机的阻尼，可认为是转动摩擦与空气阻力等，$\beta_l$为负载的阻尼，$\theta_m$为电动机旋转的角度，$\theta_l$为负载旋转的角度，$k$为扭力弹簧常数，$u$为电动机的输入转矩。  
首先对电动机进行受力分析：电动机输入转矩与弹簧扭转力矩，自身转动惯量产生的转矩，阻尼产生的转矩之和相平衡。  
弹簧扭转力矩公式为：$F_1=k\times\Delta\theta$；  
转动惯量产生的转矩为：$F_2=J\times\omega$；     
阻尼产生的转矩为：$F_3 = \beta\times\alpha$；  
综上，可导出电动机转动时的转矩平衡公式：  
$$u = k(\theta_m-\theta_l)+J_m\ddot{\theta}_m+\beta_m \dot{\theta}_m$$  
同理可导出负载转动时的转矩平衡公式：  
$$k(\theta_l-\theta_m)=-J_l\ddot{\theta}_l-\beta_l\dot{\theta}_l$$  
整理两式，单自由度弹性关节的模型为：  
$$
\left\{ \begin{array}{ll}
    J_l\ddot{\theta}_l+\beta_l\dot{\theta}_l+k(\theta_l-\theta_m)=0 \\
    J_m\ddot{\theta}_m+\beta_m\dot{\theta}_m-k(\theta_l-\theta_m)=u
\end{array} \right.
$$

## 控制系统分析
### 微分方程转化状态方程
首先确定状态变量为：$\theta_l,\dot{\theta}_l,\theta_m,\dot{\theta}_m$；  
根据前文导出的单自由度弹性关节模型，可导出系统的状态方程为：  

$$
\left\{ \begin{array}{ll}
    \dot{x_1} = x_2 \\
    \dot{x_2} = -\frac{k}{J_l}x_1-\frac{\beta_l}{J_l}x_2+\frac{k}{J_l}x_3 \\
    \dot{x_3} = x_4 \\
    \dot{x_4} = \frac{k}{J_m}x_1-\frac{\beta_m}{J_m}x_4-\frac{k}{J_m}x_3+\frac{1}{J_m}u
\end{array} \right.
$$
### 状态转移矩阵
线性定常系统的状态空间表达式为：  
$$
\left\{ \begin{array}{ll}
    \dot{X} = AX+Bu \\
    y = CX
\end{array} \right.
$$  
其中：  
$$A = 
\begin{bmatrix}
0 & 1 & 0 & 0 \\
-\frac{k}{J_l} & -\frac{\beta_l}{J_l} & \frac{k}{J_l} & 0 \\
0 & 0 & 0 & 1 \\
\frac{k}{J_m} & 0 & -\frac{k}{J_m} & -\frac{\beta_m}{J_m}
\end{bmatrix};\qquad B = 
\begin{bmatrix}
0 \\ 0 \\ 0 \\ \frac{1}{J_m}
\end{bmatrix}; \qquad C = 
\begin{bmatrix}
1 & 0 & 0 & 0
\end{bmatrix}
$$  
线性定常系统在没有控制作用时，由初始条件引起的运动为自由运动：\par
对于线性定常系统，状态转移矩阵为：
$$\Phi(t-t_0)=e^{A(t-t_0)}$$  
  
**MATLAB求解**  
代入系统已知参数，使用  
    
```matlab
var = expm(A*t)  
```  
```matlab
var = ilaplace(inv(s*diag([1 1 1 1])-A))  
```

即可解出结果。  

### 零输入给定初值状态方程仿真  

单自由度弹性关节机器人系统仿真所需参数如下表所示:  

|物理量|数值|单位|
|:----:|:----:|:----:|
|$J_m$ | 1 | $kg\cdot m^2$ |
|$J_l$ | 1 | $kg\cdot m^2$ |
|$\beta_m$ | 0.1 | $N$ |
|$\beta_l$ | 0.1 | $N$ |
|$k$ | 60 | $N/rad$ |

#### ODE45方法求解(基于MATLAB)  
使用ode45求解高阶常微分方程需要做降阶处理，使用该系统的状态方程构造函数，代码如下：  

```matlab
function dydt = odefcn(t,y,matrixA,matrixB)
    dydt = zeros(4,1);
    dydt = matrixA*[y(1);y(2);y(3);y(4)]+matrixB*0;    
```

其中，已知输入$u$为零。  
代入矩阵参数，初值，时间求微分方程的数值解，并绘制$\theta_l,\dot{\theta}_l,\theta_m,\dot{\theta}_m$关于变量$t$的曲线，代码如下：  

```matlab
clear all
syms s t
J_m = 1; J_l = 1; B_m = 0.1; B_l = 0.1; k = 60;
A = [0        1        0       0;
    -k/J_l    -B_l/J_l k/J_l   0;
     0        0        0       1;
     k/J_m    0        -k/J_m  -B_m/J_m]
b = [0;0;0;1/J_m]
tspan = linspace(0,100,500)
y0 = [0.1;0;0;0];
[tode,y] = ode45(@(t,y) odefcn(t,y,A,b), tspan, y0)
plot(tode,y(:,1),'g+',tode,y(:,2),'b*',tode,y(:,3),'k-.',tode,y(:,4),'r')
legend('y1','y2','y3','y4')
title('Solutions of Differential Equation(ode45)')
```

#### 矩阵指数方法求解(基于MATLAB)    
和上一种方案的矩阵参数，初值，时间相同，使用拉氏反变换法求解矩阵指数，并绘制$\theta_l,\dot{\theta}_l,\theta_m,\dot{\theta}_m$关于变量$t$的曲线。  
矩阵指数的计算公式：   
$$e^At=\mathcal{L}^{-1}[(sI-A)^{-1}]$$  
有以下代码： 
   
```matlab   
X = ilaplace(inv(s*diag([1 1 1 1])-A))*y0
plot(tspan,subs(X(1),t,tspan),'-b+',tspan,subs(X(2),t,tspan),'-g*',tspan,subs(X(3),t,tspan),'k-.',tspan,subs(X(4),t,tspan),'r')
legend('y1','y2','y3','y4')
title('Solutions of Differential Equation(Matrix exponential)')
```    

#### MATLAB程序运行结果  
运行以上MATLAB程序，可得到如下图所示的图像；当前给负载角度初值为$0.1rad$,弹簧处于紧绷状态，系统零输入启动后，电机与负载产生相反方向的加速度，最终达到稳态。
![ODE45](https://ws1.sinaimg.cn/large/005WMcFzly1ffn3i6ix0wj30fk0dpdgl.jpg)
![矩阵指数](https://ws1.sinaimg.cn/large/005WMcFzly1ffn3i6k4l2j30fk0dp0tg.jpg)  

#### 系统仿真动画(基于Python Tkinter)
首先使用Python scipy模块求解系统的状态方程，得到$\theta_l,\dot{\theta}_l,\theta_m,\dot{\theta}_m$关于变量$t$的变化情况。借由matplotlib模块绘制曲线。同时，使用Tkinter创建图形用户界面，并根据上述求解的值绘制动画，实现数据可视化。程序运行效果如下图所示：  
![GUI](https://ws1.sinaimg.cn/large/005WMcFzly1ffn3jpjjb2j30hs0f9jrq.jpg)
![matplotlib绘图](https://ws1.sinaimg.cn/large/005WMcFzly1ffn3jqufepj30hs0f4tb2.jpg)

##### 代码功能：
单自由度弹性关节机器人系统的仿真程序，支持自定义输入，初值，系统参数；可以通过图形用户界面观察该系统的运行状态。

##### 运行环境：  
兼容Windows/macOS/Linux，需要Python环境：  
  
- Python 2.7.11  
- matplotlib $\geq$ 1.5.1   
- numpy $\geq$ 1.12.1   
- scipy $\geq$ 0.19.0   

##### 代码说明:
首先导入需要使用的模块，相关代码块如下所示：  

```python
import numpy as np
import matplotlib
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt
import math
import time
from Tkinter import *
from scipy.integrate import odeint
```  
变量赋值部分，根据实际物理系统给转动惯量，阻尼，劲度系数等变量赋值，同时确定画布大小，确定代表电机/负载的矩形位置。  

```python
WIDTH,HEIGHT,SIDE = 400,400,100
CANVAS_MID_X,CANVAS_MID_Y = WIDTH/2,HEIGHT/2
J_m, J_l, B_m, B_l, k = 1,1,0.1,0.1,1
square_m =  np.array([
    [CANVAS_MID_X - SIDE/2, CANVAS_MID_Y - SIDE/2],
    [CANVAS_MID_X + SIDE/2, CANVAS_MID_Y - SIDE/2],
    [CANVAS_MID_X + SIDE/2, CANVAS_MID_Y + SIDE/2],
    [CANVAS_MID_X - SIDE/2, CANVAS_MID_Y + SIDE/2]]
)
square_l = square_m + 100*np.ones((4,2))
```  
以下为数据初始化函数，规范数据格式：  

```python
def data_init(initial_conditions, model_params):
    y0 = initial_conditions['y0']
    A = model_params['A']
    b = model_params['b']
    return [y0,A,b]
```  
以下为ode求解所需的降阶函数，输入为初始状态，时间，系统状态空间描述系数矩阵，输出重构为单维数组(Python odeinit解法不支持高阶输入)  

```python
def f(state, t, matrixA, matrixb):
    xdot = matrixA*state.reshape(4,1) + matrixb*np.exp(-t)
    return np.squeeze(np.asarray(xdot))
```  
以下为矩形旋转坐标运算函数，输入为矩形四点坐标，需要旋转的角度(弧度制)，旋转中心坐标；返回值为旋转后的矩形四点坐标。  

```python
def rotate(points, angle, center):
    cos_val = math.cos(angle)
    sin_val = math.sin(angle)
    cx, cy = center
    new_points = []
    for x_old, y_old in points:
        x_old -= cx
        y_old -= cy
        x_new = x_old * cos_val - y_old * sin_val
        y_new = x_old * sin_val + y_old * cos_val
        new_points.append([x_new + cx, y_new + cy])
    return new_points
```  
以下为绘图函数，输入为几何元素canvas，ode解法得到的角度list，使用i索引list元素，无返回值。遍历解出的角度list即可画出旋转矩形；为实现动画效果，需使用定时任务，在该函数中使用了time模块的sleep()函数  

```python
def draw_square(cv,ans,i):
    center_l = (CANVAS_MID_X+100, CANVAS_MID_Y+100)
    center_m = (CANVAS_MID_X, CANVAS_MID_Y)
    points_l = rotate(square_l, ans[i,0], center_l)
    points_m = rotate(square_m, ans[i,2], center_m)
    cv.create_polygon(points_l, fill="blue")
    cv.create_polygon(points_m, fill="red")
    cv.update()
    time.sleep(0.01)
    cv.delete("all")
```  
以下为开始按钮的事件函数，输入为几何元素canvas，ode解法得到的角度list，Tk的界面对象。  
 
```python
def draw_start(canvas,ans,root):
    for i in range(0, 500):
        draw_square(canvas,ans,i)
        if i == 499:
            root.destroy()
    root.mainloop()
```  
以下为数据过程可视化函数，输入为ode解法得到的角度list。封装canvas元素，label元素(用以显示解释性文字)，buttom元素(开始绘图功能支持)。  

```python
def visualize_process(ans):
    root = Tk()
    canvas = Canvas(root, bg="black", height=HEIGHT, width=WIDTH)
    canvas.pack()
    Label_l = Label(root, text="blue--Load", font="Times 16 bold")
    Label_l.pack()
    Label_m = Label(root, text="red--motor", font="Times 16 bold")
    Label_m.pack()
    btn = Button(root, text="run", command=lambda:draw_start(canvas,ans,root))
    btn.pack()
```   
以下为数据图表可视化函数，输入为ode解法得到的角度list。使用matplotlib模块中的plot函数绘制$\theta_l,\dot{\theta}_l,\theta_m,\dot{\theta}_m$关于变量$t$的曲线。  
  
```python
def visualize_figure(ans):
    t_ = np.linspace(0, 100, np.size(ans[:, 0]))
    thetal,= plt.plot(t_, ans[:,0],label='thetal')
    thetal_dot,= plt.plot(t_, ans[:,1],label='thetal_dot')
    thetam, = plt.plot(t_, ans[:,2],label='thetam')
    thetam_dot, = plt.plot(t_, ans[:,3],label='thetam_dot')
    plt.legend(handles=[thetal, thetal_dot, thetam, thetam_dot])
    plt.show()
```  
以下为主函数，初始化数据，求解模型的状态方程，并分别调用过程可视化函数，图表可视化函数。  

```python
if __name__ == '__main__':
    tspan = np.linspace(0, 100, 500)
    initial_conditions = {'y0': [0,0,0,0]}
    model_params = {'A': np.mat([0,        1,          0,           0,
                                 -k / J_l, -B_l / J_l, k / J_l,     0,
                                 0,        0,          0,           1,
                                 k / J_m,  0,          -k / J_m,    -B_m / J_m
                                 ]).reshape(4,4),
                    'b': np.mat([0, 0, 0, 1 / J_m]).reshape(4,1)
                    }
    data = data_init(initial_conditions, model_params)
    y = odeint(f,data[0],tspan,args=(data[1], data[2]))
    visualize_process(y)
    visualize_figure(y)
```
