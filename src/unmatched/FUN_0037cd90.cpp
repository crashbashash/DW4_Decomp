#include "dw4/reflected.h"
extern "C" {
int strlen(int *);
int FUN_003a7260(int, int);
int igStrCmp(int *, int);
extern int DAT_004e0858[4];
void FUN_0037cd90(beCri *arg0, int arg1);
}

/* hypothesis: arg0 is the beCri (beSound::_cri): +32/+36/+40 = _hdBGM/_hdENV/_hdSEs; the hd refs are beCriHandle (+8 _name, +12 _audio), _hdSEs a beCriHandleList */
void FUN_0037cd90(beCri *arg0, int arg1) {
    int i;
    int off;
    beCriHandle *it;
    int *p;

    p = (int *)((beCriHandle *)arg0->_hdBGM)->_name;
    p = p != 0 ? p : &DAT_004e0858[0];
    if (igStrCmp(p, arg1) == 0) {
        FUN_003a7260(((beCriHandle *)arg0->_hdBGM)->_audio, 0);
    } else {
        p = (int *)((beCriHandle *)arg0->_hdENV)->_name;
        p = p != 0 ? p : &DAT_004e0858[0];
        if (igStrCmp(p, arg1) == 0) {
            FUN_003a7260(((beCriHandle *)arg0->_hdENV)->_audio, 0);
        } else {
            i = 0;
            if (0 < ((beCriHandleList *)arg0->_hdSEs)->_count) {
                off = 0;
                do {
                    it = (beCriHandle *)((int *)(((beCriHandleList *)arg0->_hdSEs)->_data + off))[0];
                    p = it->_name != 0 ? (int *)it->_name : &DAT_004e0858[0];
                    if (p != 0) {
                        p = it->_name != 0 ? (int *)it->_name : &DAT_004e0858[0];
                        if (strlen(p) != 0) {
                            p = it->_name != 0 ? (int *)it->_name : &DAT_004e0858[0];
                            if (igStrCmp(p, arg1) == 0) {
                                FUN_003a7260(it->_audio, 0);
                            }
                        }
                    }
                    i += 1;
                    off += 4;
                } while (i < ((beCriHandleList *)arg0->_hdSEs)->_count);
            }
        }
    }
}
