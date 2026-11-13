void Gap__Gfx__igPsx2VisualContext__vfunc_197(struct S_180030 *arg0, int arg1, int arg2) {
    arg0->f72 = arg1;
    arg0->f84 = arg2;
    arg0->f1424 = 1;
    arg0->f76 = arg0->f76 + 1;
    p2SetBlendMatrices(arg0->f84, arg0->f72);
}

void FUN_00180060(O_180060 *arg0) {
    int sp5C;
    int v[3];
    char *s0;
    char *s2;
    unsigned int i;
    int off;
    if (arg0->f84 != 0) {
        if (arg0->f1420 < (int)arg0->f72) {
            s0 = arg0->f80;
            if (s0 != 0) {
                ((V1 *)FUN_00165cc0((int *)arg0))->v264(s0);
                arg0->f80 = 0;
            }
            arg0->f80 = (char *)((V2_180060 *)FUN_00165cc0((int *)arg0))->v220(arg0->f72 << 6, 0x10);
            arg0->f1420 = arg0->f72;
        }
        for (i = 0; i < arg0->f72; i++) {
            off = i << 6;
            s2 = arg0->f80 + off;
            Matrix44_Invert(&sp5C, s2, arg0->f84 + off);
            v[0] = 0;
            v[1] = 0;
            v[2] = 0;
            Matrix44_SetTranslation(s2, v);
            FUN_001903d0(s2);
        }
    }
    arg0->f1424 = 0;
}

static inline void createOwned(igSmartPointer<BuildResource> &holder, AdoptReference) {
    RELEASE(holder.p);
    holder.p = (BuildResource *)FUN_0014b390(0);
}

static inline void setMember(const igSmartPointer<BuildResource> &owner, const igSmartPointer<BuildResource> &value) {
    BuildResource *held = value.p;
    BuildResource *target = owner.p;
    BuildResource *old;
    if (held != 0) held->_refCount = held->_refCount + 1;
    old = target->f12;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    target->f12 = held;
}

void FUN_001805a0(ResourceBuilder *arg0, ResourceSource *arg1, int arg2) {
BuildResource *s2;
BuildResource *s1;
ResourceList *ll;
BuildResource *s0o;
int s0;
BuildResource *s7;
    s0 = arg1->f20;
    s2 = 0;
    igSmartPointer<BuildResource> first((BuildResource *)0, kRetainReference);
    igSmartPointer<BuildResource> second((BuildResource *)0, kRetainReference);
    s7 = (BuildResource *)FUN_0015f4a0((S_15f430 *)s0, 5, 0);
    s1 = (BuildResource *)FUN_0015f4a0((S_15f430 *)s0, 6, 0);
    if (arg0->f1340 != 0 || arg0->f644 == 2) {
        if (arg0->f1424 != 0) FUN_00180060((O_180060 *)arg0);
        second = (BuildResource *)FUN_0015f510((L *)s0, 3, 0, 0x7734);
        if (second.p == 0) {
            igSmartPointer<BuildResource> values((BuildResource *)FUN_0018a060(0), AdoptReference());
            ll = (ResourceList *)values.p;
            if (arg2 >= 0) {
                if (arg2 <= ll->cap) ll->count = arg2;
                else List_Resize((BuildResource *)ll, arg2, 12);
            }
            createOwned(second, AdoptReference());
            setMember(second, values);
            second.p->f16 = 3;
            second.p->f28 = 0x7734;
            ObjectList_AppendRetained(s0, second.p);
            s2 = (BuildResource *)FUN_0015f4a0((S_15f430 *)s0, 3, 0);
            s2->f20 = 0x7734;
        } else {
            s2 = (BuildResource *)FUN_0015f4a0((S_15f430 *)s0, 3, 0x7734);
        }
    }
    first = (BuildResource *)FUN_0015f510((L *)s0, 1, 0, 0x7734);
    if (first.p == 0) {
        igSmartPointer<BuildResource> values((BuildResource *)FUN_0018a060(0), AdoptReference());
        ll = (ResourceList *)values.p;
        if (arg2 >= 0) {
            if (arg2 <= ll->cap) ll->count = arg2;
            else List_Resize((BuildResource *)ll, arg2, 12);
        }
        createOwned(first, AdoptReference());
        setMember(first, values);
        first.p->f16 = 1;
        first.p->f28 = 0x7734;
        ObjectList_AppendRetained(s0, first.p);
        s0o = (BuildResource *)FUN_0015f4a0((S_15f430 *)s0, 1, 0);
        s0o->f20 = 0x7734;
    } else {
        s0o = (BuildResource *)FUN_0015f4a0((S_15f430 *)s0, 1, 0x7734);
    }
    FUN_00180020((long long *)arg1);
    FUN_00180ab0(arg0, s0o, first.p, s2, second.p, s7, s1, FUN_00162ca0(s1));
}

