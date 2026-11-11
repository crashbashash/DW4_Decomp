E *FUN_00237990(const A_237990 *arg0, int arg1) {
    int i;
    int n;
    E *e;

    n = arg0->f8->f8;
    for (i = 0; i < n; i++) {
        e = arg0->f8->f16[i];
        if (arg1 == e->f8) {
            return e;
        }
    }
    return 0;
}

igSmartPointer<MessageFilter> FUN_002379e0(FilterDispatcher *self, igObject *target)
{
    igSmartPointer<MessageFilter> filter((MessageFilter *)FUN_00237990((const A_237990 *)self, (int)target), kRetainReference);
    if (filter == 0) {
        void *allocator = (void *)igObject_GetAllocator(self);
        filter.release();
        filter.p = (MessageFilter *)FUN_00231b40((int)allocator);
        filter->_target = target;
        ObjectList_AppendRetained(self->_filters, filter.get());
    }
    return filter;
}

void Gap__Insight__igFilterMessageDispatcher__vfunc_28(N *arg0, int arg1) {
    int n;
    int i;
    N *t;
    int m;
    int j;
    n = arg0->f12->cnt;
    for (i = 0; i < n; i++) {
        t = arg0->f12->data[i];
        if (t->vX(arg1) != 0) {
            m = t->f12->cnt;
            for (j = 0; j < m; j++) {
                t->f12->data[j]->vX(arg1);
            }
        }
    }
}

