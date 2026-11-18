int *FUN_001a3c60(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3c70(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3c80(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3c90(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3ca0(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3cb0(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *igSmartPointer_igProjectionMatrixAttrPool_Construct(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *igSmartPointer_igMatrixObjectPool_Construct(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *igSmartPointer_igVertexBlendMatrixListAttrPool_Construct(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *igSmartPointer_igTextureMatrixAttrPool_Construct(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *igSmartPointer_igVertexBlendMatrixAttrPool_Construct(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *igSmartPointer_igTimeAttrPool_Construct(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *igSmartPointer_igModelViewMatrixAttrPool_Construct(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *igSmartPointer_igSorter_Construct(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *igSmartPointer_igVisualContext_Construct(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *igSmartPointer_igTransformStack_Construct(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *igSmartPointer_igAttrStackManager_Construct(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *igSmartPointer_igAttrDefaultManager_Construct(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *igSmartPointer_igCapabilityManager_Construct(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

void *FUN_001a3d90(igTraversal *arg0) {
    igObject_InitHeader((igObject *)arg0);
    *(int *)((char *)(arg0) + 0) = (int)(&g_igTraversal_vtable[0]);
    arg0->_travProcs = 0;
    return arg0;
}

void igCommonTraversal_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCommonTraversal_Register);
}

