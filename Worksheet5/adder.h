// begin = adder.h ============

/** @file
 *  This file contains the declarations of all exported functions in the maths library.
 */
/** Adding function
 *  This function adds two numbers.
 *  @param a is the first number
 *  @param b is the second number
 *  @return sum of a and b
 */

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
