// begin = adder.h ============

#ifndef MATHSLIBADDER_H
#define MATHSLIBADDER_H

#if defined(WIN32) || defined(_WIN32)
  #ifdef maths_STATIC
    // building/using a static library
    #define MATHSLIBAPI
  #else
    #ifdef maths_EXPORTS
      // building the DLL
      #define MATHSLIBAPI __declspec(dllexport)
    #else
      // using the DLL
      #define MATHSLIBAPI __declspec(dllimport)
    #endif
  #endif
#else
  // non-windows
  #define MATHSLIBAPI
#endif

MATHSLIBAPI int add(int a, int b);

#endif

// end = adder.h ==============
