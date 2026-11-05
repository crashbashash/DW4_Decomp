#ifndef DW4_HITBOX_H
#define DW4_HITBOX_H
/* minXYZ,maxXYZ. Original EE arithmetic; no renderer or controller updates. */
void dw4_hitbox_transform(float box[6],const float matrix[16]);
void dw4_hitbox_center(const float box[6],float center[3]);
/* 3908e0: transform the centre but retain original world-axis half extents. */
void dw4_hitbox_fixed_world(const float local[6],const float matrix[16],float world[6]);
int dw4_hitbox_intersects(const float a[6],const float b[6]);
/* Original hub Cross request: offset(0,4,7), world-axis size(3,3,3). */
void dw4_hitbox_talk_probe(const float matrix[16],float world[6]);
/* A bullet volume: `offset` transformed by the source matrix, world-axis half extents size/2 (the talk probe is offset (0,4,7), size (3,3,3)). */
void dw4_hitbox_bullet(const float matrix[16],const float offset[3],const float size[3],float world[6]);
#endif
