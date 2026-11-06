/* Counted do-while loops use `0 < n`, and the locals are declared in the order n, i, off. */
#include "dw4/reflected.h"
int igObject_IsKindOf();
int ObjectList_AppendUniqueRetained();
extern int DAT_005618e8[4];
extern int DAT_005619f8[4];
void FUN_00460790(igViewerRenderer *arg0, igGroup *arg1) {
    int n; int i; int off;
    if (arg1->_flags & 1) {
        if (igObject_IsKindOf(arg1, DAT_005619f8[0]) != 0) {
            n = 0;
            if (arg1->_childList != 0) n = ((igNodeList *)arg1->_childList)->_count;
            i = 0;
            if (0 < n) {
                off = 0;
                do {
                    FUN_00460790(arg0, *(igGroup **)((char *)((igNodeList *)arg1->_childList)->_data + off));
                    i += 1;
                    off += 4;
                } while (i < n);
            }
        } else if (igObject_IsKindOf(arg1, DAT_005618e8[0]) != 0) {
            n = ((igObjectList *)arg1->_childList)->_count;
            i = 0;
            if (0 < n) {
                off = 0;
                do {
                    ObjectList_AppendUniqueRetained(arg0->_lightList, *(int *)((char *)((igObjectList *)arg1->_childList)->_data + off));
                    i += 1;
                    off += 4;
                } while (i < n);
            }
        }
    }
}
