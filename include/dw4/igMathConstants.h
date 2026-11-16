#ifndef DW4_IGMATHCONSTANTS_H
#define DW4_IGMATHCONSTANTS_H

/* The maths library's constant vectors and matrices (zero, one, the axes and the identity). */
#include "dw4/igMath.h"
#include "dw4/igVec3f.h"
#include "dw4/igMatrix44d.h"
#include "dw4/igMatrix44f.h"

extern "C" {
extern const igMatrix44d g_matrix44dIdentity;
extern const igMatrix44d g_matrix44dZero;
extern const igMatrix44f g_matrix44Identity;
extern const igMatrix44f g_matrix44Zero;
extern const igVec2d g_vec2dZero;
extern const igVec2d g_vec2dXAxis;
extern const igVec2d g_vec2dYAxis;
extern const igVec2f g_vec2Zero;
extern const igVec2f g_vec2XAxis;
extern const igVec2f g_vec2YAxis;
extern const igVec3d g_vec3dZero;
extern const igVec3d g_vec3dOne;
extern const igVec3d g_vec3dXAxis;
extern const igVec3d g_vec3dYAxis;
extern const igVec3d g_vec3dZAxis;
extern const igVec3f g_vec3Zero;
extern const igVec3f g_vec3One;
extern const igVec3f g_vec3XAxis;
extern const igVec3f g_vec3YAxis;
extern const igVec3f g_vec3ZAxis;
extern const igVec4d g_vec4dZero;
extern const igVec4d g_vec4dOne;
extern const igVec4d g_vec4dXAxis;
extern const igVec4d g_vec4dYAxis;
extern const igVec4d g_vec4dZAxis;
extern const igVec4d g_vec4dWAxis;
extern const igVec4f g_vec4Zero;
extern const igVec4f g_vec4One;
extern const igVec4f g_vec4XAxis;
extern const igVec4f g_vec4YAxis;
extern const igVec4f g_vec4ZAxis;
extern const igVec4f g_vec4WAxis;
}

#endif
