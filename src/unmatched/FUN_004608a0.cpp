#include "dw4/reflected.h"
struct V { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(int); virtual void v31(); virtual void v32(void*); };
struct Frame { void *f0; char pad[228]; int f232; void *f236; };
extern "C" {
int FUN_00100610(...);
void *FUN_001007e0(...);
void *FUN_00238110(...);
int FUN_00460e00(...);
int FUN_00460f20(...);
int StringChunk_ReleaseHeader(...);
extern int DAT_004e1170[4];
extern Frame *DAT_0056dc50[4];
void FUN_004608a0(igViewerRenderer *arg0) {
    bool a1 = true;
    bool a0 = true;
    igViewerParameters *x = (igViewerParameters *)arg0->_parameters;
    if (x->_useSceneLights == 0 && x->_useHeadLight == 0) a0 = false;
    if (!a0 && x->_useHeadLightSpecular == 0) a1 = false;
    arg0->_lightingState = a1;
    x = (igViewerParameters *)arg0->_parameters;
    if (x->_useHeadLight != 0 || x->_useHeadLightSpecular != 0) {
        ((V *)arg0->_headlightStateAttr)->v30(1);
        if (((igViewerParameters *)arg0->_parameters)->_useHeadLightSpecular != 0) {
            if (DAT_0056dc50[0] == 0) {
                Frame *f = (Frame *)FUN_001007e0(240);
                if (f != 0) f = (Frame *)FUN_00238110(f);
                DAT_0056dc50[0] = f;
            }
            DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
            ((V *)arg0->_headlightAttr)->v32((char *)DAT_0056dc50[0] + 116);
            if (DAT_0056dc50[0] != 0) {
                if (--DAT_0056dc50[0]->f232 <= 0) {
                    Frame *s1 = DAT_0056dc50[0];
                    if (s1 != 0) {
                        if (&s1->f236) {
                            void *p = s1->f236;
                            if (p != 0) {
                                int *h = (int *)((char *)(p) - 8);
                                int rc = *(int *)((char *)(p) - 4) - 1;
                                *(int *)((char *)(p) - 4) = rc;
                                if (rc == 0) {
                                    StringChunk_ReleaseHeader(*h, h);
                                }
                            }
                        }
                        if (s1 != 0) {
                            void *p = s1->f0;
                            if (p != 0) {
                                int *h = (int *)((char *)(p) - 8);
                                int rc = *(int *)((char *)(p) - 4) - 1;
                                *(int *)((char *)(p) - 4) = rc;
                                if (rc == 0) {
                                    StringChunk_ReleaseHeader(*h, h);
                                }
                            }
                        }
                        FUN_00100610(s1);
                    }
                    DAT_0056dc50[0] = 0;
                }
            }
        } else {
            ((V *)arg0->_headlightAttr)->v32(&DAT_004e1170[0]);
        }
    } else {
        ((V *)arg0->_headlightStateAttr)->v30(0);
    }
    ((V *)arg0->_lightingAttr)->v30(arg0->_lightingState);
    FUN_00460e00(arg0, (V *)arg0->_lightingAttr);
    FUN_00460f20(arg0, (V *)arg0->_lightingAttr, ((bool)arg0->_lightingState) ^ 1);
}
}
