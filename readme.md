# 3D-CPU-Renderer

A simple 3D graphics renderer written in C, running entirely on the CPU without using any graphics APIs.
It uses the Windows API to create a window and display a pixel buffer computed by the program.

---

## Features

- Triangle rasterization using integer scanlines
- Manual Z-buffer for depth handling
- Perspective projection
- Per-triangle coloring
- Basic model rotation animation
- No GPU usage or external libraries

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