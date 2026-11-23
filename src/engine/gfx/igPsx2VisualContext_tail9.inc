void igPsx2VisualContext_SetBlendingMatrices(igPsx2VisualContext *self, unsigned int count, igMatrix44f *matrices) {
    struct S_180030 *arg0 = (struct S_180030 *)self;
    arg0->f72 = count;
    arg0->f84 = (int)matrices;
    arg0->f1424 = 1;
    arg0->f76 = arg0->f76 + 1;
    p2SetBlendMatrices(arg0->f84, arg0->f72);
}

void FUN_00180060(O_180060 *arg0) {
    int v[3];
    char *s0;
    char *s2;
    unsigned int i;
    int off;
    if (arg0->f84 != 0) {
        if (arg0->f1420 < (int)arg0->f72) {
            s0 = arg0->f80;
            if (s0 != 0) {
                ((V1 *)((Gap::Gfx::igVisualContext *)arg0)->getDriverDataMemoryPool())->v264(s0);
                arg0->f80 = 0;
            }
            arg0->f80 = (char *)((V2_180060 *)((Gap::Gfx::igVisualContext *)arg0)->getDriverDataMemoryPool())->v220(arg0->f72 << 6, 0x10);
            arg0->f1420 = arg0->f72;
        }
        for (i = 0; i < arg0->f72; i++) {
            off = i << 6;
            s2 = arg0->f80 + off;
            igMatrix44f_Invert((float *)s2, (const float *)(arg0->f84 + off));
            v[0] = 0;
            v[1] = 0;
            v[2] = 0;
            igMatrix44f_SetTranslation((float *)s2, (float *)v);
            FUN_001903d0((float *)s2);
        }
    }
    arg0->f1424 = 0;
}

static inline void createOwned(igSmartPointer<BuildResource> &holder, AdoptReference) {
    RELEASE(holder.p);
    holder.p = (BuildResource *)igVertexData_Create(0);
}

static inline void setMember(const igSmartPointer<BuildResource> &owner, const igSmartPointer<BuildResource> &value) {
    BuildResource *held = value.p;
    BuildResource *target = owner.p;
    BuildResource *old;
    if (held != 0) held->_refCount = held->_refCount + 1;
    old = target->f12;
    igObject::release(old);
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
            igSmartPointer<BuildResource> values((BuildResource *)igVec3fList_Create(0), AdoptReference());
            ll = (ResourceList *)values.p;
            if (arg2 >= 0) {
                if (arg2 <= ll->cap) ll->count = arg2;
                else ((Gap::Core::igDataList *)ll)->resizeAndSetCount(arg2, 12);
            }
            createOwned(second, AdoptReference());
            setMember(second, values);
            second.p->f16 = 3;
            second.p->f28 = 0x7734;
            ((Gap::Core::igObjectList *)s0)->append((Gap::Core::igObject *)second.p);
            s2 = (BuildResource *)FUN_0015f4a0((S_15f430 *)s0, 3, 0);
            s2->f20 = 0x7734;
        } else {
            s2 = (BuildResource *)FUN_0015f4a0((S_15f430 *)s0, 3, 0x7734);
        }
    }
    first = (BuildResource *)FUN_0015f510((L *)s0, 1, 0, 0x7734);
    if (first.p == 0) {
        igSmartPointer<BuildResource> values((BuildResource *)igVec3fList_Create(0), AdoptReference());
        ll = (ResourceList *)values.p;
        if (arg2 >= 0) {
            if (arg2 <= ll->cap) ll->count = arg2;
            else ((Gap::Core::igDataList *)ll)->resizeAndSetCount(arg2, 12);
        }
        createOwned(first, AdoptReference());
        setMember(first, values);
        first.p->f16 = 1;
        first.p->f28 = 0x7734;
        ((Gap::Core::igObjectList *)s0)->append((Gap::Core::igObject *)first.p);
        s0o = (BuildResource *)FUN_0015f4a0((S_15f430 *)s0, 1, 0);
        s0o->f20 = 0x7734;
    } else {
        s0o = (BuildResource *)FUN_0015f4a0((S_15f430 *)s0, 1, 0x7734);
    }
    ((Gap::Gfx::igPsx2VertexStream *)((long long *)arg1))->waitForSync();
    FUN_00180ab0(arg0, s0o, first.p, s2, second.p, s7, s1, Gap::Gfx::igVertexArray2Helper::getIndexCount((const igVertexData *)s1));
}

