# N-Body_2D_MFC
2D N-Body simulation via RK4 with MFC , Brute Force method（基于MFC的二维N体问题模拟，四阶龙格库塔法，暴力算法）


Compile Environment : Microsoft Visual Studio 2013 Community


Step by step intro:


>1.New Project->MFC->MFC Application->Single document->Finish


>2.Project->Class Wizard->Class 

>3.Name:CChildView/Messages:WM_TIMER,WM_CREATE,WM_KEYDOWN,WM_PAINT


>4.Replace CChildView.h,CChildView.cpp with given files


>5.Replace 【#include "nbodyTest.h"】 in CChildView.cpp with 【#include "Your Project Name.h"】


>6.Compile it and have fun


Press space to start/pause.


The final effect might looks like this：
![](http://thumbnail0.baidupcs.com/thumbnail/d45e87f8a4d664c357b16e29a6ee745a?fid=3054427709-250528-255474628577139&time=1478865600&rt=sh&sign=FDTAER-DCb740ccc5511e5e8fedcff06b081203-NqpGXOm4hQByWJxg7c9tBeVYWes%3D&expires=8h&chkv=0&chkbd=0&chkpc=&dp-logid=7325379434639998041&dp-callid=0&size=c710_u400&quality=100)


This project established a particle model of the 2D N-Body motion.


After the reasonable simplification and approximation,an equation that meeting the requirement of the model is genrated.By Runge-Kutta method which is properly numerical computing method to solve this equation.


Based on the computing method,the project build an MFC(Microsoft Foundation Classes) project in the Microsoft Visual Studio 2013 Community(usually known as VS 2013).In order to update the state in real time,the project storage bodies state in the structs and then trigger the Timer to call the CDC classes which could draw object on the screen.This project use computing method called All-pairs which is more simple and basic one.

The simulating of chaos of the three body movement in classical mechanics showed that the model is reasonable partly.
