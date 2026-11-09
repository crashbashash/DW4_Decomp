extern "C" {
typedef struct NodeList { char p0[8]; unsigned count; char p1[4]; int *data; } NodeList;
typedef struct TraversedNode { char p0[28]; NodeList *children; } TraversedNode;
typedef struct PathEntry { int w0; int refs; } PathEntry;
PathEntry *FUN_0019f630(int);
int FUN_001c5740(PathEntry *, int);
int FUN_001c5870(int, unsigned);
int FUN_001c58c0(int);
int igObject_IsKindOf(TraversedNode *, int);
int ObjectList_AppendRetained(NodeList *, PathEntry *);
int igObject_Destroy(PathEntry *);
int igObject_GetAllocator(TraversedNode *);
extern int DAT_005619f8[16];
extern int DAT_00561ea0[16];
}
struct PathEntryRef {
    PathEntry *p;
    PathEntryRef(PathEntry *object) : p(object) {}
    ~PathEntryRef() {
        PathEntry *object = p;
        if (object != 0) {
            object->refs = object->refs - 1;
            if ((object->refs & 0x7FFFFF) == 0) igObject_Destroy(object);
        }
    }
};
extern "C" void FUN_001d6410(TraversedNode *collector, TraversedNode *node, int path) {
    unsigned count;
    unsigned i;
    int child;
    NodeList *children;
    if (node != 0) {
        if (igObject_IsKindOf(node, DAT_005619f8[0]) != 0) {
            children = node->children;
            count = 0;
            if (children != 0) {
                count = children->count;
            }
            for (i = 0; i < count; i++) {
                child = node->children->data[i];
                FUN_001c5870(path, i);
                FUN_001d6410(collector, (TraversedNode *)child, path);
                FUN_001c58c0(path);
            }
        }
        if (igObject_IsKindOf(node, DAT_00561ea0[0]) != 0) {
            PathEntryRef entry(FUN_0019f630(igObject_GetAllocator(collector)));
            FUN_001c5740(entry.p, path);
            ObjectList_AppendRetained(collector->children, entry.p);
        }
    }
}
