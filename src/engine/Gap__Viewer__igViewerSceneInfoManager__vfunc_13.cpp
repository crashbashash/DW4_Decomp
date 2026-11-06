#include "dw4/reflected.h"
#include "dw4/igobject_release.h"

extern "C" {
int Gap__Core__igObject__vfunc_11(...);
int FUN_00100610(...);
void **FUN_001007e0(...);
int FUN_001b1e50(...);
void **FUN_00238110(...);
int FUN_004573c0(...);
int FUN_004573d0(...);
int FUN_004573f0(...);
int FUN_00457e90(...);
int FUN_0045ec90(...);
int FUN_00463c90(...);
int StringChunk_ReleaseHeader(...);
int igObject_Destroy(...);
void *memset(void *, int, unsigned int);
extern char DAT_004d1ac8[16];
extern char DAT_004d1ad8[16];
extern char DAT_004d1ae8[16];
extern char DAT_004d1af8[16];
extern char DAT_004d1b08[16];
extern char DAT_004d1b18[16];
extern char DAT_004d1b28[16];
extern char DAT_004d1b38[16];
extern char DAT_004d1b48[16];
extern char DAT_004d1b58[16];
extern char DAT_004d1b68[16];
extern char DAT_004d1b78[16];
extern char DAT_004d1b88[16];
struct Frame;
extern struct Frame *DAT_0056dc50[16];
void Gap__Viewer__igViewerSceneInfoManager__vfunc_13(igViewerSceneInfoManager *arg0);
}

/* igViewerRenderer-family objects: the shared parameters reference sits at +12 */
struct RendererLink {
    char pad[12];
    igObject *parameters;
};

struct Frame {
    void *f0;
    unsigned char f4;  /* +4 */
    unsigned char f5;  /* +5 */
    char pad6[208];
    unsigned char f214; /* +214 */
    char pad215[17];
    int f232;
    void *f236;
};

#define BIND(setter, receiver, name, ...)                                                 \
    {                                                                                     \
        igObject *sp;                                                                     \
        FUN_0045ec90(&sp, arg0->_guiFactory, arg0, name);                                 \
        setter(receiver, __VA_ARGS__, sp);                                                \
        IG_OBJECT_RELEASE(sp);                                                                \
    }

void Gap__Viewer__igViewerSceneInfoManager__vfunc_13(igViewerSceneInfoManager *arg0) {
    Gap__Core__igObject__vfunc_11(arg0);
    if (DAT_0056dc50[0] == 0) {
        void **v = FUN_001007e0(0xF0);
        if (v != 0) {
            v = FUN_00238110(v);
        }
        DAT_0056dc50[0] = (Frame *)v;
    }
    DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
    {
        Frame *frame = DAT_0056dc50[0];
        ((igViewerParameters *)arg0->_parameters)->_showBoundingBox = frame->f4;
        ((igViewerParameters *)arg0->_parameters)->_showNormals = frame->f5;
        ((igViewerParameters *)arg0->_parameters)->_showGui = frame->f214;
        if (frame->f214 == 0) {
            arg0->_guiVisibility = 2;
        }
    }
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
    FUN_00463c90(arg0->_viewManager, arg0->_parameters);
    {
        igObject *s2 = (igObject *)arg0->_parameters;
        RendererLink *s1 = (RendererLink *)arg0->_viewerRenderer;
        if (s2 != 0) {
            s2->_refCount = (int)s2->_refCount + 1;
        }
        igObject *a0 = s1->parameters;
        IG_OBJECT_RELEASE(a0);
        s1->parameters = s2;
    }
    {
        igObject *s2 = (igObject *)arg0->_parameters;
        RendererLink *s1 = (RendererLink *)arg0->_bboxRenderer;
        if (s2 != 0) {
            s2->_refCount = (int)s2->_refCount + 1;
        }
        igObject *a0 = s1->parameters;
        IG_OBJECT_RELEASE(a0);
        s1->parameters = s2;
    }
    {
        igObject *s2 = (igObject *)arg0->_parameters;
        RendererLink *s1 = (RendererLink *)arg0->_normalsRenderer;
        if (s2 != 0) {
            s2->_refCount = (int)s2->_refCount + 1;
        }
        igObject *a0 = s1->parameters;
        IG_OBJECT_RELEASE(a0);
        s1->parameters = s2;
    }
    *(int *)((char *)arg0->_applicationController + 16) = arg0->_viewerRenderer;
    *(igViewerSceneInfoManager **)((char *)arg0->_applicationController + 12) = arg0;
    FUN_00457e90(arg0->_applicationController, arg0->_parameters);
    FUN_001b1e50(((igViewerParameters *)arg0->_parameters)->_disables, 0xC);
    {
        int *list = (int *)((igViewerParameters *)arg0->_parameters)->_disables;
        memset((void *)list[4], 0, list[2] * 4);
    }
    BIND(FUN_004573c0, arg0->_hotKeyReceiver, DAT_004d1ac8, 0x46)
    BIND(FUN_004573c0, arg0->_hotKeyReceiver, DAT_004d1ad8, 0x44)
    BIND(FUN_004573f0, arg0->_hotKeyReceiver, DAT_004d1ae8, 0x43, 0xF)
    BIND(FUN_004573f0, arg0->_hotKeyReceiver, DAT_004d1af8, 0x48, 0xC)
    BIND(FUN_004573d0, arg0->_hotKeyReceiver, DAT_004d1b08, 3)
    BIND(FUN_004573d0, arg0->_hotKeyReceiver, DAT_004d1b18, 0)
    BIND(FUN_004573c0, arg0->_hotKeyReceiver, DAT_004d1b28, 0x4D)
    BIND(FUN_004573c0, arg0->_hotKeyReceiver, DAT_004d1b38, 0x57)
    BIND(FUN_004573f0, arg0->_hotKeyReceiver, DAT_004d1b48, 0x52, 0xA)
    BIND(FUN_004573f0, arg0->_hotKeyReceiver, DAT_004d1b58, 0x54, 0xB)
    BIND(FUN_004573c0, arg0->_hotKeyReceiver, DAT_004d1b68, 0x50)
    BIND(FUN_004573d0, arg0->_hotKeyReceiver, DAT_004d1b78, 1)
    BIND(FUN_004573d0, arg0->_hotKeyReceiver, DAT_004d1b88, 2)
}
