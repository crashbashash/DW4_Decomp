namespace Gap {
namespace Attrs {

void igModelViewMatrixAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetMatrix((igPsx2VisualContext *)vc, IG_GFX_MATRIX_STACK_MODELVIEW, (char *)_m.m);
}

void igModelViewMatrixAttr::userRegister()
{

}

igModelViewMatrixAttr *igModelViewMatrixAttr::getIdentityAttr()
{
    int allocator;

    if (g_igModelViewMatrixAttr_instance == 0) {
        if (g_useOwnerAllocator != 0) { int owner = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent); allocator = owner; } else { int fallback = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleAttribute); allocator = fallback; }
        g_igModelViewMatrixAttr_instance.release();
        g_igModelViewMatrixAttr_instance.p = (::igModelViewMatrixAttr *)_instantiateFromPool((igMemoryPoolView *)allocator);
    }
    return (igModelViewMatrixAttr *)g_igModelViewMatrixAttr_instance.p;
}

void igModelViewMatrixAttr::userUnregister()
{
    g_igModelViewMatrixAttr_instance.clear();
}

void igModelViewMatrixAttr::synchronizeDefault(igVisualContext *vc)
{
    igMatrix44f m;

    vc->getMatrix(IG_GFX_MATRIX_STACK_MODELVIEW, m);
    setMatrix(m);
}

void igModelViewMatrixAttr::setMatrix(const igMatrix44f &matrix)
{
    igMatrix44f_Copy(_m.m, matrix.m);
}
}
}

void FUN_0013f800(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 20) = arg1;
}

