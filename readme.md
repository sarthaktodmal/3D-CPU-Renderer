# 3D-CPU-Renderer

A minimal 3D graphics renderer written entirely in C. It runs on the CPU and uses the Windows API to open a window and draw pixels to the screen — without relying on any graphics libraries like OpenGL or DirectX.

The renderer builds 3D models using a list of vertices and indices to form triangles, which are then projected and drawn using a simple graphics pipeline.

---

## Features

- Draws 3D triangles: The program can draw shapes made of triangles by filling them line by line.

- Handles depth (Z-buffer): It knows which triangles should appear in front and hides the ones behind.

- Perspective view: Objects look smaller when farther away, just like in real life.

- Basic coloring: Each triangle can have its own color.

- Rotating shapes: Simple spinning animations for cubes or models.

- No graphics card needed: All the work is done by your CPU.

- Uses only C and WinAPI: Great for learning how rendering works at a low level.

---

## Result

### Cube  
<img src="media/Engine_3.gif" width="300"/>

### Robot  
<img src="media/Engine_2.gif" width="300"/>

### Sphere  
<img src="media/Engine.gif" width="300"/>

---

## Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/sarthaktodmal/3D-CPU-Renderer.git
   cd 3D-CPU-Renderer
2. Run Build.bat:
   ```bash
   ./Build.bat

---

## END