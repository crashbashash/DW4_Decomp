#include "dw4/reflected.h"
#define DEFN ((char *)DAT_004e0858)
extern "C" {
extern int DAT_004e0858[4];
int strlen(char *);
void FUN_003a7590(int, int, float, float, float);
int igStrCmp(char *, char *);
void FUN_0037cf30(beCri *arg0, char *arg1, float f0, float f1, float f2);
}

void FUN_0037cf30(beCri *arg0, char *arg1, float f0, float f1, float f2) {
    char *s;
    int i, off;
    beCriHandle *n;
    igObjectList *l;
    s = (char *)((beCriHandle *)arg0->_hdBGM)->_name;
    if ((s ? s : DEFN) && igStrCmp(s ? s : DEFN, arg1) == 0) {
        FUN_003a7590(((beCriHandle *)arg0->_hdBGM)->_volume, arg0->_baseVolume, f0, f1, f2);
    } else {
        s = (char *)((beCriHandle *)arg0->_hdENV)->_name;
        if ((s ? s : DEFN) && igStrCmp(s ? s : DEFN, arg1) == 0) {
            FUN_003a7590(((beCriHandle *)arg0->_hdENV)->_volume, arg0->_baseVolume, f0, f1, f2);
        } else {
            l = (igObjectList *)arg0->_hdSEs;
            for (i = 0; i < l->_count; i++) {
                n = ((beCriHandle **)l->_data)[i];
                s = (char *)n->_name;
                if (s ? s : DEFN) {
                    if (strlen(s ? s : DEFN)) {
                        if (igStrCmp(arg1, (char *)n->_name ? (char *)n->_name : DEFN) == 0)
                            FUN_003a7590(n->_volume, arg0->_baseVolume, f0, f1, f2);
                    }
                }
                l = (igObjectList *)arg0->_hdSEs;
            }
        }
    }
}
