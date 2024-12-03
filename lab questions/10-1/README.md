1. In the specific context of graphics workloads, performing cycle-accurate 
simulations are even more demanding due to the high number of triangles that have 
to be shaded, lighted and textured to compose a single frame. As a result, 
simulating a few minutes of a video game sequence is extremely time-consuming.

Ortiz, Jorge (05/2022). "MEGsim: A Novel Methodology for Efficient Simulation of
  Graphics Workloads in GPUs" in 2022 IEEE International Symposium on Performance 
  Analysis of Systems and Software (ISPASS) (1-66545-955-7, 978-1-66545-955-6), ( 
  69).


2. To model the most important effects of smoke, we need two extra fluid 
variables: the temperature T of the air and the concentration s of smoke 
particles—what we actually can see. Similar phenomena, such as vapor, can be 
modeled in much the same way.

Bridson, R. (2015). Fluid Simulation for Computer Graphics (2nd ed.). A K Peters/
  CRC Press. https://doi.org/10.1201/9781315266008


3. Interactive rigid body simulation is an important part of many modern computer 
tools, which no authoring tool nor game engine can do without. Such 
high-performance computer tools open up new possibilities for changing how 
designers, engineers, modelers and animators work with their design problems.

Jun Ma, Nak-Jun Sung, Min-Hyung Choi, Min Hong, Performance Comparison of Vertex 
  Block Descent and Position Based Dynamics Algorithms Using Cloth Simulation in 
  Unity, Applied Sciences, 10.3390/app142311072, 14, 23, (11072), (2024).


4. Fluid can be simulated from 2 viewpoints, Lagrangian or Eulerian.
In the Lagrangian viewpoint, we simulate the fluid as discrete blobs
of fluid. Each particle has various properties, such as mass, velocity, etc. The benefit of this approach is that conservation of mass
comes easily. 

Braley, C., & Sandu, A. (2010). Fluid simulation for computer graphics: A tutorial 
  in grid based and particle based methods. Virginia Tech, Blacksburg, 3.


5. We use a staggered grid discretization of
the velocity and pressure equations as in [Fedkiw, et al.
2001;Foster and Metaxas 1997;Griebel, et al. 1998]. This
means that pressure, temperature, and water content are
defined at the center of voxels while velocity is defined on
the faces of the voxels. Not only does this method reduce
numerical dissipation as mentioned by Fedkiw et al., but as
Griebel et al. explain, it prevents possible pressure
oscillations that can arise with collocated grids (in which all
variables are defined at cell centers). 

Harris, M. J., Baxter, W. V., Scheuermann, T., & Lastra, A. (2003, July). 
  Simulation of cloud dynamics on graphics hardware. In Proceedings of the ACM 
  SIGGRAPH/EUROGRAPHICS conference on Graphics hardware (pp. 92-101).