void FUN_001ce710(void) {
    *(int *)0x562790 = FUN_0019a6e0(Memory_GetAllocatorBySelector(*(int *)0x587038));
}

void FUN_001ce740(void) {
    void *temp_a0;

    temp_a0 = *(void **)0x562790;
    if (temp_a0 != 0) {
        *(int *)((char *)temp_a0 + 4) = (int) (*(int *)((char *)temp_a0 + 4) - 1);
        if (((unsigned long long) ((long long) *(int *)((char *)temp_a0 + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
}

void FUN_001ce790(int arg0, int arg1) {
    FUN_001e02f0(arg0, arg1);
    if (FUN_002fe290(arg1, ((int)igNode_GetMetaObject())) != 0) {
        if (FUN_002fe290(arg1, ((int)igGeometry_GetMetaObject())) != 0) {
            FUN_001e06c0((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)&FUN_001cfc70);
            return;
        }
        if (FUN_002fe290(arg1, ((int)igTransform_GetMetaObject())) != 0) {
            FUN_001e06c0((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)&FUN_001cfaa0);
            return;
        }
        if (FUN_002fe290(arg1, ((int)igGroup_GetMetaObject())) != 0) {
            FUN_001e06c0((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)&FUN_001cf990);
            return;
        }
        FUN_001e06c0((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)((int *)FUN_001cf980));
    }
}

void Gap__Bec__beHitLandModelTraversal__vfunc_11(beHitLandModelTraversal *arg0) {
    igObject *sp3C;
    igObject *s0;
    igObject *old;

    Gap__Core__igObject__vfunc_11();
    FUN_0018f760(&sp3C, igObject_GetAllocator(arg0));
    s0 = sp3C;
    if (s0 != 0) {
        s0->_refCount = s0->_refCount + 1;
    }
    old = (igObject *)arg0->_volumes;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy((void *)old);
        }
    }
    arg0->_volumes = (int)s0;
    if (sp3C != 0) {
        sp3C->_refCount = sp3C->_refCount - 1;
        if ((sp3C->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy((void *)sp3C);
        }
    }
    FUN_001ce970((TraversalMatrixState *)arg0);
}

void FUN_001ce970(TraversalMatrixState *self) {
    ReleasableList *o;
    int cnt;
    int idx;
    int j;
    MatrixStackList *m;
    int n;
    int i;
    self->mats->n = 0;
    m = self->mats;
    idx = m->n;
    if (idx < m->cap) {
        m->n = n_of_1ce970(m) + 1;
    } else {
        List_Resize(m, idx + 1, 64);
    }
    Matrix44_Copy(m->data + idx, DAT_004e0ef0);
    o = self->objs;
    n = o->n;
    for (i = 0; i < n; i++) {
        CountedObject *p = (CountedObject *)o->data[i];
        if (p != 0) {
            p->rc = p->rc - 1;
            if (((unsigned long long)((long long)p->rc << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    cnt = o->n;
    for (j = 0; j < cnt; j++) {
        o->data[j] = 0;
    }
    o->n = 0;
}

void Gap__Bec__beHitLandModelTraversal__vfunc_21(void *self, int arg1)
{
    Gap__Sg__igTraversal__vfunc_23(self, arg1);
}

void Gap__Bec__beHitLandModelTraversal__vfunc_22(void *self, int arg1)
{
    Gap__Sg__igTraversal__vfunc_24(self, arg1);
}

