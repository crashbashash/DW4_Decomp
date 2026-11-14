
extern "C" void Gap__Sg__igShaderData__resize(ShaderDataView *self, int count);

/* Resizes the push, pop and child lists to {count}; child slots past the old count are released and cleared. */
void Gap__Sg__igShaderData__resize(ShaderDataView *self, int count) {
    int i;
    ObjectList_ResizeRetained(self->_attrPushLists, count);
    ObjectList_ResizeRetained(self->_attrPopLists, count);
    i = self->_childLists->count;
    ObjectList_ResizeRetained(self->_childLists, count);
    /* matching construct: check.py — the loop guard is emitted after the loop and re-enters at the test */
    goto guard;
next:
    {
        ShaderDataList *children = self->_childLists;
        ShaderDataEntry *old = children->data[i];
        if (old != 0) {
            old->references = old->references - 1;
            if (((unsigned long long)((long long)old->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)old);
            }
        }
        if (children->count != 0 && i >= 0 && i < children->count) {
            children->data[i] = 0;
        }
    }
    i++;
test:
    if (i < count) goto next;
done:
    return;
guard:
    if (i < count) goto test;
    goto done;
}

void Gap__Sg__igShaderData__vfunc_24(void *arg0, int dummy1, int arg2, int arg3) {
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 8));
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 12), arg2);
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 20), arg3);
}

void Gap__Sg__igShaderData__vfunc_25(struct ShaderDataView *arg0) {
    ShaderDataList *l;
    int n;
    int i;
    ShaderDataEntry *o;
    l = arg0->_attrPushLists;
    n = l->count;
    for (i = 0; i < n; i++) {
        o = l->data[i];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)o);
            }
        }
    }
    {
        int m = l->count;
        int j;
        for (j = 0; j < m; j++) {
            l->data[j] = 0;
        }
    }
    l->count = 0;
    l = arg0->_attrPopLists;
    n = l->count;
    for (i = 0; i < n; i++) {
        o = l->data[i];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)o);
            }
        }
    }
    {
        int m = l->count;
        int j;
        for (j = 0; j < m; j++) {
            l->data[j] = 0;
        }
    }
    l->count = 0;
    l = arg0->_childLists;
    n = l->count;
    for (i = 0; i < n; i++) {
        o = l->data[i];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)o);
            }
        }
    }
    {
        int m = l->count;
        int j;
        for (j = 0; j < m; j++) {
            l->data[j] = 0;
        }
    }
    l->count = 0;
    o = arg0->_dataPumps;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)o);
        }
    }
    arg0->_dataPumps = 0;
}

void FUN_001d86f0(struct S_1d86f0 *arg0, int arg1, igObject *arg2) {
    igObjectList *l;
    int off;
    int n;
    igObject *old;
    l = arg0->f8;
    if (arg2 != 0) {
        arg2->_refCount = arg2->_refCount + 1;
    }
    off = arg1 * 4;
    old = *(igObject **)(l->_data + off);
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if (((unsigned long long) ((long long) (int) old->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)old);
        }
    }
    n = l->_count;
    if (n != 0 && arg1 >= 0 && arg1 < n) {
        *(igObject **)(l->_data + off) = arg2;
    }
}

void FUN_001d87b0(igTransformSequence *arg0, int arg1, igObject *arg2) {
    igObjectList *temp_s1;
    int temp_s0;
    int temp_v1;
    igObject *temp_a0;
    temp_s1 = (igObjectList *)arg0->_quatList;
    if (arg2 != 0) {
        arg2->_refCount = arg2->_refCount + 1;
    }
    temp_s0 = arg1 * 4;
    temp_a0 = *(igObject **)(temp_s1->_data + temp_s0);
    if (temp_a0 != 0) {
        temp_a0->_refCount = temp_a0->_refCount - 1;
        if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy((void *)temp_a0);
        }
    }
    temp_v1 = temp_s1->_count;
    if ((temp_v1 != 0) && (arg1 >= 0) && (arg1 < temp_v1)) {
        *(igObject **)(temp_s1->_data + temp_s0) = arg2;
    }
}

void FUN_001d8870(struct A_1d8870 *arg0, int arg1, igObject *arg2) {
    igObjectList *l;
    igObject *old;
    int n;
    int off;
    l = arg0->f20;
    if (arg2 != 0) {
        arg2->_refCount = arg2->_refCount + 1;
    }
    off = arg1 * 4;
    old = *(igObject **)(l->_data + off);
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy((void *)old);
        }
    }
    n = l->_count;
    if (n != 0 && arg1 >= 0 && arg1 < n) {
        *(igObject **)(l->_data + off) = arg2;
    }
}

void Gap__Sg__igShaderData__vfunc_17(S0_1d8930 *arg0) {
    int temp_a1;
    void *temp_a0;

    igObject_UserPostLoad();
    temp_a0 = (void *)(arg0->f14);
    temp_a1 = *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 8);
    if (temp_a1 != *(int *)((char *)(temp_a0) + 8)) {
        ObjectList_ResizeRetained(temp_a0, temp_a1);
        ObjectList_ClearRetainedPreserveCount(arg0->f14);
    }
}

