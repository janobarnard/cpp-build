#include <pointcloud_lib/pointcloud_processor.h>
#include <iostream>
#include <iomanip>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <point_cloud_file.las>" << std::endl;
        return 1;
    }

    PointCloudProcessor::PointCloudReader reader;

    std::cout << "Loading point cloud from: " << argv[1] << std::endl;

    if (!reader.loadFromFile(argv[1]))
    {
        std::cerr << "Failed to load point cloud file: " << argv[1] << std::endl;
        return 1;
    }

    size_t pointCount = reader.getPointCount();
    std::cout << "Successfully loaded " << pointCount << " points" << std::endl;

    PointCloudProcessor::Point3D minBound, maxBound;
    reader.getBounds(minBound, maxBound);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Bounds:" << std::endl;
    std::cout << "  Min: (" << minBound.x << ", " << minBound.y << ", " << minBound.z << ")" << std::endl;
    std::cout << "  Max: (" << maxBound.x << ", " << maxBound.y << ", " << maxBound.z << ")" << std::endl;

    double rangeX = maxBound.x - minBound.x;
    double rangeY = maxBound.y - minBound.y;
    double rangeZ = maxBound.z - minBound.z;

    std::cout << "Dimensions: " << rangeX << " x " << rangeY << " x " << rangeZ << std::endl;

    return 0;
}
