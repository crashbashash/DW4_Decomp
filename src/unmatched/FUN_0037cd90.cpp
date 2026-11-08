#include "dw4/reflected.h"
extern "C" {
int strlen(int *);
int FUN_003a7260(int, int);
int strcmp(int *, int);
extern int DAT_004e0858[4];
void FUN_0037cd90(beCri *arg0, int arg1);
}

void FUN_0037cd90(beCri *arg0, int arg1) {
    int i;
    int off;
    beCriHandle *it;
    int *p;

    p = (int *)((beCriHandle *)arg0->_hdBGM)->_name;
    p = p != 0 ? p : &DAT_004e0858[0];
    if (strcmp(p, arg1) == 0) {
        FUN_003a7260(((beCriHandle *)arg0->_hdBGM)->_audio, 0);
    } else {
        p = (int *)((beCriHandle *)arg0->_hdENV)->_name;
        p = p != 0 ? p : &DAT_004e0858[0];
        if (strcmp(p, arg1) == 0) {
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
                            if (strcmp(p, arg1) == 0) {
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
