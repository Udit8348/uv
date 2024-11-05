#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <stdexcept>

namespace uv
{
    class VectorDatabase
    {
    public:
        // Add a vector with an ID
        void add_vector(const std::string &id, const std::vector<float> &vector);

        // Remove a vector by ID
        void remove_vector(const std::string &id);

        // Find K nearest neighbors using cosine similarity
        std::vector<std::pair<std::string, float>> find_nearest(
            const std::vector<float> &query,
            size_t k);

        // Get the number of vectors in the database
        size_t size() const;

        // Calculate Euclidean distance between two vectors
        float euclidean_distance(
            const std::vector<float> &v1,
            const std::vector<float> &v2) const;

    private:
        // Store vectors with their IDs
        std::unordered_map<std::string, std::vector<float>> vectors_;

        // Calculate cosine similarity between two vectors
        float cosine_similarity(
            const std::vector<float> &v1,
            const std::vector<float> &v2) const;
    };

} // namespace uv