int Gap__igOptInterface__vfunc_29(void) {
    return 0;
}

void **FUN_00229460(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void Gap__igOptConfiguration__vfunc_23(void) {
    FUN_002f00c0();
}

int igDataList_GetCount(int *p)
{
    return *(int *)((char *)p + 8);
}

void FUN_00229500(void *arg0, int arg1, ...) {
    int n = __builtin_args_info(2);
    int off;
    DW4VC_108 *temp_a0;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    temp_a0 = (DW4VC_108 *)(*(int *)((char *)(arg0) + 28));
    temp_a0->vX(arg1, (char *)__builtin_next_arg(arg1) - off);
}

void FUN_00229570(void *arg0) {
    *(char *)((char *)(*(int *)((char *)(arg0) + 28)) + 32) = 1;
}

extern "C" void FUN_00229580(igInterfaceView *self)
{
    self->_logInterface->vfunc_22();
}

void FUN_002295a0(void *arg0) {
    *(char *)((char *)(*(int *)((char *)(arg0) + 28)) + 32) = 0;
}

static inline Iterator *createFieldIterator() {
    Tag tag = Tag();
    return (Iterator *)FUN_00227780(0);
}

class igMetaTyped {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual igMetaObject *getMetaObject();
};

/* Walk self's object-ref fields; each one typed as an igInterface that `other` can fill is bound via FUN_0022bc10. */
extern "C" void igInterface_BindInterfaceFields(igMetaTyped *self, igMetaTyped *other) {
    igSmartPointer<Iterator> it(createFieldIterator());
    FUN_0022a9e0((S0 *)it.get(), (S1 *)self->getMetaObject());
    for (;;) {
        void *field = (void *)FUN_0022aa60((B *)it.p);
        if (((field != 0) ^ 1) != 0) break;
        FUN_0022aab0((S_4 *)it.p);
        field = cast0_6(field);
        if (field == 0) continue;
        void *type = *(void **)((char *)field + 56);
        if (type != 0 && FUN_002fe290(type, g_igInterface_metaObject[0]) != 0
            && FUN_002fdef0(other->getMetaObject(), field) != 0) {
            int result;
            FUN_0022bc10(&result, (int)field, (int)self, (int)field, (int)other);
        }
    }
}

int FUN_00229700(int a0, int a1)
{
    return a1;
}

S_2 *FUN_00229710(S_2 *arg0) {
    R_2 *p;

    arg0->a = 0;
    arg0->b = 0;
    arg0->c = 0;
    p = arg0->a;
    if (p != 0) {
        p->refs = p->refs - 1;
        if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
    arg0->a = 0;
    p = arg0->b;
    if (p != 0) {
        p->refs = p->refs - 1;
        if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
    arg0->b = 0;
    p = arg0->c;
    if (p != 0) {
        p->refs = p->refs - 1;
        if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
    arg0->c = 0;
    return arg0;
}

S_3 *FUN_002297f0(S_3 *s, short flag) {
    if (s != 0) {
        s->a = 0; s->b = 0; s->c = 0;
        s->c.~igSmartPointer_2();
        s->b.~igSmartPointer_2();
        s->a.~igSmartPointer_2();
    }
    return s;
}

void FUN_00229980(void) {

}

void Gap__igItemInterface__vfunc_13(igInterface *arg0) {
    Gap__Core__igObject__vfunc_11();
    arg0->_itemInterface = (int)(arg0);
}

extern "C" R_3 Gap__igItemInterface__vfunc_28(Obj_10 *arg1, void *arg2, int arg3) {
    RecoveryString h;
    void *var_v0;
    int s = *(int *)((char *)(arg2) + 28);
    if (s == 0) { var_v0 = 0; } else {
        if (g_stringPool[0] == 0) {
            int v = StringPool_Allocate(0x10);
            if (v != 0) { v = StringPool_Construct(v); }
            g_stringPool[0] = v;
        }
        var_v0 = StringPool_Intern(g_stringPool[0], s);
    }
    h.p = var_v0;
    return arg1->vf(&h, arg3);
}

int FUN_00229e20(struct L *arg0, int *arg1) {
    int h;
    int lo, hi, mid, base, res;
    FUN_00229270(&h);
    lo = 0;
    hi = arg0->n - 1;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        base = FUN_0022a030((int *)arg0);
        FUN_00229fb0((void **)&h, (void **)(base + mid * 4));
        if (FUN_00229f90(&h, arg1) != 0) { lo = mid + 1; continue; }
        if (FUN_00229f70(&h, arg1) != 0) { hi = mid - 1; continue; }
        StringRef_Destruct_00130720(&h, -1);
        res = mid;
        goto done;
    }
    if (arg0->n == 0) {
        StringRef_Destruct_00130720(&h, -1);
        res = -1;
    } else {
        base = FUN_0022a030((int *)arg0);
        FUN_00229fb0((void **)&h, (void **)(base + lo * 4));
        if (FUN_00229f90(arg1, &h) != 0 || FUN_00229f70(arg1, &h) != 0) {
            StringRef_Destruct_00130720(&h, -1);
            res = -1;
        } else {
            StringRef_Destruct_00130720(&h, -1);
            res = lo;
        }
    }
done:
    return res;
}

/* The comparison is written `(*arg0 - 8) > (*arg1 - 8)` so *arg0 is loaded before *arg1. */
int FUN_00229f70(int *arg0, int *arg1) {
    return (unsigned int) (*arg0 - 8) > (unsigned int) (*arg1 - 8);
}

int FUN_00229f90(int *arg0, int *arg1) {
    return (unsigned int) (*arg0 - 8) < (unsigned int) (*arg1 - 8);
}

void **FUN_00229fb0(void **arg0, void **arg1) {
    int *temp_a1;
    int temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v1 = (void *)(*arg1);
    if (temp_v1 != 0) {
        *(int *)((char *)(temp_v1) - 4) = (int)((int) (*(int *)((char *)(temp_v1) - 4) + 1));
    }
    temp_v1_2 = (void *)(*arg0);
    if (temp_v1_2 != 0) {
        temp_a1 = (int *)((char *)temp_v1_2 - 8);
        temp_v0 = *(int *)((char *)(temp_v1_2) - 4) - 1;
        *(int *)((char *)(temp_v1_2) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    *arg0 = *arg1;
    return arg0;
}

int FUN_0022a030(int *p)
{
    return *(int *)((char *)p + 16);
}

extern "C" int FUN_0022a040(ItemRegistry *self, StringRef name, int kind);


extern "C" igSmartPointer<InterfaceItem> Gap__igItemInterface__vfunc_27(int self, const StringRef &name, int kind) {
    int key = FUN_0022a040((ItemRegistry *)self, name, kind);
    if (key == 0) {
        return igSmartPointer<InterfaceItem>((InterfaceItem *)0, kRetainReference);
    }
    igSmartPointer<InterfaceItem> item(FUN_002fd610(key));
    if (item.get() != 0) {
        igInterface_BindInterfaceFields((igMetaTyped *)self, (igMetaTyped *)item.get());
    }
    return item;
}

int FUN_0022a740(int arg0, void **arg1) {
    int temp_v0;
    void *temp_v1;

    temp_v1 = *arg1;
    if (temp_v1 != 0) {
        *(int *)((char *)(temp_v1) - 4) = (int) (*(int *)((char *)(temp_v1) - 4) + 1);
    }
    temp_v0 = FUN_0022cb80((List *)arg0, (int **)arg1);
    List_InsertWords(arg0, temp_v0, 1, arg1);
    return temp_v0;
}

extern "C" void Gap__igItemInterface__vfunc_30(ItemInterface *self, const StringRef_2 &name, int a2, int a3) {
    igSmartPointer<Iterator> it(makeIterator(IteratorType()));
    FUN_0022a8d0((S0 *)it.p, (S1 *)a2);
    for (;;) {
        int v = FUN_0022a950((S22 *)it.p);
        if (((v != 0) ^ 1) != 0) break;
        { StringRef_2 copy(name); self->vX(copy, v, a3); }
        FUN_0022a9b0((S22a9d0 *)it.p);
    }
}

void FUN_0022a8d0(S0 *arg0, S1 *arg1) {
    S_temp_a0 *temp_a0;
    if (arg1 != 0) {
        arg1->f4 = (int)((int) (arg1->f4 + 1));
    }
    temp_a0 = (S_temp_a0 *)(arg0->f8);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f8 = (int)(arg1);
    arg0->fC = 0;
    FUN_0022a950((S22 *)arg0);
}

int FUN_0022a950(struct S22 *arg0) {
    int temp_s0;
    temp_s0 = arg0->c;
    if ((temp_s0 >= igMetaObject_CountTree(arg0->b)) || (temp_s0 < 0)) {
        return 0;
    }
    return FUN_002fe300(arg0->b, temp_s0);
}

int FUN_0022a9b0(struct S22a9d0 *arg0) {
    return FUN_0022a9d0(arg0) != 0;
}

int FUN_0022a9d0(struct S22a9d0 *arg0) {
    arg0->f += 1;
    return FUN_0022a950((S22 *)arg0);
}

void FUN_0022a9e0(S0 *arg0, S1 *arg1) {
    S_temp_a0 *temp_a0;
    if (arg1 != 0) {
        arg1->f4 = (int)((int) (arg1->f4 + 1));
    }
    temp_a0 = (S_temp_a0 *)(arg0->f8);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f8 = (int)(arg1);
    arg0->fC = 0;
    FUN_0022aa60((B *)arg0);
}

int FUN_0022aa60(struct B *arg0) {
    struct A *a;
    int i;
    a = *(struct A **)((char *)arg0->p + 40);
    i = arg0->idx;
    if ((i >= a->cnt) || (i < 0)) {
        return 0;
    }
    return a->arr[i];
}

void FUN_0022aab0(struct S_4 *arg0) {
    arg0->x++;
    FUN_0022aa60((B *)arg0);
}

int FUN_0022aac0(T_4 *arg0, int arg1) {
    L_2 *a;
    int n;
    L_2 *b;
    a = arg0->l12;
    if (0 <= a->cap) {
        a->cnt = 0;
    } else {
        List_Resize(a, 0, 4);
    }
    b = arg0->l12;
    n = b->cnt;
    if (n < b->cap) {
        b->cnt = cnt_of(b) + 1;
    } else {
        List_Resize(b, n + 1, 4);
    }
    b->data[n] = arg1;
    a = arg0->l16;
    if (0 <= a->cap) {
        a->cnt = 0;
    } else {
        List_Resize(a, 0, 4);
    }
    return arg1;
}

int FUN_0022ab90(int arg0, int arg1, int arg2) {
    int var_s0;
    int r;
    var_s0 = FUN_0022aac0((T_4 *)arg0, arg1);
    if (igObject_IsKindOf(var_s0, arg2) != 0) { r = var_s0; } else { var_s0 = FUN_0022ac70(arg0, arg2); r = var_s0; } return r;
}

int FUN_0022ac00(void *arg0) {
    int temp_v1;
    void *temp_v0;

    temp_v0 = (void *)(*(int *)((char *)(arg0) + 12));
    temp_v1 = *(int *)((char *)(temp_v0) + 8);
    if (temp_v1 == 0) {
        return 0;
    }
    return *(int *)(*(int *)((char *)(temp_v0) + 16) + ((temp_v1 - 1) * 4));
}

int FUN_0022ac40(void *it) {
    return FUN_0022ad00((GraphIterator *)it) != 0;
}

int FUN_0022ac60(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 8) > 0;
}

int FUN_0022ac70(int arg0, int arg1) {
    int v;

    v = FUN_0022ad00((GraphIterator *)arg0);
    while (FUN_0022ac60((void *)arg0) != 0) {
        if (v != 0 && igObject_IsKindOf(v, arg1) != 0) {
            return v;
        }
        v = FUN_0022ad00((GraphIterator *)arg0);
    }
    return 0;
}


void FUN_0022b0a0(int arg0, int *arg1) {
    int sp60[16];
    unsigned int n, i;
    int *o;
    struct TransformObjectList *l;
    igMatrix44f_SetIdentity(sp60);
    n = *(int *)(arg1[3] + 8);
    for (i = 0; i < n; i++) {
        o = ((struct TransformObjectList *)arg1[3])->data[i];
        if (igObject_IsKindOf(o, g_igTransform_metaObject[0]) != 0) {
            FUN_001904f0(sp60, (int)o + 0x20, sp60);
        }
    }
    Matrix44_Copy(arg0, sp60);
}

void Gap__igListenerInterface__vfunc_13(igInterface *arg0) {
    Gap__Core__igObject__vfunc_11();
    arg0->_listenerInterface = (int)(arg0);
}

int Gap__igListenerBase__vfunc_28(void) {
    return 0;
}

int Gap__igListenerBase__vfunc_27(void) {
    return 0;
}

int Gap__igLockInterface__vfunc_27(int self, int mode) {
    Lock *found;
    igSmartPointer<Rc> iterator(createIterator());
    FUN_0022a8d0((S0 *)iterator.p, (S1 *)igLockBase_GetMetaObject());
    for (;;) {
        found = (Lock *)FUN_0022a950((S22 *)iterator.p);
        if (((found != 0) ^ 1) != 0) {
            break;
        }
        FUN_0022a9d0((S22a9d0 *)iterator.p);
        LockRef lock;
        lock.attach((Lock *)FUN_002fd610((int)found).get());
        if (lock.get() == 0) {
            continue;
        }
        igInterface_BindInterfaceFields((igMetaTyped *)self, (igMetaTyped *)lock.get());
        if (lock.get()->tryLock(mode) != 0) {
            return 1;
        }
    }
    return 0;
}

int Gap__igLogInterface__vfunc_24(void *d0, int arg1) {
    return fflush(arg1) == 0;
}

int Gap__igLogInterface__vfunc_27(void *arg0, int arg1, int arg2) {
    int var_v0;

    var_v0 = -1;
    if (*(unsigned char *)((char *)(arg0) + 32) != 0) {
        var_v0 = vprintf(arg1, arg2);
    }
    return var_v0;
}

igMetaObject *Gap__Core__igInfo__vfunc_22(void) {
    return g_igInfo_metaObject[0];
}

/* IgMessageInterface slot 13: run the base-class hook (Gap::Core::igObject::vfunc_11, a bare
 * return), then point _messageInterface at the object itself: the message interface is its own
 * message-interface member. */

void Gap__igMessageInterface__vfunc_13(igMessageInterface *self) {
    Gap__Core__igObject__vfunc_11();
    self->_messageInterface = (int)(self);
}

void FUN_0022b470(int arg0, int arg1) {
    FUN_0022c7f0((A_2 *)arg0, *(int *)((char *)(arg0) + 32), (B_2 *)*(int *)((char *)(arg0) + 8), arg1);
}

static inline Iterator *createGraphIterator() {
    Tag tag = Tag();
    return (Iterator *)FUN_00227460(0);
}

/* Reject a graph the optimizer cannot handle: an igSegment or an IS_DYNAMIC (flag 0x40) object.
 * The walk never re-reads the current node after advancing, so only the root is tested. */
extern "C" int igOptimizer_CheckGraph(B_2 *log, int root) {
    igSmartPointer<Iterator> it(createGraphIterator());
    FUN_0022aac0((T_4 *)it.get(), root);
    int node = FUN_0022ac00(it.get());
    for (; FUN_0022ac60(it.get()) != 0; FUN_0022ac40(it.get())) {
        if (igObject_IsKindOf(node, igSegment_GetMetaObject()) != 0) {
            log->put(DAT_004e7ec0);
            return 0;
        }
        if (*(int *)((char *)node + 20) & 0x40) {
            log->put(DAT_004e7ef0);
            return 0;
        }
    }
    return 1;
}

void FUN_0022b610(B_2 *log, int root) {
    igOptimizer_CheckGraph(log, root);
}

class NamedObject : public igMetaTyped {
public:
    unsigned int _refCount;
    char *_name;
};
typedef igTDataList<NamedObject *> NamedObjectList;
struct OptObjectSource { char pad[16]; NamedObjectList *objects; };
struct OptContext { char pad[40]; OptObjectSource *source; NamedObjectList *skipped; };
class OptPass {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void log(const char *format, ...);
    virtual void d22(); virtual void d23(); virtual void d24();
    virtual bool applyTo(NamedObject *object);
    virtual void d26();
    virtual bool accepts(NamedObject *object);
    unsigned int _refCount;
    OptContext *_context;
};

static inline Rc *createObjectList(Tag) {
    return (Rc *)FUN_002c3400(0);
}

/* Run the pass over a snapshot of the context's objects, skipping the excluded ones;
 * logs `<type> named "<name>":` before each and returns whether every application succeeded. */
extern "C" bool igOptPass_ApplyToObjects(OptPass *self) {
    OptContext *context = self->_context;
    OptObjectSource *source = context->source;
    igSmartPointer<Rc> objects(createObjectList(Tag()));
    for (int i = 0, n = source->objects->count(); i < n; i++) {
        ObjectList_AppendRetained(objects.p, source->objects->_data[i]);
    }
    bool ok = true;
    int count = ((NamedObjectList *)objects.p)->count();
    for (int j = 0; j < count; j++) {
        NamedObjectList *skipped = context->skipped;
        NamedObject *object = ((NamedObjectList *)objects.p)->_data[j];
        if (skipped->find(object) < 0 && self->accepts(object)) {
            char *name = object->_name ? object->_name : emptyString;
            self->log(DAT_004e7f30, ((igMetaObject *)object->getMetaObject())->_name, name);
            bool applied = self->applyTo(object);
            ok = ok && applied;
        }
    }
    return ok;
}

bool FUN_0022b820(int arg0, int arg1) {
    if (igObject_IsKindOf(arg1, g_igSceneInfo_metaObject[0]) != 0) {
        return FUN_0022bac0((void *)arg1, (void *)arg0);
    }
    if (igObject_IsKindOf(arg1, g_igAnimationDatabase_metaObject[0]) != 0) {
        return FUN_0022b910((Own *)arg1, (V *)arg0);
    }
    return 0;
}

void FUN_0022b8a0(void **arg0, void *arg1) {
    if (igObject_IsKindOf(arg1, g_igSceneInfo_metaObject[0]) != 0) {
        ((DW4VC_132_1 *)(arg0))->vX((int)(*(int *)((char *)(arg1) + 20)));
        return;
    }
    igObject_IsKindOf(arg1, g_igAnimationDatabase_metaObject[0]);
}

extern "C" bool FUN_0022b910(Own *arg0, V *arg1) {
    bool r;
    bool ok;
    Lst *l;
    int n;
    int i;
    T_5 *t;
    ok = true;
    l = arg0->f28;
    n = l->count;
    for (i = 0; i < n; i++) {
        igSmartPointer<T_5> held;
        t = l->data[i]->held;
        held = t;
        if (arg1->v31(held.p)) {
            r = arg1->v26(held);
            storeHeld(l, i, held);
            ok = ok || r;
        }
    }
    return ok;
}

bool FUN_0022bac0(void *arg0, void *arg1) {
    RT *r = ((Arg0 *)arg0)->ref;
    bool res;
    if (r) ++r->references;
    if (((C132 *)arg1)->vX(r) != 0) {
        res = ((C112 *)arg1)->vX(&r);
        FUN_001d6340(arg0, r);
        RT::rel(r);
        return res;
    }
    RT::rel(r);
    return 0;
}

void thunk_Gap__Core__igObject__vfunc_09__0022bbc0(void) {
    Gap__Core__igObject__vfunc_09();
}

void Gap__igOptInterface__vfunc_13(void *arg0) {
    Gap__Core__igObject__vfunc_11();
    *(int *)((char *)(arg0) + 8) = (int)(arg0);
}

int Gap__Core__igMetaObject__vfunc_22(void) {
    return g_igMetaObject_metaObject[0];
}

void FUN_0022bc10(int *arg0, int arg1, int arg2, int arg3, int arg4) {

    if (FUN_0022e160((M *)arg1, arg2, (M *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022e0a0((void *)arg1, arg2, (void *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022dfe0((void *)arg1, arg2, (void *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022df20((void *)arg1, arg2, (void *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022de60((void *)arg1, (char *)arg2, (void *)arg3, (char *)arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022dda0((Q *)arg1, arg2, (Q *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022dce0((char *)arg1, arg2, (char *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022dc20((void *)arg1, arg2, (void *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022db60((M *)arg1, arg2, arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022daa0((void *)arg1, arg2, (void *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022d9e0((int *)arg1, arg2, (int *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022d8e0((M *)arg1, arg2, arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022d820((void *)arg1, arg2, (void *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022d760((void *)arg1, arg2, (void *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022d6a0((Q *)arg1, arg2, (Q *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022d5e0((void *)arg1, arg2, (void *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022d520((void *)arg1, arg2, (void *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022d460((O_2 *)arg1, arg2, (O_2 *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022d390((Q *)arg1, arg2, (Q *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022d2c0((char *)arg1, arg2, (char *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022d1f0((igMetaField *)arg1, arg2, (igMetaField *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022d120((Q *)arg1, arg2, (Q *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022d050((Q *)arg1, arg2, (Q *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022cf70((Q *)arg1, arg2, (Q *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022ce90((char *)arg1, arg2, (char *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else if (FUN_0022cdb0((void *)arg1, arg2, (void *)arg3, arg4, 0) & 0xFF) {
        *arg0 = g_statusSucceeded[0];
    } else {
        *arg0 = g_statusSucceeded[2];
    }
}

extern "C" int FUN_0022c7f0(A_2 *arg0, int arg1, B_2 *arg2, int arg3) {
    bool found;
    Lst_2 *l;
    unsigned int n;
    unsigned int i;
    char *nm;
    Ent *e;
    igSmartPointer<Rc_2> buffer(FUN_002b9500(0), AdoptReference());
    l = arg0->getObj()->lst;
    found = 0;
    i = 0;
    n = l->count;
    for (; i < n; i++) {
        e = l->arr[i];
        nm = e->name;
        igStringObj_Set(buffer.p, nm);
        if (FUN_0022c150(arg1, arg2, buffer.p, arg3, e, arg0) != 0) {
            found = 1;
        } else if (*nm == 0x5f) {
            igStringObj_Set(buffer.p, e->name + 1);
            if (0 != FUN_0022c150(arg1, arg2, buffer.p, arg3, e, arg0)) found = 1;
        }
    }
    if (found) arg2->put(DAT_004e7ea8);
    return 1;
}

igMetaObject *Gap__igOptInterface__vfunc_22(void) {
    return g_igOptInterface_metaObject[0];
}

void Gap__igOptInterface__vfunc_27(void) {

}

void Gap__igOptInterface__vfunc_28(void) {

}

void Gap__igOptInterface__vfunc_30(void) {

}

void Gap__igOptInterface__vfunc_31(void) {

}

void Gap__igOptInterface__vfunc_32(int *arg0) {
    *arg0 = 0;
}

void Gap__igOptInterface__vfunc_12(void) {
    Gap__Core__igObject__vfunc_10();
}

igMetaObject *FUN_0022ca10(void) {
    return g_igOptBase_metaObject[0];
}

igMetaObject *Gap__igMessageInterface__vfunc_22(void) {
    return g_igMessageInterface_metaObject[0];
}

igMetaObject *Gap__igLogInterface__vfunc_22(void) {
    return g_igLogInterface_metaObject[0];
}

igMetaObject *Gap__igLockInterface__vfunc_22(void) {
    return g_igLockInterface_metaObject[0];
}

igMetaObject *Gap__igListenerInterface__vfunc_22(void) {
    return g_igListenerInterface_metaObject[0];
}

igMetaObject *Gap__igItemInterface__vfunc_22(void) {
    return g_igItemInterface_metaObject[0];
}

igMetaObject *Gap__igFileInfo__vfunc_22(void) {
    return g_igFileInfo_metaObject[0];
}

igMetaObject *Gap__igFileInfoList__vfunc_22(void) {
    return g_igFileInfoList_metaObject[0];
}

void Gap__igListenerBase__vfunc_29(void) {

}

igMetaObject *Gap__igCompoundList__vfunc_22(void) {
    return g_igCompoundList_metaObject[0];
}

igMetaObject *Gap__igItemDataBaseField__vfunc_22(void) {
    return g_igItemDataBaseField_metaObject[0];
}

int Gap__igItemDataBaseField__vfunc_23(void) {
    return DAT_0056d9e0[0];
}

igMetaObject *Gap__igItemDataBaseList__vfunc_22(void) {
    return g_igItemDataBaseList_metaObject[0];
}

igMetaObject *Gap__igIterateDerived__vfunc_22(void) {
    return g_igIterateDerived_metaObject[0];
}

igMetaObject *Gap__igIterateField__vfunc_22(void) {
    return g_igIterateField_metaObject[0];
}

igMetaObject *Gap__igIterateGraph__vfunc_22(void) {
    return g_igIterateGraph_metaObject[0];
}

igMetaObject *Gap__igListenerList__vfunc_22(void) {
    return g_igListenerList_metaObject[0];
}

igMetaObject *Gap__igListenerListList__vfunc_22(void) {
    return g_igListenerListList_metaObject[0];
}

igMetaObject *Gap__igMessageList__vfunc_22(void) {
    return g_igMessageList_metaObject[0];
}

igMetaObject *Gap__igOptConfiguration__vfunc_22(void) {
    return g_igOptConfiguration_metaObject[0];
}

igMetaObject *Gap__igInterface__vfunc_22(void) {
    return g_igInterface_metaObject[0];
}

igMetaObject *Gap__igMessageBase__vfunc_22(void) {
    return g_igMessageBase_metaObject[0];
}

igMetaObject *Gap__igListenerBase__vfunc_22(void) {
    return g_igListenerBase_metaObject[0];
}

extern "C" int FUN_0022cb80(List *arg0, int **arg1) {
    int *x;
    RecoveryString_2 h;
    int lo = 0;
    int hi = arg0->count - 1;
    int mid;
    int **s0;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        s0 = &arg0->data[mid];
        x = *s0;
        if (x) *(int *)((char *)x - 4) = *(int *)((char *)x - 4) + 1;
        {
            int *q = h.p;
            if (q) {
                int *t = (int *)((char *)q - 8);
                int v = t[1] - 1;
                t[1] = v;
                if (0 == v) StringChunk_ReleaseHeader(*t, t);
            }
        }
        h.p = *s0;
        unsigned a = (unsigned)((char *)*arg1 - (char *)8);
        unsigned b = (unsigned)((char *)h.p - (char *)8);
        if (b < a) {
            lo = mid + 1;
        } else if (a < b) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (arg0->count == 0) return 0;
    if ((unsigned)((char *)arg0->data[lo] - (char *)8) < (unsigned)((char *)*arg1 - (char *)8)) return 1 + lo;
    return lo;
}

igMetaObject *Gap__igMessageList__vfunc_24(void) {
    return g_igMessageBase_metaObject[0];
}

igMetaObject *Gap__igListenerListList__vfunc_24(void) {
    return g_igListenerList_metaObject[0];
}

igMetaObject *Gap__igListenerList__vfunc_24(void) {
    return g_igListenerBase_metaObject[0];
}

igMetaObject *Gap__igFileInfoList__vfunc_24(void) {
    return g_igFileInfo_metaObject[0];
}

int FUN_0022cdb0(void *arg0, int arg1, void *arg2, int arg3, int arg4) {
    /* matching construct: variant search — decl order [2, 1, 0]; the unit compiler assigns stack slots and registers in declaration order */
    void *temp_a1;
    void *temp_a0;
    int var_v0;
    arg0 = cast0(arg0);
    arg2 = cast0(arg2);
    if ((arg0 != 0) && (arg2 != 0)) {
        var_v0 = 1;
        temp_a0 = (void *)(arg1 + *(int *)((char *)(arg0) + 8));
        temp_a1 = (void *)(arg3 + *(int *)((char *)(arg2) + 8));
        *(unsigned char *)((char *)(temp_a1) + 0) = (unsigned char) *(unsigned char *)((char *)(temp_a0) + 0);
        *(unsigned char *)((char *)(temp_a1) + 1) = (unsigned char) *(unsigned char *)((char *)(temp_a0) + 1);
        *(unsigned char *)((char *)(temp_a1) + 2) = (unsigned char) *(unsigned char *)((char *)(temp_a0) + 2);
        *(unsigned char *)((char *)(temp_a1) + 3) = (unsigned char) *(unsigned char *)((char *)(temp_a0) + 3);
    }
    else { var_v0 = 0; }
    return var_v0;
}

int FUN_0022ce90(char *arg0, int arg1, char *arg2, int arg3, int arg4) {
    char *temp_a0;
    char *temp_v1;

    arg0 = dw4_cast_or_null(arg0, g_igVec4fMetaField_metaObject);
    arg2 = dw4_cast_or_null(arg2, g_igVec4fMetaField_metaObject);
    if ((arg0 != 0) && (arg2 != 0)) {
        temp_a0 = (char *)(arg1 + ((igVec4fMetaField *)arg0)->_offset);
        temp_v1 = (char *)(arg3 + ((igVec4fMetaField *)arg2)->_offset);
        *(float *)(temp_v1 + 0) = *(float *)(temp_a0 + 0);
        *(float *)(temp_v1 + 4) = *(float *)(temp_a0 + 4);
        *(float *)(temp_v1 + 8) = *(float *)(temp_a0 + 8);
        *(float *)(temp_v1 + 12) = *(float *)(temp_a0 + 12);
        return 1;
    }
    return 0;
}

int FUN_0022cf70(Q *arg0, int arg1, Q *arg2, int arg3, int arg4) {
    int var_v0;
    long long *dst;
    long long *src;
    Q *var_s3;
    Q *var_s1;

    if ((arg0 != 0) && (igObject_IsKindOf(arg0, DAT_00560f60[0]) != 0)) {
        var_s3 = arg0;
    } else {
        var_s3 = 0;
    }
    if ((arg2 != 0) && (igObject_IsKindOf(arg2, DAT_00560f60[0]) != 0)) {
        var_s1 = arg2;
    } else {
        var_s1 = 0;
    }
    if ((var_s3 != 0) && (var_s1 != 0)) {
        src = (long long *)(arg1 + var_s3->f8);
        dst = (long long *)(arg3 + var_s1->f8);
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        return 1;
    }
    return 0;
}

int FUN_0022d050(Q *arg0, int arg1, Q *arg2, int arg3, int arg4) {
    unsigned char *dst;
    unsigned char *src;
    Q *var_s3;
    Q *var_s1;

    if ((arg0 != 0) && (igObject_IsKindOf(arg0, DAT_00560f68[0]) != 0)) {
        var_s3 = arg0;
    } else {
        var_s3 = 0;
    }
    if ((arg2 != 0) && (igObject_IsKindOf(arg2, DAT_00560f68[0]) != 0)) {
        var_s1 = arg2;
    } else {
        var_s1 = 0;
    }
    if ((var_s3 != 0) && (var_s1 != 0)) {
        src = (unsigned char *)(arg1 + var_s3->f8);
        dst = (unsigned char *)(arg3 + var_s1->f8);
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        return 1;
    }
    return 0;
}

int FUN_0022d120(Q *arg0, int arg1, Q *arg2, int arg3, int arg4) {
    float *dst;
    float *src;
    Q *var_s3;
    Q *var_s1;

    if ((arg0 != 0) && (igObject_IsKindOf(arg0, g_igVec3fMetaField_metaObject[0]) != 0)) {
        var_s3 = arg0;
    } else {
        var_s3 = 0;
    }
    if ((arg2 != 0) && (igObject_IsKindOf(arg2, g_igVec3fMetaField_metaObject[0]) != 0)) {
        var_s1 = arg2;
    } else {
        var_s1 = 0;
    }
    if ((var_s3 != 0) && (var_s1 != 0)) {
        src = (float *)(arg1 + var_s3->f8);
        dst = (float *)(arg3 + var_s1->f8);
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        return 1;
    }
    return 0;
}

int FUN_0022d1f0(igMetaField *arg0, int arg1, igMetaField *arg2, int arg3, int arg4) {
    /* matching construct: variant search — decl order [1, 0]; the unit compiler assigns stack slots and registers in declaration order */
    char *temp_v1;
    char *temp_a0;

    arg0 = (igMetaField *)dw4_cast_or_null((char *)arg0, DAT_00560f80);
    arg2 = (igMetaField *)dw4_cast_or_null((char *)arg2, DAT_00560f80);
    if ((arg0 != 0) && (arg2 != 0)) {
        temp_a0 = (char *)(arg1 + arg0->_offset);
        temp_v1 = (char *)(arg3 + arg2->_offset);
        *(long long *)(temp_v1 + 0) = *(long long *)(temp_a0 + 0);
        *(long long *)(temp_v1 + 8) = *(long long *)(temp_a0 + 8);
        *(long long *)(temp_v1 + 16) = *(long long *)(temp_a0 + 16);
        return 1;
    }
    return 0;
}

int FUN_0022d2c0(char *arg0, int arg1, char *arg2, int arg3, int arg4) {
    char *temp_a0;
    char *temp_v1;

    arg0 = dw4_cast_or_null(arg0, g_igVec2fMetaField_metaObject);
    arg2 = dw4_cast_or_null(arg2, g_igVec2fMetaField_metaObject);
    if ((arg0 != 0) && (arg2 != 0)) {
        temp_a0 = (char *)(arg1 + ((igVec2fMetaField *)arg0)->_offset);
        temp_v1 = (char *)(arg3 + ((igVec2fMetaField *)arg2)->_offset);
        *(float *)(temp_v1 + 0) = *(float *)(temp_a0 + 0);
        *(float *)(temp_v1 + 4) = *(float *)(temp_a0 + 4);
        return 1;
    }
    return 0;
}

int FUN_0022d390(Q *arg0, int arg1, Q *arg2, int arg3, int arg4) {
    int var_v0;
    long long *dst;
    long long *src;
    Q *var_s3;
    Q *var_s1;

    if ((arg0 != 0) && (igObject_IsKindOf(arg0, DAT_00560f98[0]) != 0)) {
        var_s3 = arg0;
    } else {
        var_s3 = 0;
    }
    if ((arg2 != 0) && (igObject_IsKindOf(arg2, DAT_00560f98[0]) != 0)) {
        var_s1 = arg2;
    } else {
        var_s1 = 0;
    }
    if ((var_s3 != 0) && (var_s1 != 0)) {
        src = (long long *)(arg1 + var_s3->f8);
        dst = (long long *)(arg3 + var_s1->f8);
        dst[0] = src[0];
        dst[1] = src[1];
        return 1;
    }
    return 0;
}

extern "C" int FUN_0022d460(O_2 *arg0, int arg1, O_2 *arg2, int arg3, int arg4) {
    O_2 *s3 = O_2::Cast(arg0);
    O_2 *s1 = O_2::Cast(arg2);
    if (s3 != 0 && s1 != 0) {
        Matrix44_Copy(arg3 + s1->f8, arg1 + s3->f8);
        return 1;
    }
    return 0;
}

int FUN_0022d520(void *arg0, int arg1, void *arg2, int arg3, int arg4) {
    void *r0;
    void *r2;
    if (arg0 != 0 && igObject_IsKindOf(arg0, DAT_00561010[0]) != 0) {
        r0 = arg0;
    } else {
        r0 = 0;
    }
    if (arg2 != 0 && igObject_IsKindOf(arg2, DAT_00561010[0]) != 0) {
        r2 = arg2;
    } else {
        r2 = 0;
    }
    if (r0 != 0 && r2 != 0) {
        FUN_00190330(arg3 + *(int *)((char *)r2 + 8), arg1 + *(int *)((char *)r0 + 8));
        return 1;
    }
    return 0;
}

int FUN_0022d5e0(void *arg0, int arg1, void *arg2, int arg3, int arg4) {
    int var_v0;
    arg0 = cast0_2(arg0);
    arg2 = cast0_2(arg2);
    if ((arg0 != 0) && (arg2 != 0)) {
        var_v0 = 1;
        *(unsigned short *)(arg3 + *(int *)((char *)(arg2) + 8)) = *(unsigned short *)(arg1 + *(int *)((char *)(arg0) + 8));
    }
    else { var_v0 = 0; }
    return var_v0;
}

int FUN_0022d6a0(Q *arg0, int arg1, Q *arg2, int arg3, int arg4) {
    long long *dst;
    long long *src;
    Q *var_s3;
    Q *var_s1;

    if ((arg0 != 0) && (igObject_IsKindOf(arg0, g_igUnsignedLongMetaField_metaObject[0]) != 0)) {
        var_s3 = arg0;
    } else {
        var_s3 = 0;
    }
    if ((arg2 != 0) && (igObject_IsKindOf(arg2, g_igUnsignedLongMetaField_metaObject[0]) != 0)) {
        var_s1 = arg2;
    } else {
        var_s1 = 0;
    }
    if ((var_s3 != 0) && (var_s1 != 0)) {
        src = (long long *)(arg1 + var_s3->f8);
        dst = (long long *)(arg3 + var_s1->f8);
        dst[0] = src[0];
        return 1;
    }
    return 0;
}

int FUN_0022d760(void *arg0, int arg1, void *arg2, int arg3, int arg4) {
    int var_v0;
    arg0 = cast0_3(arg0);
    arg2 = cast0_3(arg2);
    if ((arg0 != 0) && (arg2 != 0)) {
        var_v0 = 1;
        *(int *)(arg3 + *(int *)((char *)(arg2) + 8)) = *(int *)(arg1 + *(int *)((char *)(arg0) + 8));
    }
    else { var_v0 = 0; }
    return var_v0;
}

int FUN_0022d820(void *arg0, int arg1, void *arg2, int arg3, int arg4) {
    void *r0;
    void *r2;
    if (arg0 != 0 && igObject_IsKindOf(arg0, g_igUnsignedCharMetaField_metaObject[0]) != 0) {
        r0 = arg0;
    } else {
        r0 = 0;
    }
    if (arg2 != 0 && igObject_IsKindOf(arg2, g_igUnsignedCharMetaField_metaObject[0]) != 0) {
        r2 = arg2;
    } else {
        r2 = 0;
    }
    if (r0 != 0 && r2 != 0) {
        *(unsigned char *)(arg3 + *(int *)((char *)r2 + 8)) = *(unsigned char *)(arg1 + *(int *)((char *)r0 + 8));
        return 1;
    }
    return 0;
}

int FUN_0022d8e0(struct M *arg0, int arg1, int arg2, int arg3, int arg4) {
    char *sp5C;
    char *t;
    int *temp_a1;
    int temp_v0;
    int var_v0;

    arg0 = (M *)cast0_4(arg0);
    arg2 = (int)cast0_4((void *)arg2);
    if ((arg0 != 0) && (arg2 != 0)) {
        sp5C = *(char **)(arg1 + arg0->f8);
        t = sp5C;
        if (t != 0) {
            *(int *)(t - 4) = *(int *)(t - 4) + 1;
        }
        igStringMetaField_AssignRetainedToken(arg2, arg3, &sp5C);
        var_v0 = 1;
        t = sp5C;
        if (t != 0) {
            temp_a1 = (int *)(t - 8);
            temp_v0 = *(int *)(t - 4) - 1;
            *(int *)(t - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
            var_v0 = 1;
        }
    }
    else { var_v0 = 0; }
    return var_v0;
}

int FUN_0022d9e0(int *arg0, int arg1, int *arg2, int arg3, int arg4) {
    int *source = castToType(arg0);
    int *destination = castToType(arg2);
    if (source != 0 && destination != 0) {
        *(short *)(arg3 + destination[2]) = *(short *)(arg1 + source[2]);
        return 1;
    }
    return 0;
}

int FUN_0022daa0(void *arg0, int arg1, void *arg2, int arg3, int arg4) {
    int var_v0;
    arg0 = cast0_5(arg0);
    arg2 = cast0_5(arg2);
    if ((arg0 != 0) && (arg2 != 0)) {
        var_v0 = 1;
        *(int *)(arg3 + *(int *)((char *)(arg2) + 8)) = *(int *)(arg1 + *(int *)((char *)(arg0) + 8));
    }
    else { var_v0 = 0; }
    return var_v0;
}

int FUN_0022db60(struct M *arg0, int arg1, int arg2, int arg3, int arg4) {
    int var_v0;

    arg0 = (M *)cast0_6(arg0);
    arg2 = (int)cast0_6((void *)arg2);
    if ((arg0 != 0) && (arg2 != 0)) {
        igObjectRefMetaField_Assign(arg2, arg3, *(int *)(arg1 + arg0->f8));
        var_v0 = 1;
    }
    else { var_v0 = 0; }
    return var_v0;
}

int FUN_0022dc20(void *arg0, int arg1, void *arg2, int arg3, int arg4) {
    int var_v0;
    arg0 = cast0_7(arg0);
    arg2 = cast0_7(arg2);
    if ((arg0 != 0) && (arg2 != 0)) {
        var_v0 = 1;
        *(int *)(arg3 + *(int *)((char *)(arg2) + 8)) = *(int *)(arg1 + *(int *)((char *)(arg0) + 8));
    }
    else { var_v0 = 0; }
    return var_v0;
}

int FUN_0022dce0(char *arg0, int arg1, char *arg2, int arg3, int arg4) {
    char *temp_a0;
    char *temp_v1;

    arg0 = dw4_cast_or_null(arg0, g_igLongMetaField_metaObject);
    arg2 = dw4_cast_or_null(arg2, g_igLongMetaField_metaObject);
    if ((arg0 != 0) && (arg2 != 0)) {
        temp_a0 = (char *)(arg1 + *(int *)(arg0 + 8));
        temp_v1 = (char *)(arg3 + *(int *)(arg2 + 8));
        *(long long *)temp_v1 = *(long long *)temp_a0;
        return 1;
    }
    return 0;
}

int FUN_0022dda0(Q *arg0, int arg1, Q *arg2, int arg3, int arg4) {
    Q *var_s3;
    Q *var_s1;

    if ((arg0 != 0) && (igObject_IsKindOf(arg0, g_igIntMetaField_metaObject[0]) != 0)) {
        var_s3 = arg0;
    } else {
        var_s3 = 0;
    }
    if ((arg2 != 0) && (igObject_IsKindOf(arg2, g_igIntMetaField_metaObject[0]) != 0)) {
        var_s1 = arg2;
    } else {
        var_s1 = 0;
    }
    if ((var_s3 != 0) && (var_s1 != 0)) {
        *(int *)(arg3 + var_s1->f8) = *(int *)(arg1 + var_s3->f8);
        return 1;
    }
    return 0;
}

int FUN_0022de60(void *arg0, char *arg1, void *arg2, char *arg3, int arg4) {
    int var_v0;
    arg0 = cast0_8(arg0);
    arg2 = cast0_8(arg2);
    if ((arg0 != 0) && (arg2 != 0)) {
        var_v0 = 1;
        *(float *)(arg3 + *(int *)((char *)(arg2) + 8)) = *(float *)(arg1 + *(int *)((char *)(arg0) + 8));
    }
    else { var_v0 = 0; }
    return var_v0;
}

int FUN_0022df20(void *arg0, int arg1, void *arg2, int arg3, int arg4) {
    int r;
    void *a;
    void *b;
    if (arg0 != 0 && igObject_IsKindOf(arg0, g_igEnumMetaField_metaObject[0]) != 0) {
        a = arg0;
    } else {
        a = 0;
    }
    if (arg2 != 0 && igObject_IsKindOf(arg2, g_igEnumMetaField_metaObject[0]) != 0) {
        b = arg2;
    } else {
        b = 0;
    }
    if (a != 0 && b != 0) {
        *(int *)(arg3 + *(int *)((char *)(b) + 8)) = *(int *)(arg1 + *(int *)((char *)(a) + 8));
        return 1;
    }
    return 0;
}

extern "C" int FUN_0022dfe0(void *arg0, int arg1, void *arg2, int arg3, int arg4) {
    K k;
    S_a *var_s3 = k.Cast(arg0);
    S_a *var_s1 = k.Cast(arg2);
    if (var_s3 != 0 && var_s1 != 0) {
        *(long long *)(arg3 + var_s1->f8) = *(long long *)(arg1 + var_s3->f8);
        return 1;
    }
    return 0;
}

int FUN_0022e0a0(void *arg0, int arg1, void *arg2, int arg3, int arg4) {
    int var_v0;
    arg0 = cast0_9(arg0);
    arg2 = cast0_9(arg2);
    if ((arg0 != 0) && (arg2 != 0)) {
        var_v0 = 1;
        *(char *)(arg3 + *(int *)((char *)(arg2) + 8)) = *(char *)(arg1 + *(int *)((char *)(arg0) + 8));
    }
    else { var_v0 = 0; }
    return var_v0;
}

int FUN_0022e160(struct M *arg0, int arg1, struct M *arg2, int arg3, int arg4) {
    int var_v0;

    arg0 = (M *)cast0_10(arg0);
    arg2 = (M *)cast0_10(arg2);
    if ((arg0 != 0) && (arg2 != 0)) {
        var_v0 = 1;
        *(unsigned char *)(arg3 + arg2->f8) = *(unsigned char *)(arg1 + arg0->f8);
    }
    else { var_v0 = 0; }
    return var_v0;
}

void Gap__igItemDataBaseList__vfunc_18(S_5 *arg0) {
    int temp_s0;

    temp_s0 = arg0->f8;
    if (temp_s0 < arg0->fC) {
        if (temp_s0 != 0) {
            arg0->f10 = FUN_00300e50(arg0, arg0->f10, temp_s0 * 0xC);
            arg0->fC = temp_s0;
            return;
        }
        FUN_00300f50(arg0, arg0->f10);
        arg0->f10 = 0;
        arg0->fC = arg0->f8;
    }
}

void Gap__igItemDataBaseList__vfunc_04(S_6 *arg0) {
    int n;
    int q;
    int neg;
    int cap;
    unsigned int p;
    unsigned int e;
    unsigned int q2;
    int r;

    n = arg0->f8;
    if (!(0 > arg0->fC)) {
        arg0->f8 = 0;
    } else {
        int c = f8_of(arg0);
        neg = -c;
        if (c == 0) {
            cap = 0x400;
        } else {
            q = neg >> 0xA;
            if (neg < 0) {
                q = (neg + 0x3FF) >> 0xA;
            }
            cap = (q != 0) ? c + ((q + 1) << 0xA) : c * 2;
        }
        arg0->f10 = FUN_00300e50(arg0, arg0->f10, cap * 0xC);
        arg0->fC = cap;
        arg0->f8 = 0;
    }
    p = arg0->f10;
    e = p + (n * 0xC);
    q2 = e;
    while (q2 < p) {
        r = FUN_00229700(0xC, q2);
        if (r != 0) {
            FUN_00229710((S_2 *)r);
        }
        q2 += 0xC;
    }
    while (p < e) {
        FUN_002297f0((S_3 *)p, -1);
        p += 0xC;
    }
    Gap__Core__igObject__vfunc_02(arg0);
}

void **FUN_0022e3c0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

