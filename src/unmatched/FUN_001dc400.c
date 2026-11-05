#include "dw4/reflected.h"
/* igSorter::_lightAttrs target and its list at +12: classes not recovered (the list has
   the 4-byte-element _count/_capacity/_data layout); the count is volatile for the retail reload. */
struct L { char p0[8]; volatile int cnt; int cap; int *data; };
struct LA { char p0[12]; struct L *l; };
extern igMetaObject *DAT_0055efe8[4];
int List_Resize();
int List_AppendWords();

void FUN_001dc400(igSorter *arg0, igGroup *arg1, igAttrStackManager *arg2) {
    igAttrStack *e;
    int v;
    int n;
    struct L *l;
    e = ((igAttrStack **)((igAttrStackList *)arg2->_attrStacks)->_data)[((int *)arg2->_attrStackIndexTable)[DAT_0055efe8[0]->_id]];
    if (e->_count == 0) {
        v = 0;
    } else {
        v = *(int *)((char *)e->_data + (e->_count - 1) * 4);
    }
    l = ((struct LA *)arg0->_lightAttrs)->l;
    n = l->cnt;
    if (n < l->cap) {
        l->cnt = l->cnt + 1;
    } else {
        List_Resize(l, n + 1, 4);
    }
    l->data[n] = v;
    List_AppendWords(((struct LA *)arg0->_lightAttrs)->l, ((igNodeList *)arg1->_childList)->_count, ((igNodeList *)arg1->_childList)->_data);
}
