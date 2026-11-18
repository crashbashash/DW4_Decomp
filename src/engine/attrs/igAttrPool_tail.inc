int igAttrPool_AddNonSharableType(int *p, void *meta)
{
    return ObjectList_AppendUniqueRetained((igTDataList<igObject *> *)(*(int *)((char *)p + 12)), (igObject *)meta);
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

void igAttrPool_resetFields(igAttrPool *self, int flags) {
    void *metas[4];
    int i;
    Gap__Core__igObject__resetFields((igObject *)self, flags);
    clearBytes((char *)metas, sizeof(metas));
    metas[0] = igTextureBindAttr_GetMetaObject();
    metas[1] = igTextureAttr_GetMetaObject();
    metas[2] = igLightAttr_GetMetaObject();
    metas[3] = igLightStateAttr_GetMetaObject();
    for (i = 0; i < 4; i++) {
        igAttrPool_AddNonSharableType((int *)self, metas[i]);
    }
}

