/* reference-counted engine object header: refcount word at +4 */
typedef struct RefCountedHeader { int pad; int f4; } RefCountedHeader;
/* Element-buffer list header: count at +8, buffer at +16. */
typedef struct ElementBufferList { char pad[8]; int f8; int pad2; RefCountedHeader **f16; } ElementBufferList;
#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(RefCountedHeader *);
void beMessenger_ClearObjects(beMessenger *arg0);
}

void beMessenger_ClearObjects(beMessenger *arg0) {
    beMessengerArgData *args;
    ElementBufferList *l;
    int n;
    int i;
    RefCountedHeader *o;
    int n2;
    int j;

    args = (beMessengerArgData *)arg0->_argData;
    l = (ElementBufferList *)args->_objectList;
    n = l->f8;
    for (i = 0; i < n; i++) {
        o = l->f16[i];
        if (o != 0) {
            o->f4 = o->f4 - 1;
            if (((unsigned long long) ((long long) o->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = l->f8;
    for (j = 0; j < n2; j++) {
        l->f16[j] = 0;
    }
    l->f8 = 0;
}
