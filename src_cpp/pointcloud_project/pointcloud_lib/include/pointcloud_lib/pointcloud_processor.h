#pragma once

#include <string>
#include <vector>

namespace PointCloudProcessor
{

    struct Point3D
    {
        double x, y, z;
    };

    class PointCloudReader
    {
    public:
        PointCloudReader();
        ~PointCloudReader();

        bool loadFromFile(const std::string &filename);
        std::vector<Point3D> getPoints() const;
        size_t getPointCount() const;
        void getBounds(Point3D &min, Point3D &max) const;

    private:
        class Impl;
        Impl *pImpl;
    };

}