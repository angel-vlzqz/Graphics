#include <vector>

struct Vertex {
    float x, y, z;
};

void generateGroundPlane(float plane_size, int grid_resolution, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
    float spacing = plane_size / grid_resolution;

    // Step 3: Generate vertices
    for (int i = 0; i <= grid_resolution; i++) {
        for (int j = 0; j <= grid_resolution; j++) {
            float x = -plane_size / 2 + i * spacing;
            float y = 0.0f; // Y is fixed as the ground plane
            float z = -plane_size / 2 + j * spacing;

            vertices.push_back({x, y, z});
        }
    }

    // Step 4: Generate indices for triangles
    for (int i = 0; i < grid_resolution; i++) {
        for (int j = 0; j < grid_resolution; j++) {
            int top_left = i * (grid_resolution + 1) + j;
            int top_right = top_left + 1;
            int bottom_left = top_left + (grid_resolution + 1);
            int bottom_right = bottom_left + 1;

            // First triangle
            indices.push_back(top_left);
            indices.push_back(bottom_left);
            indices.push_back(top_right);

            // Second triangle
            indices.push_back(top_right);
            indices.push_back(bottom_left);
            indices.push_back(bottom_right);
        }
    }
}