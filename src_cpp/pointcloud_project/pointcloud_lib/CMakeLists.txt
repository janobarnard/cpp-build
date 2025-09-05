add_library(pointcloud_lib
    src/pointcloud_processor.cpp
)

target_include_directories(pointcloud_lib
    PUBLIC ./include
)

target_link_libraries(pointcloud_lib
    PUBLIC
        PkgConfig::PDAL
)
