#include <vector>
#include <cmath>

struct Vertex
{
  float x, y, z;
};

void generateSphere(float radius, int latitude_segments, int longitude_segments, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
{
  // Step 2: Generate vertices
  for (int lat = 0; lat <= latitude_segments; lat++)
  {
    float theta = M_PI * lat / latitude_segments; // Latitude angle (0 to PI)
    float sin_theta = sin(theta);
    float cos_theta = cos(theta);

    for (int lon = 0; lon <= longitude_segments; lon++)
    {
      float phi = 2 * M_PI * lon / longitude_segments; // Longitude angle (0 to 2*PI)
      float sin_phi = sin(phi);
      float cos_phi = cos(phi);

      float x = radius * sin_theta * cos_phi;
      float y = radius * cos_theta;
      float z = radius * sin_theta * sin_phi;

      vertices.push_back({x, y, z});
    }
  }

  // Step 3: Generate indices
  for (int lat = 0; lat < latitude_segments; lat++)
  {
    for (int lon = 0; lon < longitude_segments; lon++)
    {
      int current = lat * (longitude_segments + 1) + lon;
      int next = current + longitude_segments + 1;

      // First triangle of the quad
      indices.push_back(current);
      indices.push_back(next);
      indices.push_back(current + 1);

      // Second triangle of the quad
      indices.push_back(current + 1);
      indices.push_back(next);
      indices.push_back(next + 1);
    }
  }
}