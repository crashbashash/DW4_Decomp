/* beNDMWWindow_PlayQueuedModelClose - 0x003f5f80.  Plays the queued model-close sequences: for each entry of the
 * model-close info-name list it fetches the info name and the sequence name (retained interned strings), looks up the
 * RAM number at the same index and sends the model sequence; each string is released before the send (the text itself
 * stays valid because the lists keep their own reference).  The strings are held in int locals: that is the form whose
 * virtual-register order reproduces retail's colouring (pointer-typed copies of the stack slots take later ids). */
#include "dw4/reflected.h"
extern "C" {
void StringList_CopyRetained(char **, int, int);
void StringChunk_ReleaseHeader(int, int *);
void beNDMWWindow_SendModelSequence(beNDMWWindow *, int, int, int);
}
/* Interned strings carry {owner, count} in the 8 bytes before the text. */
#define STR_RELEASE(s) if (s) { int *h_ = (int *)((s) - 8); if (--h_[1] == 0) StringChunk_ReleaseHeader(h_[0], h_); }

extern "C" void beNDMWWindow_PlayQueuedModelClose(beNDMWWindow *w) {
    int n = ((igDataList *)w->_modelCloseInfoNameList)->_count;
    int i = 0;
    int m;
    int s;
    int t;
    int off;
    if (0 < n) {
        off = 0;
        do {
            char *a;
            char *b;
            StringList_CopyRetained(&a, w->_modelCloseInfoNameList, i);
            s = (int)a;
            STR_RELEASE(s);
            m = *(int *)((char *)((igIntList *)w->_modelCloseRamNoList)->_data + off);
            StringList_CopyRetained(&b, w->_modelCloseSeqNameList, i);
            t = (int)b;
            STR_RELEASE(t);
            beNDMWWindow_SendModelSequence(w, s, m, t);
            i++;
            off += 4;
        } while (i < n);
    }
}
