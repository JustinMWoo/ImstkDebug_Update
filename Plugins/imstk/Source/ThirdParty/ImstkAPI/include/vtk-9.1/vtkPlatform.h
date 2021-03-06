/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPlatform.h.in

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkPlatform_h
#define vtkPlatform_h

/* Whether we require large files support.  */
/* #undef VTK_REQUIRE_LARGE_FILE_SUPPORT */

/* The maximum length of a file name in bytes including the
 * terminating null.
 */
#if defined(PATH_MAX) // Usually defined on Windows
# define VTK_MAXPATH PATH_MAX
#elif defined(MAXPATHLEN)  // Usually defined on linux
# define VTK_MAXPATH MAXPATHLEN
#else
# define VTK_MAXPATH 32767 // Possible with Windows "extended paths"
#endif

#endif
