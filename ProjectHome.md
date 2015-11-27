| ![http://i60.tinypic.com/2vug6yu.png](http://i60.tinypic.com/2vug6yu.png) |
|:--------------------------------------------------------------------------|

# Description #

LMX is a numerical library for C++ developers that provides built-in methods, including matrix and vector algebra, dense and sparse storage, linear direct and iterative solvers, nonlinear solvers, ODE systems integrators (Newmark, HHT, BDF, etc.). It also links to other well known libraries for high performance computations.

# Overview #

The principal difference with other libraries is that it provides a framework that enables switching between different types of matrices (dense and sparse) before and after the compilation of your code. This feature implies a little overhead in numerical operations but is not very important in the usual bottlenecks of the computational codes. An efficiency suite is supplied for you to evaluate its possible impact in your project.

As templates are throughly used, the library consists on a series of header files and can be used directly to compile your code. The size of the compiled objects and executables is kept small although the compilation time is higher compared with a precompiled library.

At this time, we provide linked methods to gmm++, SuperLU and Lapack, and the incorporation of BLAS for dense high performance methods is planed for the (near) future. The installation of these libraries is optional, as LMX is selfcontained, but their use is recommended when speed is a concern.

We hope it is as useful for you as it is for us.

_Cheers!_

# Publications #
MULTIBODY DYNAMICS 2007, ECCOMAS Thematic Conference
C.L. Bottasso, P. Masarati, L. Trainelli (eds.)
Milano, Italy, 25–28 June 2007

[![](http://w3.mecanica.upm.es/~diglesias/imagenes/IglesiasArribas_paper.png)](http://w3.mecanica.upm.es/~diglesias/docs/IglesiasArribas_paper.pdf) [![](http://w3.mecanica.upm.es/~diglesias/imagenes/posterDani_peq.png)](http://w3.mecanica.upm.es/~diglesias/docs/posterDani.pdf)