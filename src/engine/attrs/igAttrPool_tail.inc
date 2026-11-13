int FUN_0013c1b0(int *p, void *meta)
{
    return ObjectList_AppendUniqueRetained(*(int *)((char *)p + 12), meta);
}

static inline void clearBytes(char *p, unsigned int n) {
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
}

void Gap__Attrs__igAttrPool__vfunc_13(igAttrPool *self) {
    void *metas[4];
    int i;
    Gap__Core__igObject__resetFields((igObject *)self);
    clearBytes((char *)metas, sizeof(metas));
    metas[0] = igTextureBindAttr_GetMetaObject();
    metas[1] = igTextureAttr_GetMetaObject();
    metas[2] = igLightAttr_GetMetaObject();
    metas[3] = igLightStateAttr_GetMetaObject();
    for (i = 0; i < 4; i++) {
        FUN_0013c1b0((int *)self, metas[i]);
    }
}

