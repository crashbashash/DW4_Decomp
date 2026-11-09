extern "C" {
struct Instance { int w0; unsigned rc; };
int igInsightPlugin_GetMetaObject();
int igMetaObject_CountTree(int);
int FUN_002fe300(int, int);
int igObject_GetAllocator(int);
int igObject_Destroy(Instance *);
int FUN_00236dd0(int, Instance *);
int FUN_002fd6e0(Instance **, int, int);
}
struct PluginRef {
    Instance *p;
    PluginRef(int type, int allocator) {
        Instance *created;
        FUN_002fd6e0(&created, type, allocator);
        p = created;
        if (p != 0) {
            p->rc = 1 + p->rc;
        }
        if (created != 0) {
            created->rc = created->rc - 1;
            if ((created->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(created);
            }
        }
    }
    ~PluginRef() {
        Instance *object = p;
        if (object != 0) {
            object->rc = object->rc - 1;
            if ((object->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    Instance *get() const { return p; }
};
extern "C" void FUN_00236ca0(int self) {
    int meta;
    int count;
    int i;
    count = igMetaObject_CountTree(meta = igInsightPlugin_GetMetaObject());
    for (i = 0; i < count; i++) {
        int type = FUN_002fe300(meta, i);
        PluginRef plugin(type, igObject_GetAllocator(self));
        if (plugin.get()) {
            FUN_00236dd0(self, plugin.get());
        }
    }
}
