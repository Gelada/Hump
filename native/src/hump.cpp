#include "hump.h"

// ---- OpenCV ----
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

// ---- CGAL ----
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

int ocv_gaussian_blur(const char* in_path, const char* out_path, int ksize)
{
    try {
        if (!in_path || !out_path || ksize <= 0 || ksize % 2 == 0) return 1;
        cv::Mat src = cv::imread(in_path, cv::IMREAD_COLOR);
        if (src.empty()) return 2;
        cv::Mat dst;
        cv::GaussianBlur(src, dst, cv::Size(ksize, ksize), 0);
        if (!cv::imwrite(out_path, dst)) return 3;
        return 0;
    } catch (...) {
        return 99;
    }
}

double cgal_polygon_area(const double* xy, int n)
{
    if (!xy || n < 3) return 0.0;

    using K = CGAL::Exact_predicates_inexact_constructions_kernel;
    using Point = K::Point_2;
    using Polygon = CGAL::Polygon_2<K>;

    Polygon poly;
    poly.reserve(n);
    for (int i = 0; i < n; ++i) {
        poly.push_back(Point(xy[2*i + 0], xy[2*i + 1]));
    }
    // CGAL area is signed: positive if CCW.
    return CGAL::to_double(poly.area());
}
