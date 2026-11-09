extern "C" {
struct InstanceNode { int word0; int references; };
void igObject_Destroy(InstanceNode *);
unsigned FUN_002fe2c0(int);
int FUN_002fe2e0(int, unsigned);
InstanceNode *FUN_00186c00(int);
int FUN_00301ee0(InstanceNode *, unsigned);
int FUN_002fd6e0(InstanceNode **, int, int);
extern int DAT_00560f08[4];
}
struct NodeList : InstanceNode { int count; int capacity; InstanceNode **data; };
struct InstanceRef {
    InstanceNode *p;
    InstanceRef(int type, int allocator) {
        InstanceNode *created;
        FUN_002fd6e0(&created, type, allocator);
        p = created;
        if (p != 0) {
            p->references = p->references + 1;
        }
        if (created != 0) {
            created->references = created->references - 1;
            if ((created->references & 0x7FFFFF) == 0) {
                igObject_Destroy(created);
            }
        }
    }
    ~InstanceRef() {
        InstanceNode *node = p;
        if (node != 0) {
            node->references = node->references - 1;
            if ((node->references & 0x7FFFFF) == 0) {
                igObject_Destroy(node);
            }
        }
    }
};
struct InstanceListRef {
    NodeList *p;
    InstanceListRef(NodeList *list) : p(list) {}
    InstanceListRef(const InstanceListRef &other) : p(other.p) {
        if (p != 0) {
            p->references = p->references + 1;
        }
    }
    ~InstanceListRef() {
        InstanceNode *node = p;
        if (node != 0) {
            node->references = node->references - 1;
            if ((node->references & 0x7FFFFF) == 0) {
                igObject_Destroy(node);
            }
        }
    }
};
static inline void setElement(const InstanceListRef &list, int index, const InstanceRef &element) {
    InstanceNode *value = element.p;
    NodeList *l = list.p;
    InstanceNode *previous;
    if (value != 0) {
        value->references = value->references + 1;
    }
    previous = l->data[index];
    if (previous != 0) {
        previous->references = previous->references - 1;
        if ((previous->references & 0x7FFFFF) == 0) {
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
        InstanceRef element(FUN_002fe2e0(meta, i), allocator);
        setElement(list, i, element);
    }
    return list;
}
