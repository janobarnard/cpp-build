#include <pointcloud_lib/pointcloud_processor.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <ranges>
#include <concepts>

template <std::floating_point T>
T calculateDistance(T x1, T y1, T z1, T x2, T y2, T z2)
{
    T dx = x2 - x1;
    T dy = y2 - y1;
    T dz = z2 - z1;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <point_cloud_file.las>" << std::endl;
        return 1;
    }

    PointCloudProcessor::PointCloudReader reader;

    if (!reader.loadFromFile(argv[1]))
    {
        std::cerr << "Failed to load point cloud file: " << argv[1] << std::endl;
        return 1;
    }

    auto points = reader.getPoints();
    std::cout << "Loaded " << points.size() << " points" << std::endl;

    if (points.size() < 10)
    {
        std::cout << "Not enough points for analysis" << std::endl;
        return 0;
    }

    auto first10Points = points | std::views::take(10);

    std::cout << "First 10 points:" << std::endl;
    size_t i = 0;
    for (const auto &point : first10Points)
    {
        std::cout << "Point " << i++ << ": ("
                  << point.x << ", " << point.y << ", " << point.z << ")" << std::endl;
    }

    std::vector<double> distances;
    for (size_t j = 0; j < points.size() - 1; ++j)
    {
        distances.push_back(calculateDistance(points[j].x, points[j].y, points[j].z,
                                              points[j + 1].x, points[j + 1].y, points[j + 1].z));
    }

    if (!distances.empty())
    {
        auto [min_dist, max_dist] = std::ranges::minmax(distances);
        std::cout << "Distance range between adjacent points: "
                  << min_dist << " to " << max_dist << std::endl;
    }

    return 0;
}