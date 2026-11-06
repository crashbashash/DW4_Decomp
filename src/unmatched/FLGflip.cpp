/* Bounds-checked byte set chosen by the current byte; the byte table is read through a local
 * pointer, the store index added first; alternate compiler -O3,p. */
#include "dw4/reflected.h"
extern "C" {
struct Rec { char pad[12]; igUnsignedCharList *f12; };
int beMessenger_GetObject(int, int);
int beMessenger_SendNamed(int, void *, int, int, void *);
struct Rec *igProperty_GetRecordArray(int, void *);
extern int DAT_0050d8f0[4];
extern int DAT_0050d940[4];
extern int DAT_0050d9f0[4];
extern int DAT_0058a1c0[4];
extern unsigned char GPR_005549c8;
extern unsigned char GPR_005549cc;
void FLGflip(int arg0);
}

void FLGflip(int arg0) {
    int obj;
    igUnsignedCharList *a;
    int cnt;
    unsigned char *p;
    beMessenger_SendNamed(DAT_0058a1c0[0], &DAT_0050d940[0], 0, 0, &DAT_0050d8f0[0]);
    obj = beMessenger_GetObject(DAT_0058a1c0[0], 0);
    p = (unsigned char *)igProperty_GetRecordArray(obj, &DAT_0050d9f0[0])->f12->_data;
    if (p[arg0] != 0) {
        a = igProperty_GetRecordArray(obj, &DAT_0050d9f0[0])->f12;
        cnt = a->_count;
        if (cnt != 0 && arg0 >= 0 && arg0 < cnt) {
            ((unsigned char *)a->_data)[arg0] = GPR_005549c8;
        }
    } else {
        a = igProperty_GetRecordArray(obj, &DAT_0050d9f0[0])->f12;
        cnt = a->_count;
        if (cnt != 0 && arg0 >= 0 && arg0 < cnt) {
            ((unsigned char *)a->_data)[arg0] = GPR_005549cc;
        }
    }
}
