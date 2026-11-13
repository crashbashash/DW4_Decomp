int Gap__Insight__igWindowResizeEventReceiver__vfunc_32(Receiver *self, int width, int height) {
    igSmartPointer<ResizeEvent> event((ResizeEvent *)FUN_002332b0(igObject_GetAllocator()));
    {
        ResizeEvent *e = event.get();
        e->origin[0] = DAT_004e0fa0[0];
        e->origin[1] = DAT_004e0fa4[0];
    }
    {
        ResizeEvent *e = event.get();
        e->size[0] = (float)width;
        e->size[1] = (float)height;
    }
    FUN_00237ea0((igMessageDispatcherOwnerView *)self->f8->f40, event.get());
    return 0;
}

void igInsightCore_AddManager(void *arg0, void *arg1) {
    if (FUN_00236b70() == 0) {
        igRendererOrderedList_Append(*(int *)((char *)(arg0) + 8), arg1, 0);
        *(int *)((char *)(arg1) + 12) = (int)(arg0);
        ((DW4VC_92_0 *)(((char *)(arg1) + 0)))->vX();
    }
}

void igInsightCore_RemoveManager(void *arg0, void *arg1) {
    int sp3C;

    if (FUN_00236b70() != 0) {
        ((DW4VC_96_0 *)(((char *)(arg1) + 0)))->vX();
        *(int *)((char *)(arg1) + 12) = 0;
        FUN_002d7750(&sp3C, *(int *)((char *)(arg0) + 8), arg1);
    }
}

void igInsightCore_AddToScheduler(S12 *arg0, int arg1) {
    if (((DW4VC_104_0 *)(arg0->f12))->vX() == 0) {
        ((DW4VC_96_1 *)(arg0->f12))->vX(arg1);
    }
}

void igInsightCore_RemoveFromScheduler(S236 *arg0, int arg1) {
    if (((DW4VC_104_0 *)arg0->p)->vX() != 0) {
        ((DW4VC_100_1 *)arg0->p)->vX((int)(arg1));
    }
}

void FUN_00236ca0(int self) {
    int meta;
    int count;
    int i;
    count = igMetaObject_CountTree(meta = (int)igInsightPlugin_GetMetaObject());
    for (i = 0; i < count; i++) {
        int type = FUN_002fe300(meta, i);
        igSmartPointer<Instance> plugin(FUN_002fd6e0(type, igObject_GetAllocator(self)).get(), kRetainReference);
        if (plugin.get()) {
            FUN_00236dd0((void *)self, (void **)plugin.get());
        }
    }
}

void FUN_00236dd0(void *arg0, void **arg1) {
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 104));
    ((DW4VC_92_1 *)(arg1))->vX((int)(arg0));
}

void FUN_00236e20(void *arg0, void **arg1) {
    int sp3C;

    ((DW4VC_96_1 *)(arg1))->vX((int)(arg0));
    ObjectList_RemoveFirstRetained(&sp3C, *(int *)((char *)(arg0) + 104), arg1, 0);
}

void FUN_00236e80(A *arg0) {
    int i;

    for (i = arg0->f68->cnt - 1; i >= 0; i--) {
        FUN_00236e20(arg0, (void **)arg0->f68->arr[i]);
    }
}

void igInsightCore_AddRenderer(void *arg0, int arg1) {
    FUN_00457ca0(arg1, *(int *)((char *)arg0 + 24));
    igRendererOrderedList_Append(*(int *)((char *)arg0 + 28), arg1, 0);
}

void igInsightCore_RemoveRenderer(Obj_236f30 *arg0, int arg1) {
    int sp2C;
    FUN_002d7750(&sp2C, arg0->f28, arg1);
    if (sp2C == g_statusSucceeded[0]) {
        FUN_00457ca0(arg1, 0);
    }
}

Obj_236f80 *igInsightCore_FindManager(Self *arg0, int arg1) {
    unsigned int i;
    for (i = 0; i < arg0->mid->list->count; i++) {
        Obj_236f80 *o = arg0->mid->list->arr[i];
        int r = o->v20(); if (r == arg1) return o;
    }
    return 0;
}

int FUN_00237010(void) {
    return (int)g_igInfoManager_metaObject[0];
}

int igInsightCore_AddRendererOrder(int *p)
{
    return FUN_002d7090(*(int *)((char *)p + 28));
}

