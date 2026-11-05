/* A rotated, nonuniformly scaled animation must scale in local axes. */
#include "dw4/scene.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const int64_t times[] = {0};
    const float translation[] = {5, 6, 7};
    const float scale[] = {2, 3, 4};
    const float rotation[] = {0, 0, 0.7071067812f, 0.7071067812f};
    /* Row-vector rotation: local +X turns toward -Y.  Scale first, then rotate,
     * then translate: (1,0,0) -> (2,0,0) -> (0,-2,0) -> (5,4,7). */
    const float points[3][3] = {{5, 4, 7}, {8, 6, 7}, {5, 6, 11}};
    dw4_scene s;
    dw4_scene_node node;
    float world[16];
    int axis, component;

    memset(&s, 0, sizeof s);
    memset(&node, 0, sizeof node);
    s.node = &node;
    s.nnode = 1;
    node.parent = 0xFFFFFFFFu;
    node.has_seq = 1;
    node.seq.times = times;
    node.seq.trans = translation;
    node.seq.scale = scale;
    node.seq.rot = rotation;
    node.seq.ntimes = node.seq.ntrans = node.seq.nscale = node.seq.nrot = 1;
    if (dw4_scene_node_world(&s, 0, world) != 0)
        return 1;
    for (axis = 0; axis < 3; axis++)
        for (component = 0; component < 3; component++)
            if (fabsf(world[4 * axis + component] + world[12 + component] -
                      points[axis][component]) > 0.0001f) {
                fprintf(stderr, "animated transform scales in the wrong axes\n");
                return 1;
            }
    /* Camera record 2437's degree-XYZ keys reproduce its stored rotation. */
    {
        const float angles[] = {-60, -10, 0, 0};
        const float expected[9] = {0.9848078f, 0, 0.1736482f,
            0.1503837f, 0.5f, -0.8528685f, -0.0868241f, 0.8660254f, 0.4924039f};
        node.seq.scale = NULL; node.seq.nscale = 0;
        node.seq.rot = angles; node.seq.rotation_euler = 1;
        assert(!dw4_scene_node_world(&s, 0, world));
        for (axis = 0; axis < 3; axis++) for (component = 0; component < 3; component++)
            assert(fabsf(world[4*axis+component]-expected[3*axis+component]) < 0.0001f);
    }
    {
        /* Original 1df040 yields 158/317 ticks at this midpoint. Full-ns
         * division gives .5 and moves the authored translation to 5 instead. */
        const int64_t keys[]={12345,83345681};
        const float move[]={0,0,0,10,0,0};
        memset(&node.seq,0,sizeof node.seq);
        node.seq.times=keys;node.seq.ntimes=2;
        node.seq.trans=move;node.seq.ntrans=2;
        dw4_scene_set_time(&s,41679013);
        assert(!dw4_scene_node_world(&s,0,world));
        assert(fabsf(world[12]-4.984227f)<.00001f);
        /* The explicit camera adapter retains its own degree-XYZ timeline. */
        node.seq.rotation_euler=1;
        assert(!dw4_scene_node_world(&s,0,world));assert(world[12]==5);
    }
    {const int64_t keys[]={0,3313500160LL};
        node.seq.times=keys;node.seq.ntimes=2;node.seq.duration_ns=3316666603LL;node.seq.play_mode=0;
        assert(dw4_scene_node_loop_time(&s,0,3316666603LL)==3316666603LL);
        assert(dw4_scene_node_loop_time(&s,0,3316666604LL)==1);
        assert(dw4_scene_node_loop_time(&s,0,6633333206LL)==0);
    }
    puts("  scene: local scale, quaternion, quantized interpolation, authored strict-end ambient loop and explicit camera Euler evaluation ok");
    return 0;
}
