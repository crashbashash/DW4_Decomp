/* Disc-backed character preview animation; no savestate or captured geometry. */
#ifndef DW4_ACTORANIM_H
#define DW4_ACTORANIM_H
#include "dw4/scene.h"
typedef struct dw4_actoranim dw4_actoranim;
dw4_actoranim *dw4_actoranim_open(const uint8_t *blob, uint32_t size, const dw4_scene *scene, uint32_t node);
dw4_actoranim *dw4_actoranim_open_motion(const uint8_t *blob, uint32_t size,
                                        const dw4_scene *scene, uint32_t node, const char *motion);
/* Full-area path: select skeletons and motions only from the owning original
 * beAction2Info._animationDatabase, avoiding unrelated equal-size rigs. */
dw4_actoranim *dw4_actoranim_open_motion_database(const uint8_t *,uint32_t,const dw4_scene *,uint32_t node,const char *motion,uint32_t database,char *error,size_t cap);
double dw4_actoranim_duration(const dw4_actoranim *a);
/* Controller duration is the igAnimation int64, not the compressed stream float. */
int64_t dw4_actoranim_duration_ns(const dw4_actoranim *a);
void dw4_actoranim_loop(dw4_actoranim *a, int enabled);
/* Blend a previous local pose into the evaluated pose before skeletal composition. */
void dw4_actoranim_blend(dw4_actoranim *a, double from, float weight);
/* Blend a compatible outgoing motion before skeletal composition. Borrowed
 * source outlives evaluation; this does not advance either animation clock. */
int dw4_actoranim_blend_motion(dw4_actoranim *,dw4_actoranim *,double,float);
void dw4_actoranim_close(dw4_actoranim *a);
/* Actor-local bone matrix, including non-skinning attachment bones. */
int dw4_actoranim_bone(dw4_actoranim *a, const char *name, double seconds, float matrix[16]);
/* Output arrays are owned by a and remain valid until the next evaluation. */
int dw4_actoranim_pose(dw4_actoranim *a, const dw4_scene *s, uint32_t node, double seconds,
                       const float **positions, const float **normals);
#endif
