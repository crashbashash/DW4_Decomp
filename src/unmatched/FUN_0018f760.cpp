#include "dw4/igSmartPointer.h"

extern "C" {
struct InstanceNode : public igObject { };
unsigned FUN_002fe2c0(int);
int FUN_002fe2e0(int, unsigned);
InstanceNode *FUN_00186c00(int);
int FUN_00301ee0(InstanceNode *, unsigned);
extern int DAT_00560f08[4];
}
extern "C" igSmartPointer<InstanceNode> FUN_002fd6e0(int, int);
struct NodeList : InstanceNode { int count; int capacity; InstanceNode **data; };

struct InstanceListRef {
    NodeList *p;
    InstanceListRef(NodeList *list) : p(list) {}
    InstanceListRef(const InstanceListRef &other) : p(other.p) {
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
    }
    ~InstanceListRef() {
        InstanceNode *node = p;
        if (node != 0) {
            node->_refCount = node->_refCount - 1;
            if ((node->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(node);
            }
        }
    }
};
static inline void setElement(const InstanceListRef &list, int index, const igSmartPointer<InstanceNode> &element) {
    InstanceNode *value = element.p;
    NodeList *l = list.p;
    InstanceNode *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = l->data[index];
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    if (l->count != 0 && index >= 0 && index < l->count) {
        l->data[index] = value;
    }
}
extern "C" InstanceListRef FUN_0018f760(int allocator) {
    int meta = DAT_00560f08[0];
    unsigned count = FUN_002fe2c0(meta);
    unsigned i;
    InstanceListRef list((NodeList *)FUN_00186c00(allocator));
    FUN_00301ee0(list.p, count);
    for (i = 0; i < count; i++) {
        igSmartPointer<InstanceNode> element(FUN_002fd6e0(FUN_002fe2e0(meta, i), allocator).get(), kRetainReference);
        setElement(list, i, element);
    }
    return list;
}
