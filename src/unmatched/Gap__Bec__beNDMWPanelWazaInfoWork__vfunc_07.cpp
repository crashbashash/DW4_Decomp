#include "dw4/reflected.h"
extern "C" {
int Gap__Core__igObject__vfunc_07();
int List_Reserve(igDataList *, int, int);
int List_Resize(igDataList *, int, int);
int StringChunk_ReleaseHeader(int, int *);
int StringList_Resize(igDataList *, int);
extern int DAT_004c9228[4];
void Gap__Bec__beNDMWPanelWazaInfoWork__vfunc_07(beNDMWPanelWazaInfoWork *arg0);
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};

void Gap__Bec__beNDMWPanelWazaInfoWork__vfunc_07(beNDMWPanelWazaInfoWork *arg0) {
    int n;
    char **p;
    igDataList *l;
    char *old;
    int n2;
    int *q;
    int i;
    int k;
    int *a1;
    int rc;
    char *t;

    Gap__Core__igObject__vfunc_07();
    l = (igDataList *)arg0->_textSetList;
    if (l->_count < 0x31) {
        List_Reserve(l, 0x30, 4);
    }
    StringList_Resize((igDataList *)arg0->_textSetList, 0x30);
    {
        /* every text slot takes a share of one empty token */
        StringRef empty(0);
        l = (igDataList *)arg0->_textSetList;
        n = l->_count;
        p = (char **)l->_data;
        for (i = 0; i < n; i++) {
            t = empty.p;
            if (t != 0) {
                ((int *)t)[-1] = ((int *)t)[-1] + 1;
            }
            old = *p;
            if (old != 0) {
                a1 = (int *)old - 2;
                rc = ((int *)old)[-1] - 1;
                ((int *)old)[-1] = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
            *p = empty.p;
            p++;
        }
    }
    l = (igDataList *)arg0->_textColorList;
    if (l->_count < 0x31) {
        List_Reserve(l, 0x30, 4);
    }
    l = (igDataList *)arg0->_textColorList;
    if (l->_capacity >= 0x30) {
        l->_count = 0x30;
    } else {
        List_Resize(l, 0x30, 4);
    }
    l = (igDataList *)arg0->_textColorList;
    n2 = l->_count;
    q = (int *)l->_data;
    for (k = 0; k < n2; k++) {
        q[k] = DAT_004c9228[0];
    }
}
