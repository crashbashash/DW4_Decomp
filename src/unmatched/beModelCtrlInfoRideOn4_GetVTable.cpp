#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
void StringChunk_ReleaseHeader(int, int *);
extern int DAT_00537e80[4];                 /* beModelCtrlInfoRideOn vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
extern int DAT_0053ac90[4];                 /* beModelCtrlInfoRideOn4 vtable */
int beModelCtrlInfoRideOn4_GetVTable(void);
}

struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
struct igMatrix44fView { float m[16]; igMatrix44fView(); };

struct ModelNameField {
    const char *p;
    ModelNameField() { p = 0; }
    ~ModelNameField() {
        const char *s = p;
        if (s) {
            int *header = (int *)s - 2;
            int count = ((int *)s)[-1] - 1;
            ((int *)s)[-1] = count;
            if (count == 0) StringChunk_ReleaseHeader(*header, header);
        }
    }
};
struct ModelNodeField {
    igObject *p;
    ModelNodeField() { p = 0; }
    ~ModelNodeField() {
        igObject *o = p;
        if (o) {
            --o->_refCount;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
        }
    }
};
struct RideOnVtable { RideOnVtable(int **slot) { *slot = DAT_00537e80; } };

struct RideOnView : igObjectView, RideOnVtable {
    ModelNameField modelName;               /* +8 _modelName */
    int modelRamNo;                         /* +12 */
    ModelNodeField modelNode;               /* +16 _modelNode */
    igMatrix44fView oldMatrix;              /* +20 _oldMatrix */
    RideOnView() : RideOnVtable(&vtable) { }
    ~RideOnView() { vtable = DAT_00537e80; }
};

struct RideOn4Vtable { RideOn4Vtable(int **slot) { *slot = DAT_0053ac90; } };

struct RideOn4View : RideOnView, RideOn4Vtable {
    float oldPlayerPos[3];                  /* +84 */
    float vector[3];                        /* +96 */
    float scalar, limitter;                 /* +108 */
    int isFirst;                            /* +116 */
    RideOn4View() : RideOn4Vtable(&vtable) { }
    ~RideOn4View() { vtable = DAT_0053ac90; }
};

int beModelCtrlInfoRideOn4_GetVTable(void) {
    RideOn4View info;
    return *(int *)((char *)&info + *(int *)((char *)DAT_00586dc8[0] + 916));
}
