typedef struct T { int word0; int references; } T;
typedef struct O { T *a; T *b; int *vt; } O;
void igObject_Destroy(T *);
void Memory_FreeBufferAlias_002ed5c0(void *);
extern int DAT_00530608[4];
O *FUN_002dc1e0(O *self, int delete_storage) {
    T *p;
    T *q;
    if (self) {
        self->vt = &DAT_00530608[0];
        p = self->a;
        --p->references;
        if (((unsigned long long)(long long)p->references & 0x7fffffULL) == 0)
            igObject_Destroy(p);
        self->a = 0;
        q = self->b;
        --q->references;
        if (((unsigned long long)(long long)q->references & 0x7fffffULL) == 0)
            igObject_Destroy(q);
        self->b = 0;
        if ((short)delete_storage > 0) Memory_FreeBufferAlias_002ed5c0(self);
    }
    return self;
}
