#include "uv.hpp"
#include <gtest/gtest.h>

TEST(VectorDatabaseTest, BasicOperations)
{
    uv::VectorDatabase db;

    // Test adding vectors
    db.add_vector("test1", {1.0f, 0.0f, 0.0f});
    EXPECT_EQ(db.size(), 1);

    // Test finding nearest neighbors
    std::vector<float> query = {1.0f, 0.1f, 0.0f};
    auto results = db.find_nearest(query, 1);

    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].first, "test1");
    EXPECT_NEAR(results[0].second, 0.995f, 0.01f);
}

TEST(VectorDatabaseTest, RemoveVector)
{
    uv::VectorDatabase db;

    // Add and then remove a vector
    db.add_vector("test1", {1.0f, 0.0f, 0.0f});
    EXPECT_EQ(db.size(), 1);

    // Remove the vector and verify it's gone
    db.remove_vector("test1"); // Should work fine
    EXPECT_EQ(db.size(), 0);   // Database should be empty now
}

TEST(VectorDatabaseTest, CosineSimilarity)
{
    uv::VectorDatabase db;

    // Add orthogonal vectors
    db.add_vector("x", {1.0f, 0.0f, 0.0f});
    db.add_vector("y", {0.0f, 1.0f, 0.0f});

    // Query with x-axis vector
    std::vector<float> query = {1.0f, 0.0f, 0.0f};
    auto results = db.find_nearest(query, 2);

    EXPECT_EQ(results.size(), 2);
    EXPECT_EQ(results[0].first, "x"); // Should match x-axis vector
    EXPECT_NEAR(results[0].second, 1.0f, 0.001f);
    EXPECT_EQ(results[1].first, "y"); // Should be orthogonal
    EXPECT_NEAR(results[1].second, 0.0f, 0.001f);
}