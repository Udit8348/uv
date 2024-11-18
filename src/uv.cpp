#include "uv.hpp"
#include <algorithm>
#include <queue>

namespace uv
{

    void VectorDatabase::add_vector(const std::string &id, const std::vector<float> &vector)
    {
        if (vectors_.find(id) != vectors_.end())
        {
            throw std::runtime_error("Vector ID already exists");
        }
        vectors_[id] = vector;
    }

    void VectorDatabase::remove_vector(const std::string &id)
    {
        if (vectors_.find(id) == vectors_.end())
        {
            throw std::runtime_error("Vector ID not found");
        }
        vectors_.erase(id);
    }

    float VectorDatabase::cosine_similarity(
        const std::vector<float> &v1,
        const std::vector<float> &v2) const
    {
        if (v1.size() != v2.size())
        {
            throw std::runtime_error("Vector dimensions do not match");
        }

        float dot_product = 0.0f;
        float norm1 = 0.0f;
        float norm2 = 0.0f;

        for (size_t i = 0; i < v1.size(); ++i)
        {
            dot_product += v1[i] * v2[i];
            norm1 += v1[i] * v1[i];
            norm2 += v2[i] * v2[i];
        }

        if (norm1 == 0.0f || norm2 == 0.0f)
        {
            return 0.0f;
        }

        return dot_product / (std::sqrt(norm1) * std::sqrt(norm2));
    }

    float VectorDatabase::euclidean_distance(
        const std::vector<float> &v1,
        const std::vector<float> &v2) const
    {
        if (v1.size() != v2.size())
        {
            throw std::runtime_error("Vector dimensions do not match");
        }

        float sum_squares = 0.0f;
        for (size_t i = 0; i < v1.size(); ++i)
        {
            float diff = v1[i] - v2[i];
            sum_squares += diff * diff;
        }

        return std::sqrt(sum_squares);
    }

    std::vector<std::pair<std::string, float>> VectorDatabase::find_nearest(
        const std::vector<float> &query,
        size_t k)
    {
        if (k > vectors_.size())
        {
            k = vectors_.size();
        }

        std::vector<std::pair<std::string, float>> results;
        for (const auto &[id, vector] : vectors_)
        {
            float similarity = cosine_similarity(query, vector);
            results.push_back({id, similarity});
        }

        // Sort by similarity in descending order
        std::partial_sort(
            results.begin(),
            results.begin() + k,
            results.end(),
            [](const auto &a, const auto &b)
            {
                return a.second > b.second;
            });

        results.resize(k);
        return results;
    }

    size_t VectorDatabase::size() const
    {
        return vectors_.size();
    }

    const std::vector<float> &VectorDatabase::get_vector(const std::string &id) const
    {
        auto it = vectors_.find(id);
        if (it == vectors_.end())
        {
            throw std::runtime_error("Vector ID not found: " + id);
        }
        return it->second;
    }

} // namespace uv