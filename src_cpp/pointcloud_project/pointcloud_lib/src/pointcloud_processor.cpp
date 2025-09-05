#include <pointcloud_lib/pointcloud_processor.h>
#include <pdal/PointTable.hpp>
#include <pdal/PointView.hpp>
#include <pdal/io/LasReader.hpp>
#include <pdal/Dimension.hpp>
#include <memory>
#include <algorithm>
#include <limits>

namespace PointCloudProcessor
{

    class PointCloudReader::Impl
    {
    public:
        std::vector<Point3D> points;

        bool loadFromFile(const std::string &filename)
        {
            pdal::PointTable table;
            pdal::LasReader reader;
            reader.prepare(table);

            pdal::PointViewSet viewSet = reader.execute(table);
            if (viewSet.empty())
            {
                return false;
            }

            pdal::PointViewPtr view = *viewSet.begin();
            points.clear();
            points.reserve(view->size());

            for (pdal::PointId i = 0; i < view->size(); ++i)
            {
                Point3D pt;
                pt.x = view->getFieldAs<double>(pdal::Dimension::Id::X, i);
                pt.y = view->getFieldAs<double>(pdal::Dimension::Id::Y, i);
                pt.z = view->getFieldAs<double>(pdal::Dimension::Id::Z, i);
                points.push_back(pt);
            }

            return true;
        }
    };

    PointCloudReader::PointCloudReader() : pImpl(new Impl()) {}

    PointCloudReader::~PointCloudReader()
    {
        delete pImpl;
    }

    bool PointCloudReader::loadFromFile(const std::string &filename)
    {
        return pImpl->loadFromFile(filename);
    }

    std::vector<Point3D> PointCloudReader::getPoints() const
    {
        return pImpl->points;
    }

    size_t PointCloudReader::getPointCount() const
    {
        return pImpl->points.size();
    }

    void PointCloudReader::getBounds(Point3D &min, Point3D &max) const
    {
        if (pImpl->points.empty())
        {
            min = max = {0.0, 0.0, 0.0};
            return;
        }

        min = max = pImpl->points[0];

        for (const auto &point : pImpl->points)
        {
            min.x = std::min(min.x, point.x);
            min.y = std::min(min.y, point.y);
            min.z = std::min(min.z, point.z);

            max.x = std::max(max.x, point.x);
            max.y = std::max(max.y, point.y);
            max.z = std::max(max.z, point.z);
        }
    }

}