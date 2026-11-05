#include "dw4/reflected.h"
int StringChunk_ReleaseHeader();
int igObject_Destroy();
int thunk_FUN_002ed460__002ff810();
extern int DAT_00524950[4];
extern int DAT_005288e0[4];
extern int DAT_0052fde0[4];


void *FUN_0019b040(igSceneInfo *arg0, short arg1) {
    igObject *p;
    int rc;
    int *hd;

    if (arg0 != 0) {
        arg0->_vtable = (int)  &DAT_005288e0[0];
        if (&arg0->_sceneGraphList) {
            p = (igObject *)arg0->_sceneGraphList;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_cameras) {
            p = (igObject *)arg0->_cameras;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_textures) {
            p = (igObject *)arg0->_textures;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_sceneGraph) {
            p = (igObject *)arg0->_sceneGraph;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->_vtable = (int)  &DAT_0052fde0[0];
            if (arg0 != 0) {
                arg0->_vtable = (int)  &DAT_00524950[0];
                if (&arg0->_name) {
                    p = (igObject *)arg0->_name;
                    if (p != 0) {
                        hd = (int *)((char *)p - 8);
                        rc = *(int *)((char *)p - 4) - 1;
                        *(int *)((char *)p - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*hd, hd);
                        }
                    }
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
