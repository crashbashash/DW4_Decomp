#include "dw4/reflected.h"
extern "C" {
int igStrCmp(const char *, const char *);
extern char DAT_004e0858[];   /* the empty string */
extern char DAT_0050e7b8[];
/* second argument: messenger node whose +12 holds the beFontInfo (class of the node itself not recovered) */
struct P { char p[12]; int f12; };
int FUN_003841d0(beFont *arg0, struct P *arg1);
}

int FUN_003841d0(beFont *arg0, struct P *arg1) {
    int j;
    const char *p;
    int res;
    int i;
    igAttrSet *y;
    const char *q;
    beFontInfoData *it;
    int off;
    beBaseInfoDataList *l;
    int off2;


    res = -1;
    l = (beBaseInfoDataList *)((beFontInfo *)arg1->f12)->_dataList;
    if (igStrCmp((const char *)arg0->_condition00, DAT_0050e7b8) == 0) {
        i = arg0->_history;
        off = i * 4;
        if (i < l->_count) {
            do {
                q = (const char *)arg0->_condition01;
                p = (const char *)((igAttrSet *)((beFontInfoData *)*(int *)(l->_data + off))->_attrSet)->_name;
                if (igStrCmp(p != 0 ? p : DAT_004e0858, q) == 0) {
                    res = i;
                    break;
                }
                i += 1;
                off += 4;
            } while (i < l->_count);
        }
    } else {
        j = arg0->_history;
        off2 = j * 4;
        if (j < l->_count) {
            do {
                it = (beFontInfoData *)*(int *)(l->_data + off2);
                p = (const char *)it->_name;
                y = (igAttrSet *)it->_attrSet;
                q = (const char *)arg0->_condition00;
                if (igStrCmp(p != 0 ? p : DAT_004e0858, q) == 0) {
                    p = (const char *)y->_name;
                    q = (const char *)arg0->_condition01;
                    if (igStrCmp(p != 0 ? p : DAT_004e0858, q) == 0) {
                        res = j;
                        break;
                    }
                }
                j += 1;
                off2 += 4;
            } while (j < l->_count);
        }
    }
    if (res != -1) {
        arg0->_history = res + 1;
    }
    return res;
}
