#include "dw4/reflected.h"
extern "C" {
int FUN_00100610(...);
void **FUN_001007e0(...);
int FUN_001c5d10(...);
int FUN_001d65e0(...);
int FUN_001d6700(...);
void **FUN_00238110(...);
int igObject_IsKindOf(...);
int FUN_004578c0(...);
int FUN_00460330(...);
int ObjectList_AppendRetainedList(...);
int StringChunk_ReleaseHeader(...);
int igSceneInfo_GetMetaObject(...);
extern float DAT_004e1058[16];
extern float DAT_004e105c[16];
extern float DAT_004e1060[16];
struct Frame;
extern struct Frame *DAT_0056dc50[16];
extern int DAT_0058c9f0[16];
extern int DAT_0058c9f8[16];
extern int DAT_0058cae8[16];
extern int DAT_0058caf0[16];
extern int DAT_0058caf8[16];

struct Frame {
    void *f0;
    char pad[76];
    float f80;
    float f84;
    float f88;
    char pad2[140];
    int f232;
    void *f236;
};
struct T3 { int a; int b; int c; };

int FUN_00462670(igViewerSceneInfoManager *arg0, igSceneInfo *arg1) {
    T3 t0, t1, t2, t3, t4;
    Frame *s0;
    bool b;
    bool a;
    if (igObject_IsKindOf(arg1, igSceneInfo_GetMetaObject()) != 0) {
        if (arg1->_sceneGraph == 0) {
            return 0;
        }
        if (DAT_0056dc50[0] == 0) {
            void **v = FUN_001007e0(0xF0);
            if (v != 0) {
                v = FUN_00238110(v);
            }
            DAT_0056dc50[0] = (Frame *)v;
        }
        DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
        s0 = DAT_0056dc50[0];
        if (arg1 != 0 && arg1->_animationBegin == 0 && arg1->_animationEnd == 0) {
            FUN_001d6700(arg1);
        }
        if (arg1->_cameras == 0) {
            FUN_001d65e0(arg1);
        }
        FUN_001c5d10(((igViewerParameters *)arg0->_parameters)->_scene, arg1->_sceneGraph);
        t0.a = 2;
        t0.b = 0;
        t0.c = DAT_0058c9f0[0];
        FUN_004578c0(arg0->_parameters, &t0);
        FUN_00460330(arg0->_viewerRenderer);
        b = false;
        float f2 = s0->f80;
        a = false;
        if (!(f2 != DAT_004e1058[0])) { if (!(s0->f84 != DAT_004e105c[0])) { a = true; } }
        if (a && s0->f88 == DAT_004e1060[0]) {
            b = true;
        }
        if (b) {
            igViewerParameters *o = (igViewerParameters *)arg0->_parameters;
            *(float *)&o->_upVector[0] = *(float *)&arg1->_upVector[0];
            *(float *)&o->_upVector[1] = *(float *)&arg1->_upVector[1];
            *(float *)&o->_upVector[2] = *(float *)&arg1->_upVector[2];
        } else {
            igViewerParameters *o = (igViewerParameters *)arg0->_parameters;
            *(float *)&o->_upVector[0] = f2;
            *(float *)&o->_upVector[1] = s0->f84;
            *(float *)&o->_upVector[2] = s0->f88;
        }
        t1.a = 2;
        t1.b = 0;
        t1.c = DAT_0058c9f8[0];
        FUN_004578c0(arg0->_parameters, &t1);
        ObjectList_AppendRetainedList(((igViewerParameters *)arg0->_parameters)->_cameras, arg1->_cameras);
        t2.a = 2;
        t2.b = 0;
        t2.c = DAT_0058cae8[0];
        FUN_004578c0(arg0->_parameters, &t2);
        {
            igViewerParameters *o = (igViewerParameters *)arg0->_parameters;
            long long *q = &o->_beginTime;
            if (o->_beginTime == 0) {
                *q = arg1->_animationBegin;
            }
        }
        t3.a = 2;
        t3.b = 0;
        t3.c = DAT_0058caf0[0];
        FUN_004578c0(arg0->_parameters, &t3);
        {
            igViewerParameters *o = (igViewerParameters *)arg0->_parameters;
            long long *q = &o->_endTime;
            if (o->_endTime == 0) {
                *q = arg1->_animationEnd;
            }
        }
        t4.a = 2;
        t4.b = 0;
        t4.c = DAT_0058caf8[0];
        FUN_004578c0(arg0->_parameters, &t4);
        if (DAT_0056dc50[0] != 0) {
            int rc = DAT_0056dc50[0]->f232 - 1;
            DAT_0056dc50[0]->f232 = rc;
            if (rc <= 0) {
                Frame *f = DAT_0056dc50[0];
                if (f != 0) {
                    if (&f->f236) {
                        void *p = f->f236;
                        if (p != 0) {
                            int *h = (int *)((char *)p - 8);
                            int r = *(int *)((char *)p - 4) - 1;
                            *(int *)((char *)p - 4) = r;
                            if (r == 0) {
                                StringChunk_ReleaseHeader(*h, h);
                            }
                        }
                    }
                    if (f != 0) {
                        void *p = f->f0;
                        if (p != 0) {
                            int *h = (int *)((char *)p - 8);
                            int r = *(int *)((char *)p - 4) - 1;
                            *(int *)((char *)p - 4) = r;
                            if (r == 0) {
                                StringChunk_ReleaseHeader(*h, h);
                            }
                        }
                    }
                    FUN_00100610(f);
                }
                DAT_0056dc50[0] = 0;
            }
        }
        return 1;
    }
    return 0;
}
}
