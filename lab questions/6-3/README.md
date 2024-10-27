Markdown Explanation:

Applying Phong Lighting Model in OpenGL

To apply a lighting model to your OpenGL scene, we can use the Phong Lighting Model. This model allows us to simulate how light interacts with surfaces, creating realistic shading effects. The model consists of three main components: ambient, diffuse, and specular lighting.

1. Phong Lighting Model Components

	•	Ambient: This is the base level of light that affects all surfaces equally, representing indirect light.
	•	Diffuse: This light simulates the scattering of light when it hits a surface. It depends on the angle between the light and the surface normal.
	•	Specular: This component simulates the reflective “shine” on surfaces and depends on the viewer’s position relative to the light source and the surface.

The total lighting at a surface point is calculated as:

￼

Where:

	•	￼
	•	￼
	•	￼

Here, ￼ are material coefficients, and the dot products represent the angles between vectors.

2. Steps to Apply the Lighting Model

Step 1: Set Up Lighting and Material Properties

Define the light position, light color, and the material properties of the objects (ambient, diffuse, and specular reflectivity).

Step 2: Enable OpenGL Lighting

Enable lighting and set up the light and material properties in your main() function.

Step 3: Add Normal Calculation for Geometry

To calculate lighting properly, normals need to be specified for each vertex of the geometry.

Step 4: Render the Scene with Lighting

Enable depth testing and ensure the light position is correctly set during rendering. The lighting will be applied to your geometry based on the defined material properties and light source.
