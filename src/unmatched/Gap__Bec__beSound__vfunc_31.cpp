/* beSound::vfunc_31 (0x0039e870, 928 bytes) - per-frame state machine of the sound manager (arg1 is the beBaseInfoRam record;
 * its _st0 at +24 is the state).
 * State 0: asks the messenger (SendGroup with DAT_0050f9b0/DAT_0050f9c0); with at least one reply object, takes reply object 0 and walks its
 *   list, removing every element whose name (fallback DAT_004e0858) differs from DAT_0050f9d0 after clearing that element's own list
 *   (release, zero, count 0, reserve 4 if empty); the index advances only on kept elements.  Then FUN_0037dc60(cri, DAT_0050f9d8),
 *   _st0 += 1, _st1.._st3 = 0 and fall into state 1 (with no reply object it leaves at once).
 * State 1: drops the playing-SE entries whose _time is older than the insight world time (ObjectList_RemoveFirstRetained).
 * Matching notes: needs the pinned alternate compiler with -O3,p -Cpp_exceptions off (its unit profile). The address-taken scratch slot `sp`
 * (the out-parameter of ObjectList_RemoveFirstRetained, a plain struct: no destructor, so retail's exception table has no cleanup
 * actions) keeps arg1 spilled to the stack (reloaded at every use) and gives the case labels their 8-byte padding. Local declaration order fixes the s-register
 * colouring (found by a random walk over declaration orders). */
#include "dw4/reflected.h"
extern "C" {
int beMessenger_SendGroup(...);
int beMessenger_GetObjectCount(...);
igObjectList *beMessenger_GetObject(...);
int igStrCmp(...);
int List_Reserve(...);
int List_RemoveWordAt(...);
int igObject_Destroy(...);
int FUN_0037dc60(...);
int ObjectList_RemoveFirstRetained(...);
extern char DAT_004e0858[];
extern int DAT_0050f9b0[4];
extern int DAT_0050f9c0[4];
extern int DAT_0050f9d0[4];
extern int DAT_0050f9d8[4];
void Gap__Bec__beSound__vfunc_31(beSound *self, beBaseInfoRam *arg1);
}
struct RP { int *p; };
#define NM(e) ((e)->_name ? (char *)(e)->_name : DAT_004e0858)
#define REL(o) { igObject *rr = (igObject *)(o); if (rr != 0) { rr->_refCount = (int)rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
typedef struct SE { int p[2]; int _name; int p2[2]; igDataList *_list; } SE;
void Gap__Bec__beSound__vfunc_31(beSound *self, beBaseInfoRam *arg1) {
    igDataList *objs;
    long long now;
    SE *e;
    igDataList *l;
    int n;
    int i;
    int m;
    int j2;
    RP sp;
    int k;
    int j;
    switch (arg1->_st0) {
    case 0:
        beMessenger_SendGroup(self->_messenger, &DAT_0050f9b0[0], &DAT_0050f9c0[0]);
        if (beMessenger_GetObjectCount(self->_messenger) <= 0) break;
            objs = (igDataList *)beMessenger_GetObject(self->_messenger, 0);
            i = 0;
            if (0 < objs->_count) do {
                e = ((SE **)objs->_data)[i];
                if (NM(e) == 0) { i++; continue; }
                if (igStrCmp(NM(e), &DAT_0050f9d0[0]) == 0) { i++; continue; }
                l = e->_list;
                n = l->_count;
                for (j = 0; j < n; j++) {
                    REL(((igObject **)l->_data)[j]);
                }
                m = l->_count;
                for (j2 = 0; j2 < m; j2++) {
                    ((int *)l->_data)[j2] = 0;
                }
                l->_count = 0;
                if (0 < e->_list->_count) {
                } else {
                    List_Reserve(e->_list, 0, 4);
                }
                REL(((igObject **)objs->_data)[i]);
                List_RemoveWordAt(objs, i);
                ((int *)objs->_data)[objs->_count] = 0;
            } while (i < objs->_count);
        FUN_0037dc60(self->_cri, &DAT_0050f9d8[0]);
        arg1->_st0 = arg1->_st0 + 1;
        arg1->_st3 = 0;
        arg1->_st2 = 0;
        arg1->_st1 = 0;
    case 1:
        now = ((igInsightCore *)self->_insight)->_worldTime;
        l = (igDataList *)self->_playSEs;
        k = 0;
        if (0 < l->_count) do {
            bePlaySE *s = ((bePlaySE **)l->_data)[k];
            if (s->_time < now) {
                ObjectList_RemoveFirstRetained(&sp, l, s, k);
                k--;
            }
            l = (igDataList *)self->_playSEs;
            k++;
        } while (k < l->_count);
    }
}
