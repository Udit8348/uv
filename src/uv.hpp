#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <stdexcept>
#include <mutex>

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

        // Get a vector by ID
        const std::vector<float> &get_vector(const std::string &id) const;

        // Save the database to a file
        void save_to_file(const std::string &filepath);

        // Load the database from a file
        void load_from_file(const std::string &filepath);

        float calculate_similarity(const std::vector<float> &vec1, const std::vector<float> &vec2)
        {
            return cosine_similarity(vec1, vec2);
        }

    private:
        std::unordered_map<std::string, std::vector<float>> vectors_;
        std::mutex mtx_;

        float cosine_similarity(const std::vector<float> &v1, const std::vector<float> &v2) const;
    };

} // namespace uv