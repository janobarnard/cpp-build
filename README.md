# C++ Build Challenge

## Task
Get the `main_app` project to build.

**Download and build the main dependency.** You can install *its transitive dependencies* with `apt`.

## Structure
- `src_cpp/pointcloud_project/` - Main CMake project
- `src_cpp/pointcloud_project/main_app/` - Main application
- `src_cpp/pointcloud_project/pointcloud_lib/` - Library dependency
- `Dockerfile` - Build environment

## Main Dependency
The project requires PDAL (Point Data Abstraction Library) for processing LAS point cloud files.
