#pragma once
#include "uv.hpp"
#include <string>
#include <vector>
#include <memory>

namespace uv
{

    class QueryResult
    {
    public:
        std::vector<std::pair<std::string, float>> results;
    };

    class QueryProcessor
    {
    public:
        explicit QueryProcessor(VectorDatabase &db) : db_(db) {}

        // Process a single query file
        QueryResult process_file(const std::string &filename);

        // Process individual commands
        QueryResult process_find(const std::string &query_text);
        QueryResult process_filter(const std::string &filter_text,
                                   const QueryResult &previous_results,
                                   bool filter_in);

    private:
        VectorDatabase &db_;
        // Mock embedding function (replace with real embedding later)
        std::vector<float> get_embedding(const std::string &text);
    };

} // namespace uv