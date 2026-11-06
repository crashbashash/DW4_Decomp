#include "dw4/reflected.h"
/* List-like object at +28 of the layer switch, with its count at +8. */
typedef struct UnidentifiedCountedList { char pad[8]; int cnt; } UnidentifiedCountedList;
typedef struct LayerSwtObject { int w0; int refs; char pad[20]; UnidentifiedCountedList *list; } LayerSwtObject;
extern "C" {
int FUN_001dc9a0(LayerSwtObject *, int);
int igObject_Destroy(LayerSwtObject *);
void Gap__Bec__beLayerCtl__vfunc_32(beLayerCtl *arg0);
}

void Gap__Bec__beLayerCtl__vfunc_32(beLayerCtl *arg0) {
    int n;
    LayerSwtObject *a0;
    UnidentifiedCountedList *l;
    arg0->_isOrdered = 0;
    if (arg0->_layerSwt != 0) {
        goto test; /* matching construct: goto/label layout reproduces the retail loop shape */
    body:
        FUN_001dc9a0(a0, 0);
    test:
        a0 = (LayerSwtObject *)arg0->_layerSwt;
        l = a0->list;
        if (l != 0) {
            n = l->cnt;
        } else {
            n = 0;
        }
        if (n > 0) goto body;
        if (a0 != 0) {
            a0->refs = a0->refs - 1;
            if (((unsigned long long)((long long)a0->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->_layerSwt = 0;
    }
}
