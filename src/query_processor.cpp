#include "query_processor.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

namespace uv
{

    QueryResult QueryProcessor::process_file(const std::string &filename)
    {
        if (filename.substr(filename.length() - 5) != ".uvql")
        {
            throw std::runtime_error("Invalid file extension. Expected .uvql");
        }

        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file: " + filename);
        }

        std::string line;
        QueryResult current_result;
        bool has_find = false;

        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string command;
            iss >> command;

            if (command == "FIND")
            {
                if (has_find)
                {
                    throw std::runtime_error("Multiple FIND commands not supported");
                }
                std::string query_text;
                std::getline(iss >> std::ws, query_text);
                current_result = process_find(query_text);
                has_find = true;
            }
            else if (command == "FILTER")
            {
                if (!has_find)
                {
                    throw std::runtime_error("FILTER must follow a FIND command");
                }
                std::string direction, filter_text;
                iss >> direction;
                std::getline(iss >> std::ws, filter_text);

                bool filter_in = (direction == "IN");
                if (direction != "IN" && direction != "OUT")
                {
                    throw std::runtime_error("FILTER must specify IN or OUT");
                }

                current_result = process_filter(filter_text, current_result, filter_in);
            }
        }

        return current_result;
    }

    QueryResult QueryProcessor::process_find(const std::string &query_text)
    {
        auto query_vector = get_embedding(query_text);
        auto results = db_.find_nearest(query_vector, 100); // Get top 100 results
        return QueryResult{results};
    }

    QueryResult QueryProcessor::process_filter(const std::string &filter_text,
                                               const QueryResult &previous_results,
                                               bool filter_in)
    {
        auto filter_vector = get_embedding(filter_text);
        std::vector<std::pair<std::string, float>> filtered_results;

        for (const auto &result : previous_results.results)
        {
            auto vector = db_.get_vector(result.first);
            float similarity = db_.cosine_similarity(filter_vector, vector);

            if ((filter_in && similarity > 0.5f) || (!filter_in && similarity <= 0.5f))
            {
                filtered_results.push_back(result);
            }
        }

        return QueryResult{filtered_results};
    }

    std::vector<float> QueryProcessor::get_embedding(const std::string &text)
    {
        // Mock implementation - replace with real embedding
        // For now, return a simple 3D vector
        return {1.0f, 0.0f, 0.0f};
    }

} // namespace uv