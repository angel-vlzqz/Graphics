# Textured Triangles

This program illustrates texture mapping by drawing three triangles, each with a red and yellow checkered pattern mapped onto it. The same texture is used for each triangle, but the mappings of texture coordinates to vertex coordinates are different in each triangle.

## Running the Program

To run the program, compile it and execute the resulting binary. The program will display a window containing the three textured triangles.

## User Input

The program responds to the following keyboard input:

* `p`: Stop the image from spinning.
* `c`: Start the image spinning.
* `u`: Move the object up.
* `d`: Move the object down.
* `l`: Move the object to the left.
* `r`: Move the object to the right.
* `-`: Zoom out on the object.
* `+` or `=`: Zoom in on the object.

## Animation

The program uses a timer to create an animation effect. The timer calls the `animate` function every 10 milliseconds, which increases the angle of the object and redisplays the window. This creates the spinning effect on the object.

## Building

Compile the program using a command similar to the following:

```bash
g++ Part1.cpp -o Part1 -lfreeglut -lopengl32 -lglu32
```

Run the program with:

```bash
./Part1
```


# RGB Color Cube Flyby

This program provides a flyby animation around an RGB color cube, demonstrating the use of OpenGL for rendering 3D graphics. The cube is a convex polyhedron, allowing it to be rendered using backface culling without a depth buffer.

## Features

- Interactive keyboard controls to manipulate the cube's view and animation.
- Animation of a rotating view around the RGB color cube.
- Multiple cubes with varying colors floating around the scene.
- Backface culling for efficient rendering.

## Controls

- `r`: Rotate the cube.
- `p`: Pause the rotation.
- `c`: Continue the rotation.
- `u`: Move the object upwards.
- `d`: Move the object downwards.
- `-`: Zoom out on the object.
- `+` or `=`: Zoom in on the object.

## Installation and Running

1. Ensure you have OpenGL and GLUT installed on your system.
2. Compile the program using a C++ compiler with OpenGL support.
3. Run the compiled binary to launch the application.

## Animation

The program uses a timer to create an animation effect by flying around the cube along a specified orbit. The camera moves and looks at the cube's center, creating a tumbling effect.

## Implementation Details

- **Cube Definition**: The cube has vertices with RGB color gradients, and each face is defined for rendering.
- **Display Function**: Clears the window, applies transformations, and draws the cubes.
- **Timer Function**: Updates the camera and cube positions for animation.
- **Reshape Function**: Adjusts the viewport and camera settings when the window is resized.
- **Initialization**: Enables backface culling for rendering the cube.

## Building

Compile the program using a command similar to the following:

```bash
g++ -o Part2 Part2.cpp -lGL -lGLU -lglut
```

Run the program with:

```bash
./Part2
```

