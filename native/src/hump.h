#pragma once

#if defined(_WIN32)
  #define WRAP_API extern "C" __declspec(dllexport)
#else
  #define WRAP_API extern "C" __attribute__((visibility("default")))
#endif

// OpenCV example: blur an image file and write result.
// Returns 0 on success, nonzero on failure.
WRAP_API int ocv_gaussian_blur(const char* in_path, const char* out_path, int ksize);

// CGAL example: signed area of a polygon (x0,y0,x1,y1,...).
// n = number of points, returns area in double (positive = CCW).
WRAP_API double cgal_polygon_area(const double* xy, int n);
