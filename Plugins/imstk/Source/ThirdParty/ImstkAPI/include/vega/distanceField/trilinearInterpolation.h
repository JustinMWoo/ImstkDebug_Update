/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "distance field" library , Copyright (C) 2007 CMU, 2018 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
 * http://www.jernejbarbic.com/vega                                      *
 *                                                                       *
 * Research: Jernej Barbic, Hongyi Xu, Yijing Li,                        *
 *           Danyong Zhao, Bohan Wang,                                   *
 *           Fun Shing Sin, Daniel Schroeder,                            *
 *           Doug L. James, Jovan Popovic                                *
 *                                                                       *
 * Funding: National Science Foundation, Link Foundation,                *
 *          Singapore-MIT GAMBIT Game Lab,                               *
 *          Zumberge Research and Innovation Fund at USC,                *
 *          Sloan Foundation, Okawa Foundation,                          *
 *          USC Annenberg Foundation                                     *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of the BSD-style license that is            *
 * included with this library in the file LICENSE.txt                    *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the file     *
 * LICENSE.TXT for more details.                                         *
 *                                                                       *
 *************************************************************************/

namespace vega
{
/*
  Trilinear interpolation.
*/

#define TRILINEAR_INTERPOLATION(wx,wy,wz,v000,v100,v110,v010,v001,v101,v111,v011) \
( (wx) * (wy) * (wz) *             (v111) + \
  (wx) * (wy) * (1-(wz)) *         (v110) + \
  (wx) * (1-(wy)) * (wz) *         (v101) + \
  (wx) * (1-(wy)) * (1-(wz)) *     (v100) + \
  (1-(wx)) * (wy) * (wz) *         (v011) + \
  (1-(wx)) * (wy) * (1-(wz)) *     (v010) + \
  (1-(wx)) * (1-(wy)) * (wz) *     (v001) + \
  (1-(wx)) * (1-(wy)) * (1-(wz)) * (v000))

#define GRADIENT_COMPONENT_X(wx,wy,wz,v000,v100,v110,v010,v001,v101,v111,v011) \
  (((wy) * (wz) *             (v111) + \
    (wy) * (1-(wz)) *         (v110) + \
    (1-(wy)) * (wz) *         (v101) + \
    (1-(wy)) * (1-(wz)) *     (v100) + \
    (-1) * (wy) * (wz) *         (v011) + \
    (-1) * (wy) * (1-(wz)) *     (v010) + \
    (-1) * (1-(wy)) * (wz) *     (v001) + \
    (-1) * (1-(wy)) * (1-(wz)) * (v000) ) / gridX)

#define GRADIENT_COMPONENT_Y(wx,wy,wz,v000,v100,v110,v010,v001,v101,v111,v011) \
  (((wx) * (wz) *             (v111) + \
    (wx) * (1-(wz)) *         (v110) + \
    (wx) * (-1) * (wz) *         (v101) + \
    (wx) * (-1) * (1-(wz)) *     (v100) + \
    (1-(wx)) * (wz) *         (v011) + \
    (1-(wx)) * (1-(wz)) *     (v010) + \
    (1-(wx)) * (-1) * (wz) *     (v001) + \
    (1-(wx)) * (-1) * (1-(wz)) * (v000)) / gridY)
  
#define GRADIENT_COMPONENT_Z(wx,wy,wz,v000,v100,v110,v010,v001,v101,v111,v011) \
  (((wx) * (wy) *                (v111) + \
    (wx) * (wy) * (-1) *         (v110) + \
    (wx) * (1-(wy)) *            (v101) + \
    (wx) * (1-(wy)) * (-1) *     (v100) + \
    (1-(wx)) * (wy) *            (v011) + \
    (1-(wx)) * (wy) * (-1) *     (v010) + \
    (1-(wx)) * (1-(wy)) *        (v001) + \
    (1-(wx)) * (1-(wy)) * (-1) * (v000)) / gridZ)
} // namespace vega
