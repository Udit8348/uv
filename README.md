# uv

I'm building a vector database in C++ called "uv" (inspired by the common vector notation u and v in linear algebra). This project is my exploration into vector databases and similarity search implementations.

## What is uv?

uv is a lightweight vector database that allows you to store and query high-dimensional vectors efficiently. It's designed as a learning project to understand the fundamentals of vector databases, which are becoming increasingly important in machine learning applications.

## Features (Planned)

- Vector storage and retrieval
- Cosine similarity search
- Approximate Nearest Neighbor (ANN) search
- Basic CRUD operations
- Simple CLI interface

## Why I Built This

As a student interested in both databases and machine learning, I wanted to understand how vector databases work under the hood. While there are excellent production-ready solutions like FAISS and Milvus, building one from scratch helps me learn about:

- Vector similarity algorithms
- Efficient data structures for high-dimensional data
- Database fundamentals
- C++ optimization techniques

## Current Status

This is a work in progress. I'm actively developing the core functionality and learning along the way.
After the mid point update, I plan to add more paging and persistence to the database to that it is robust just like buzzdb.

## Building from Source

```
# Build the binary
bazel build //src:uv

# Run the binary
bazel run //src:uv

# Run the tests
bazel test //src:uv_test
``` 
