#include "dw4/actoranim.h"
#include "dw4/mount.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    static const char *names[] = {"H_dorumon_Skin0Shape1", "H_agumon_Skin0Shape1",
                                 "H_vmon_Skin0Shape1", "H_girumon_Skin0Shape1"};
    dw4_mount m;
    dw4_scene s;
    uint32_t size, node;
    int species;
    assert(argc == 2 && !dw4_mount_open(&m, argv[1]));
    const uint8_t *blob = dw4_mount_entry(&m, 0, 806, &size, NULL);
    assert(blob && !dw4_scene_load_actor_preview(&s, blob, size));
    for (species = 0; species < 4; species++) {
        for (node = 0; node < s.nnode; node++)
            if (s.node[node].name && !strcmp(s.node[node].name, names[species])) break;
        assert(node < s.nnode);
        dw4_actoranim *a = dw4_actoranim_open(blob, size, &s, node);
        assert(a);
        const float *p, *n;
        unsigned nv = s.mesh[s.node[node].mesh].num_verts, j;
        float *first = malloc(nv * 12);
        assert(first && !dw4_actoranim_pose(a, &s, node, 0, &p, &n));
        memcpy(first, p, nv * 12);
        assert(!dw4_actoranim_pose(a, &s, node, 0.2, &p, &n));
        double delta = 0;
        for (j = 0; j < nv * 3; j++) {
            assert(isfinite(p[j]) && fabs(p[j]) < 30 && isfinite(n[j]));
            delta += fabs(p[j] - first[j]);
        }
        assert(delta > 1); /* actual mesh motion, independent of the animated backdrop */
        assert(!dw4_actoranim_pose(a, &s, node, dw4_actoranim_duration(a), &p, &n));
        for (j = 0; j < nv * 3; j++) assert(fabs(p[j] - first[j]) < 0.0001);
        assert(dw4_actoranim_pose(a, &s, node, NAN, &p, &n) == -1);
        free(first);
        dw4_actoranim_close(a);
    }
    dw4_scene_close(&s);
    for (species = 0; species < 4; species++) {
        static const char *assets[] = {"m_dorumon.igb", "m_agumon.igb", "m_vmon.igb", "m_girumon.igb"};
        blob = dw4_mount_data(&m, assets[species], &size);
        assert(blob && !dw4_scene_load_actor_preview(&s, blob, size));
        dw4_actoranim *a = NULL;
        for (node = 0; node < s.nnode; node++) {
            if (!s.node[node].name || !strstr(s.node[node].name, "Skin0Shape1") ||
                !dw4_scene_node_texture(&s, node)) continue;
            a = dw4_actoranim_open_motion(blob, size, &s, node, "waitS");
            if (a) break;
        }
        assert(a);
        unsigned j;
        {
            dw4_actoranim *run=dw4_actoranim_open_motion(blob,size,&s,node,"runS");assert(run);
            float outgoing[16],incoming[16],blended[16];
            assert(!dw4_actoranim_bone(a,"RArm04",.2,outgoing));
            assert(!dw4_actoranim_bone(run,"RArm04",.4,incoming));
            assert(!dw4_actoranim_blend_motion(run,a,.2,1));
            assert(!dw4_actoranim_bone(run,"RArm04",.4,blended));
            for(unsigned k=0;k<16;k++)assert(fabsf(blended[k]-outgoing[k])<.0001f);
            assert(!dw4_actoranim_blend_motion(run,a,.2,0));
            assert(!dw4_actoranim_bone(run,"RArm04",.4,blended));
            for(unsigned k=0;k<16;k++)assert(fabsf(blended[k]-incoming[k])<.0001f);
            assert(!dw4_actoranim_blend_motion(run,a,.2,.5));
            assert(!dw4_actoranim_bone(run,"RArm04",.4,blended));
            for(unsigned k=0;k<16;k++)assert(isfinite(blended[k]));
            assert(dw4_actoranim_blend_motion(run,a,NAN,.5)==-1);
            dw4_actoranim_blend(run,0,0);dw4_actoranim_close(run);
        }
        /* Authored Switch masks start clear. Joining P1 must not expose P2;
         * the Shadow mask is a separate mutable instance even when its pack
         * template is shared with PC01. LOD ranges are [0,0,10000]. */
        assert(!dw4_scene_node_visible(&s,node,0));
        uint32_t pc=UINT32_MAX,shadow=UINT32_MAX,shadow_mesh=UINT32_MAX;
        for(j=0;j<s.nnode;j++) if(s.node[j].name) {
            if(!strcmp(s.node[j].name,"PC01")) pc=j;
            if(!strcmp(s.node[j].name,"Shadow")) shadow=j;
        }
        assert(pc<s.nnode && shadow<s.nnode);
        assert(!dw4_scene_switch_set(&s,pc,0,1));
        assert(dw4_scene_node_visible(&s,node,0) && dw4_scene_node_visible(&s,node,9999));
        assert(!dw4_scene_node_visible(&s,node,10000));
        assert(!dw4_scene_switch_set(&s,pc,4,1));
        assert(!dw4_scene_switch_set(&s,shadow,0,1));
        for(j=shadow+1;j<s.nnode && s.node[j].depth>s.node[shadow].depth;j++)
            if(s.node[j].mesh!=UINT32_MAX) {shadow_mesh=j;break;}
        assert(shadow_mesh<s.nnode && dw4_scene_node_visible(&s,shadow_mesh,0));
        assert(!dw4_scene_switch_set(&s,pc,0,0));
        assert(!dw4_scene_node_visible(&s,node,0) && dw4_scene_node_visible(&s,shadow_mesh,0));
        assert(dw4_scene_switch_set(&s,pc,32,1)<0);
        {
            float hand0[16], hand1[16];
            assert(!dw4_actoranim_bone(a, "RArm04", 0, hand0));
            assert(!dw4_actoranim_bone(a, "RArm04", .2, hand1));
            double movement = 0;
            for (j = 0; j < 16; j++) {
                assert(isfinite(hand0[j]) && isfinite(hand1[j]));
                movement += fabs(hand1[j]-hand0[j]);
            }
            assert(movement > .001);
            assert(dw4_actoranim_bone(a, "missing-bone", 0, hand1) == -1);
            assert(dw4_actoranim_bone(a, "RArm04", NAN, hand1) == -1);
        }
        dw4_actoranim_close(a);
        dw4_scene_close(&s);
    }
    dw4_mount_close(&m);
    puts("actor idle poses: all four rigs move, remain finite and repeat at their own durations OK");
}
