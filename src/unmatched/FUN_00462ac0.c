#include "dw4/reflected.h"
int FUN_00100610();
int FUN_001007e0();
int FUN_00238110();
int FUN_004578c0();
int FUN_0045f930();
int FUN_00462a50();
int FUN_00462cf0();
int FUN_00464540();
int StringChunk_ReleaseHeader();
int igObject_Destroy();
extern int DAT_0058cad8[4];
extern int DAT_0058cb00[4];
extern int DAT_0058cb08[4];
typedef struct Frame {
    void *f0;
    char pad[56];
    unsigned char f60;
    char pad2[171];
    int f232;
    void *f236;
} Frame;
extern Frame *DAT_0056dc50[4];
void FUN_00462ac0(igViewerSceneInfoManager *arg0) {
    int sp50[3];
    int sp40[3];
    int sp30[3];
    Frame *f;
    Frame *g;
    Frame *s0;
    igViewerParameters *v;
    igObject *a;
    int *pp;
    void *p;
    int *h;
    int rc;
    FUN_00462a50();
    FUN_00464540(arg0->_viewManager, ((igViewerParameters *)arg0->_parameters)->_scene);
    FUN_00462cf0(arg0);
    FUN_0045f930(arg0->_viewerRenderer);
    v = (igViewerParameters *)arg0->_parameters;
    pp = &v->_selectedObject;
    a = (igObject *)*pp;
    if (a != 0) {
        a->_refCount = (int)a->_refCount - 1;
        if (((unsigned long long)((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(a);
        }
    }
    *pp = 0;
    sp50[0] = 2;
    sp50[1] = 0;
    sp50[2] = DAT_0058cb00[0];
    FUN_004578c0(arg0->_parameters, sp50);
    ((igViewerParameters *)arg0->_parameters)->_timeOperation = 1;
    sp40[0] = 2;
    sp40[1] = 0;
    sp40[2] = DAT_0058cb08[0];
    FUN_004578c0(arg0->_parameters, sp40);
    if (DAT_0056dc50[0] == 0) {
        f = (Frame *)FUN_001007e0(240);
        if (f != 0) f = (Frame *)FUN_00238110(f);
        DAT_0056dc50[0] = f;
    }
    DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
    v = (igViewerParameters *)arg0->_parameters;
    g = DAT_0056dc50[0];
    if (((igObjectList *)v->_cameras)->_count > 0 && g->f60 != 0) {
        v->_operationMode = v->_firstCameraMode;
    } else {
        v->_operationMode = 1;
    }
    sp30[1] = 0;
    sp30[0] = 2;
    sp30[2] = DAT_0058cad8[0];
    FUN_004578c0(arg0->_parameters, sp30);
    if (DAT_0056dc50[0] != 0) {
        if (--DAT_0056dc50[0]->f232 <= 0) {
            f = DAT_0056dc50[0];
            if (f != 0) {
                if (&f->f236) {
                    p = f->f236;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                if (f != 0) {
                    p = f->f0;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                FUN_00100610(f);
            }
            DAT_0056dc50[0] = 0;
        }
    }
}
