#include "uv.hpp"
#include "query_processor.hpp"
#include <iostream>
#include <string>
#include <thread>

void print_usage()
{
    std::cout << "Usage: uv <query_file.uvql>\n";
}

// Example function to save the database in a separate thread
void save_database(uv::VectorDatabase &db, const std::string &filepath)
{
    db.save_to_file(filepath);
}

// Example function to load the database in a separate thread
void load_database(uv::VectorDatabase &db, const std::string &filepath)
{
    db.load_from_file(filepath);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        print_usage();
        return 1;
    }

    std::string query_file = argv[1];

    try
    {
        uv::VectorDatabase db;
        // Add some sample vectors
        db.add_vector("cat_photo", {1.0f, 0.0f, 0.0f});
        db.add_vector("dog_photo", {0.0f, 1.0f, 0.0f});
        db.add_vector("bird_photo", {0.0f, 0.0f, 1.0f});

        std::thread save_thread(save_database, std::ref(db), "database.txt");
        std::thread load_thread(load_database, std::ref(db), "database.txt");

        save_thread.join();
        load_thread.join();

        uv::QueryProcessor processor(db);
        auto results = processor.process_file(query_file);

        // Print results
        std::cout << "Query results:\n";
        for (const auto &[id, similarity] : results.results)
        {
            std::cout << "ID: " << id << ", Similarity: " << similarity << "\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}