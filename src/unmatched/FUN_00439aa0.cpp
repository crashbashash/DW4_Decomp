#include "dw4/reflected.h"
extern "C" {
extern unsigned char GPR_00554a68;
extern unsigned char GPR_00554a6c;
extern unsigned char GPR_00554a70;
int List_Resize(void *, int, int);

int FUN_00439aa0(beNDMWShopCtrlSales *self) {
    int cnt;
    int pg;
    int k;
    int n;
    igUnsignedCharList *q;
    int i;
    int off;
    igObjectList *l;
    int idx;
    int base;
    int s1;
    igObjectList *l2;
    int lim;
    int j;
    int N2;
    igUnsignedCharList *Q2;
    int N3;
    igUnsignedCharList *Q3;
    char *d;
    int *e;
    igObjectList *lx;
    lx = (igObjectList *)self->_salesItemList;
    cnt = lx->_count;
    i = 0;
    if (i < cnt) {
    off = 0;
    do {
        if (*(int *)(lx->_data + off) != 0) cnt = i + 1;
        i++;
        off += 4;
        lx = (igObjectList *)self->_salesItemList;
    } while (i < lx->_count);
    }
    if (cnt % 12 != 0) pg = cnt / 12 + 1;
    else pg = cnt / 12;
    self->_maxPage = pg;
    s1 = 12;
    base = self->_nowPage * 12;
    l2 = (igObjectList *)self->_salesItemList;
    for (k = 0; k < 12; k++) {
        idx = base + k;
        if (idx > l2->_count - 1 || ((int *)l2->_data)[idx] == 0) { s1 = k; break; }
        l2 = (igObjectList *)self->_salesItemList;
    }
    if (s1 <= 0) s1 = 1;
    else if (s1 > 12) s1 = 12;
    ((igUnsignedCharList *)self->_decideList)->_count = 0;
    for (j = 0; j < s1; j++) {
        e = (int *)((int *)((igObjectList *)self->_salesItemList)->_data)[base + j];
        if (e == 0) {
            q = (igUnsignedCharList *)self->_decideList;
            n = q->_count;
            if (n < q->_capacity) q->_count = n + 1; else List_Resize(q, n + 1, 1);
            ((unsigned char *)q->_data)[n] = GPR_00554a68;
        } else if (e[2] == 3 && e[3] == 0xb9) {
            Q2 = (igUnsignedCharList *)self->_decideList;
            N2 = Q2->_count;
            if (N2 < Q2->_capacity) Q2->_count = N2 + 1; else List_Resize(Q2, N2 + 1, 1);
            ((unsigned char *)Q2->_data)[N2] = GPR_00554a6c;
        } else {
            Q3 = (igUnsignedCharList *)self->_decideList;
            N3 = Q3->_count;
            if (N3 < Q3->_capacity) Q3->_count = N3 + 1; else List_Resize(Q3, N3 + 1, 1);
            ((unsigned char *)Q3->_data)[N3] = GPR_00554a70;
        }
    }
    return s1;
}
}
