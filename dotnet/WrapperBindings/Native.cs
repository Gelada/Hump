using System;
using System.Runtime.InteropServices;

internal static class Native
{
#if WINDOWS
    private const string LIB = "wrapper.dll";
#elif OSX
    private const string LIB = "libwrapper.dylib";
#else
    private const string LIB = "libwrapper.so";
#endif

    [DllImport(LIB, EntryPoint = "ocv_gaussian_blur",
        CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    internal static extern int OcvGaussianBlur(string inPath, string outPath, int ksize);

    [DllImport(LIB, EntryPoint = "cgal_polygon_area",
        CallingConvention = CallingConvention.Cdecl)]
    internal static extern double CgalPolygonArea([In] double[] xy, int n);
}