#include "dw4/reflected.h"
#pragma opt_strength_reduction off
extern "C" {
int FUN_0037caf0(beCri *, int);
int FUN_0037c130(beCri *arg0, unsigned char arg1, long long arg2);
}

int FUN_0037c130(beCri *arg0, unsigned char arg1, long long arg2) {
    long long bestKey;
    beCriHandleList *list;
    int i;
    int best;
    long long bestRank;
    int off2;
    beCriHandle *e;
    beCriAudio *m;
    int off;
    beCriHandle *e2;
    beCriAudio *m2;
    int flag;
    int n;
    int flag2;
    long long rk;
    list = (beCriHandleList *)arg0->_hdSEs;
    n = *(int *)&list->_count;
    i = 0;
    if (0 < n) {
        off = 0;
        flag = arg1;
        while (1) {
            e = *(beCriHandle **)(list->_data + off);
            m = (beCriAudio *)e->_audio;
            if (!(flag == 1 && m->_adxt == 0) && !(flag == 0 && m->_sndf == 0)) {
                if (e->_playID == 0) return i;
            }
            i += 1; off += 4;
            if (!(i < list->_count)) break;
        }
    }
    bestKey = arg0->_request;
    bestRank = 0x7fff;
    i = 0;
    if (0 < n) {
        off2 = 0;
        flag2 = arg1;
        rk = (short)arg2;
        while (1) {
            e2 = *(beCriHandle **)(list->_data + off2);
            m2 = (beCriAudio *)e2->_audio;
            if (!(flag2 == 1 && m2->_adxt == 0) && !(flag2 == 0 && m2->_sndf == 0)) {
                if (e2->_priority <= rk && e2->_playID < bestKey && e2->_priority <= (short)bestRank) {
                    bestKey = e2->_playID;
                    bestRank = e2->_priority;
                    best = i;
                }
            }
            i += 1; off2 += 4;
            if (!(i < list->_count)) break;
        }
    }
    if (best != -1) FUN_0037caf0(arg0, ((int *)list->_data)[best]);
    return best;
}
