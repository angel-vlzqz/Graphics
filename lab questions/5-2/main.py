import numpy as np

# Vertex class to represent a point in 3D space
class Vertex:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

# Quadrilateral class to represent a quadrilateral using four vertices
class Quadrilateral:
    def __init__(self, v1, v2, v3, v4):
        self.vertices = [v1, v2, v3, v4]

# Mesh class to represent a collection of vertices and quadrilaterals
class Mesh:
    def __init__(self):
        self.vertices = []
        self.quadrilaterals = []
    
    # Add a new vertex to the mesh
    def add_vertex(self, x, y, z):
        vertex = Vertex(x, y, z)
        self.vertices.append(vertex)
        return vertex
    
    # Add a new quadrilateral by specifying four vertices
    def add_quadrilateral(self, v1, v2, v3, v4):
        quad = Quadrilateral(v1, v2, v3, v4)
        self.quadrilaterals.append(quad)

# Function to calculate the normal vector for a quadrilateral (assuming planar surface)
def calculate_normal(v1, v2, v3):
    vector1 = np.array([v2.x - v1.x, v2.y - v1.y, v2.z - v1.z])
    vector2 = np.array([v3.x - v1.x, v3.y - v1.y, v3.z - v1.z])
    normal = np.cross(vector1, vector2)
    normal = normal / np.linalg.norm(normal)  # Normalize the vector
    return normal

# Phong shading function to compute the shading for a quadrilateral mesh
def phong_shading(mesh, light_position, view_position, ambient_light, diffuse_coeff, specular_coeff, shininess):
    shading_results = []
    for quad in mesh.quadrilaterals:
        # Get vertices of the quadrilateral
        v1, v2, v3, v4 = quad.vertices
        
        # Compute normal for the quadrilateral
        normal = calculate_normal(v1, v2, v3)
        
        # Calculate vectors to light and view positions
        light_vector = np.array([light_position[0] - v1.x, light_position[1] - v1.y, light_position[2] - v1.z])
        light_vector = light_vector / np.linalg.norm(light_vector)  # Normalize light vector
        
        view_vector = np.array([view_position[0] - v1.x, view_position[1] - v1.y, view_position[2] - v1.z])
        view_vector = view_vector / np.linalg.norm(view_vector)  # Normalize view vector
        
        # Ambient component
        ambient = ambient_light
        
        # Diffuse component using Lambert's cosine law
        diffuse = max(np.dot(normal, light_vector), 0) * diffuse_coeff
        
        # Specular component using Blinn-Phong model
        halfway_vector = (light_vector + view_vector) / np.linalg.norm(light_vector + view_vector)
        specular = pow(max(np.dot(normal, halfway_vector), 0), shininess) * specular_coeff
        
        # Calculate final shading value for the quadrilateral
        shading = ambient + diffuse + specular
        shading_results.append(shading)
        
        print(f"Shading for quadrilateral: {shading}")
    
    return shading_results

# Example Usage

# Create a mesh
mesh = Mesh()

# Add vertices
v1 = mesh.add_vertex(0, 0, 0)
v2 = mesh.add_vertex(1, 0, 0)
v3 = mesh.add_vertex(1, 1, 0)
v4 = mesh.add_vertex(0, 1, 0)
v5 = mesh.add_vertex(0, 0, 1)
v6 = mesh.add_vertex(1, 0, 1)
v7 = mesh.add_vertex(1, 1, 1)
v8 = mesh.add_vertex(0, 1, 1)

# Add quadrilaterals to form a cube
mesh.add_quadrilateral(v1, v2, v3, v4)  # Bottom face
mesh.add_quadrilateral(v5, v6, v7, v8)  # Top face
mesh.add_quadrilateral(v1, v2, v6, v5)  # Front face
mesh.add_quadrilateral(v2, v3, v7, v6)  # Right face
mesh.add_quadrilateral(v3, v4, v8, v7)  # Back face
mesh.add_quadrilateral(v4, v1, v5, v8)  # Left face

# Define lighting and view parameters
light_position = [10, 10, 10]
view_position = [0, 0, 5]
ambient_light = 0.1
diffuse_coeff = 0.7
specular_coeff = 0.2
shininess = 32

# Calculate shading for the mesh
shading_results = phong_shading(mesh, light_position, view_position, ambient_light, diffuse_coeff, specular_coeff, shininess)

# Display results
for idx, shading in enumerate(shading_results):
    print(f"Quadrilateral {idx+1} shading: {shading}")