#include "uv.hpp"
#include <iostream>

int main()
{
    uv::VectorDatabase db;

    // Add some example vectors
    db.add_vector("vec1", {1.0f, 0.0f, 0.0f});
    db.add_vector("vec2", {0.0f, 1.0f, 0.0f});
    db.add_vector("vec3", {0.0f, 0.0f, 1.0f});

    // Query vector
    std::vector<float> query = {1.0f, 1.0f, 0.0f};

    // Find 2 nearest neighbors
    auto results = db.find_nearest(query, 2);

    std::cout << "Nearest neighbors to query vector:\n";
    for (const auto &[id, similarity] : results)
    {
        std::cout << "ID: " << id << ", Similarity: " << similarity << "\n";
    }

    return 0;
}