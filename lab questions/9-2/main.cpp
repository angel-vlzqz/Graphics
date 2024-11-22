// Box boundaries
float minX = -10.0f, maxX = 10.0f;
float minY = -10.0f, maxY = 10.0f;
float minZ = -10.0f, maxZ = 10.0f;

// Damping factor for collisions
float dampingFactor = 0.9f;

// Particle structure
struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
};

// Update function
void updateParticles(std::vector<Particle>& particles, float deltaTime) {
    for (auto& particle : particles) {
        // Compute next position
        glm::vec3 nextPos = particle.position + particle.velocity * deltaTime;

        // Check collisions and adjust velocity
        if (nextPos.x < minX || nextPos.x > maxX) {
            particle.velocity.x = -particle.velocity.x * dampingFactor;
            particle.position.x = glm::clamp(particle.position.x, minX, maxX);
        }
        if (nextPos.y < minY || nextPos.y > maxY) {
            particle.velocity.y = -particle.velocity.y * dampingFactor;
            particle.position.y = glm::clamp(particle.position.y, minY, maxY);
        }
        if (nextPos.z < minZ || nextPos.z > maxZ) {
            particle.velocity.z = -particle.velocity.z * dampingFactor;
            particle.position.z = glm::clamp(particle.position.z, minZ, maxZ);
        }

        // Update position
        particle.position += particle.velocity * deltaTime;
    }
}

// Rendering function
void renderParticles(const std::vector<Particle>& particles) {
    glBegin(GL_POINTS);
    for (const auto& particle : particles) {
        glVertex3f(particle.position.x, particle.position.y, particle.position.z);
    }
    glEnd();
}