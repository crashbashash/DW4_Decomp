/* 0x0015ff10 - igVertexArray2Helper slot 23: build the stream objects of a new vertex array.
 * When the helper has no igVertexArray2 yet (+12 == 0) it creates one and, for every stream
 * kind requested in the layout word *arg1, creates a data list of `arg2` elements and wraps
 * it in a stream record (kind in +16) that is appended to the array's stream list (+16):
 *   bit 0 / bit 1 / bit 2     kinds 1 / 3 / 2   (12 / 12 / 4 byte elements)
 *   bits 16..19 (count)       kind 4, one record per index (8 byte elements, index in +20)
 *   bits 4..7   (count)       kind 5, arg2 * count 4-byte elements, count in +24
 *   bits 8..11  (count)       kind 6, arg2 * count 1-byte elements, count in +24
 *   bits 20..21 (mode)        kind 9, mode 1 = 4-byte list, mode 2 = 8-byte list
 *   bit 22 / bit 23           kinds 7 / 8       (12 byte elements)
 * Returns arg2, or 0 when the helper already has an array.  The reference-counted locals
 * (array, record, list) release themselves when their scope ends.
 * Evidence: findings #656-#658, docs/engine/igvertexarray2helper.md. */
#include "dw4/reflected.h"
extern "C" {
void *FUN_0014a780(...);
void *FUN_0014b390(...);
void *FUN_00189e40(...);
void *FUN_0018a060(...);
void *FUN_0018a2d0(...);
void *FUN_002c9740(...);
void *FUN_002c99b0(...);
int List_Resize(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
int Gap__Core__igVertexArray2Helper__vfunc_23(igVertexArray2Helper *arg0, unsigned int *arg1, int arg2);
}

/* reference-counted engine object header: refcount (low 23 bits) at +4 */
struct RC { int vt; int rc; };
/* data list header: element count at +8, capacity at +12 */
struct DataList { int vt; int rc; int count; int cap; };
/* stream record: list at +12, kind at +16, index/count at +20/+24 */
struct StreamRec { int vt; int rc; int pad8; DataList *list; int kind; int index; int count; };
/* matching construct: stack smart-pointer slot (empty destructor) */
struct RP { RC *p; ~RP() {} };

#define REL(x) { RC *q_ = (x); if (q_ != 0) { q_->rc = q_->rc - 1; if (((unsigned long long)((long long)q_->rc << 0x29) >> 0x29) == 0) igObject_Destroy(q_); } }
/* size a freshly created list to n elements (a negative count leaves it untouched) */
#define SIZE_LIST(lst, n, esz) { DataList *dl_ = (lst); if ((n) >= 0) { if ((n) <= dl_->cap) { dl_->count = (n); } else { List_Resize(dl_, (n), (esz)); } } }
/* replace the record slot with a new record created from the object's allocator, then attach `list` to it */
#define ATTACH(rec, lst) { RC *l_ = (RC *)(lst); StreamRec *r_ = (rec); if (l_ != 0) l_->rc = l_->rc + 1; REL((RC *)r_->list) r_->list = (DataList *)l_; }

int Gap__Core__igVertexArray2Helper__vfunc_23(igVertexArray2Helper *arg0, unsigned int *arg1, int arg2) {
    RP array;
    RP record;
    if (arg0->_vertexArray != 0) { return 0; }
    array.p = (RC *)FUN_0014a780(igObject_GetAllocator(arg0));
    {
        RC *a_ = array.p;
        if (a_ != 0) a_->rc = a_->rc + 1;
        REL((RC *)arg0->_vertexArray)
        arg0->_vertexArray = (int)a_;
    }
    record.p = 0;
    if (*arg1 & 1) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_0018a060(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 12)
        alloc = igObject_GetAllocator(arg0);
        REL(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 1;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL(list.p)
    }
    if (*arg1 & 2) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_0018a060(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 12)
        alloc = igObject_GetAllocator(arg0);
        REL(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 3;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL(list.p)
    }
    if (*arg1 & 4) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_00189e40(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 4)
        alloc = igObject_GetAllocator(arg0);
        REL(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 2;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL(list.p)
    }
    if ((*arg1 & 0xF0000) >> 16 & 0xFF) {
        unsigned int index;
        for (index = 0; index < ((*arg1 & 0xF0000) >> 16 & 0xFF); index++) {
            RP list;
            int alloc;
            list.p = (RC *)FUN_0018a2d0(igObject_GetAllocator(arg0));
            SIZE_LIST((DataList *)list.p, arg2, 8)
            alloc = igObject_GetAllocator(arg0);
            REL(record.p)
            record.p = (RC *)FUN_0014b390(alloc);
            ATTACH((StreamRec *)record.p, list.p)
            ((StreamRec *)record.p)->kind = 4;
            ((StreamRec *)record.p)->index = index;
            ObjectList_AppendRetained(((int *)array.p)[4], record.p);
            REL(list.p)
        }
    }
    if ((*arg1 & 0xF0) >> 4 & 0xFF) {
        RP list;
        int alloc;
        int total;
        list.p = (RC *)FUN_002c9740(igObject_GetAllocator(arg0));
        total = arg2 * ((*arg1 & 0xF0) >> 4 & 0xFF);
        SIZE_LIST((DataList *)list.p, total, 4)
        alloc = igObject_GetAllocator(arg0);
        REL(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 5;
        ((StreamRec *)record.p)->count = (*arg1 & 0xF0) >> 4 & 0xFF;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL(list.p)
    }
    if ((*arg1 & 0xF00) >> 8 & 0xFF) {
        RP list;
        int alloc;
        int total;
        list.p = (RC *)FUN_002c99b0(igObject_GetAllocator(arg0));
        total = arg2 * ((*arg1 & 0xF00) >> 8 & 0xFF);
        SIZE_LIST((DataList *)list.p, total, 1)
        alloc = igObject_GetAllocator(arg0);
        REL(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 6;
        ((StreamRec *)record.p)->count = (*arg1 & 0xF00) >> 8 & 0xFF;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL(list.p)
    }
    {
        unsigned int mode = (*arg1 & 0x300000) >> 0x14;
        unsigned char field = mode;
        if (field != 0) {
            int modeInt = field & 0xFF;
            int alloc = igObject_GetAllocator(arg0);
            REL(record.p)
            record.p = (RC *)FUN_0014b390(alloc);
            ((StreamRec *)record.p)->kind = 9;
            if (modeInt == 1) {
                RP list;
                list.p = (RC *)FUN_002c9740(igObject_GetAllocator(arg0));
                SIZE_LIST((DataList *)list.p, arg2, 4)
                ATTACH((StreamRec *)record.p, list.p)
                REL(list.p)
            } else if (modeInt == 2) {
                RP list;
                list.p = (RC *)FUN_0018a2d0(igObject_GetAllocator(arg0));
                SIZE_LIST((DataList *)list.p, arg2, 8)
                ATTACH((StreamRec *)record.p, list.p)
                REL(list.p)
            }
            ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        }
    }
    if (*arg1 & 0x400000) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_0018a060(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 12)
        alloc = igObject_GetAllocator(arg0);
        REL(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 7;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL(list.p)
    }
    if (*arg1 & 0x800000) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_0018a060(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 12)
        alloc = igObject_GetAllocator(arg0);
        REL(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 8;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL(list.p)
    }
    REL(record.p)
    REL(array.p)
    return arg2;
}
