#include "dw4/reflected.h"
extern "C" {
int List_RemoveWordAt(void *, int);
int igObject_Destroy(void *);
}
extern "C" void beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(beNDMWLoadCtrl2CommonIntf *w, int key) {
    bool found = false;
    beNDMWLoadSlotPlayerList *l = (beNDMWLoadSlotPlayerList *)w->_slotSaveData;
    for (int i = l->_count - 1; i >= 0; i--) {
        int off; igIntList *in; int j; int n; igIntList *in2;
        in = (igIntList *)((beNDMWLoadSlotPlayer **)l->_data)[i]->_accessPlList; n = in->_count; in2 = in; j = 0;
        if (j < n) { off = 0;
          do { if (key == *(int*)(in2->_data + off)) { List_RemoveWordAt(in, j); found = true; break; } j++; off += 4; in2 = in; } while (j < n); }
        if (found == true) break;
    }
    if (found == true) {
        for (int i = l->_count - 1; i >= 0; i--) {
            beNDMWLoadSlotPlayer *e = ((beNDMWLoadSlotPlayer **)l->_data)[i];
            if (((igIntList *)e->_accessPlList)->_count == 0) {
                if (e != 0) {
                    e->_refCount = e->_refCount - 1;
                    if ((e->_refCount & 0x7FFFFF) == 0) igObject_Destroy(e);
                }
                List_RemoveWordAt(l, i);
                ((beNDMWLoadSlotPlayer **)l->_data)[l->_count] = 0;
            }
        }
    }
}
