void FUN_001d4180(void) {
    DAT_005628d8[0] = (int)Gap::Attrs::igTextureBindAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_005627e8[0] = (int)Gap::Attrs::igTextureStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_005627f0[0] = (int)Gap::Attrs::igTextureStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_005627f8[0] = (int)Gap::Attrs::igTextureStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562800[0] = (int)Gap::Attrs::igBlendFunctionAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562808[0] = (int)Gap::Attrs::igBlendFunctionAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562810[0] = (int)Gap::Attrs::igBlendStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562818[0] = (int)Gap::Attrs::igBlendStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562820[0] = (int)Gap::Attrs::igLightingStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562838[0] = (int)Gap::Attrs::igClearAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562840[0] = (int)Gap::Attrs::igClearAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562848[0] = (int)Gap::Attrs::igClearAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562850[0] = (int)Gap::Attrs::igDepthStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562858[0] = (int)Gap::Attrs::igTextureCoordSourceAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562860[0] = (int)Gap::Attrs::igTextureCoordSourceAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    g_shadowTextureFunctionAttr0[0] = (igTextureFunctionAttr *)Gap::Attrs::igTextureFunctionAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562870[0] = (int)Gap::Attrs::igTextureFunctionAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562878[0] = (int)Gap::Attrs::igTextureMatrixStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562880[0] = (int)Gap::Attrs::igTextureMatrixStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562828[0] = (int)Gap::Attrs::igAlphaFunctionAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_00562830[0] = (int)Gap::Attrs::igAlphaStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_005628d0[0] = (int)Gap::Attrs::igAlphaStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    DAT_005627e0[0] = (int)Gap::Attrs::igRenderDestinationAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
}

namespace Gap {
namespace Sg {

void igProjectiveShadowShader::userConstruct(int flag)
{
    igNode::userConstruct(flag);
    if (igMetaObject_CountInstances(getMeta(), 1) == 0)
        FUN_001d4180();
}
}
}

void igProjectiveShadowShader_ConfigureSharedAttrs(void) {
    ShadowColor black;
    ShadowColor white;
    ((ShadowSetupObj *)DAT_005628d8[0])->s23(0);
    {
        ShadowRef image;
        image.p = (ShadowSetupObj *)Gap::Attrs::igTextureAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
        ((ShadowSetupObj *)DAT_005628d8[0])->s31((int)image.p);
        ShadowRef texture;
        texture.p = (ShadowSetupObj *)Gap::Gfx::igImage::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
        ((Gap::Attrs::igTextureAttr *)image.p)->setImage((Gap::Gfx::igImage *)texture.p, 0);
        texture.p->s26(1);
        texture.p->s27(1);
        texture.p->s28(5);
        texture.p->s29();
        unsigned char *px = texture.p->pixels;
        px[0] = 255;
        px[1] = 255;
        px[2] = 255;
        image.p->s30(0);
        image.p->s31(0);
        image.p->s32(0);
        image.p->s33(0);
    }
    ((ShadowSetupObj *)DAT_005627e8[0])->s23(0);
    ((ShadowSetupObj *)DAT_005627e8[0])->s30(1);
    ((ShadowSetupObj *)DAT_005627f0[0])->s23(1);
    ((ShadowSetupObj *)DAT_005627f0[0])->s30(1);
    ((ShadowSetupObj *)DAT_005627f8[0])->s23(0);
    ((ShadowSetupObj *)DAT_005627f8[0])->s30(0);
    ((ShadowSetupObj *)DAT_00562820[0])->s30(0);
    ((ShadowSetupObj *)DAT_00562850[0])->s30(0);
    ((ShadowSetupObj *)DAT_00562800[0])->s30(0);
    ((ShadowSetupObj *)DAT_00562800[0])->s31(5);
    ((ShadowSetupObj *)DAT_00562808[0])->s30(1);
    ((ShadowSetupObj *)DAT_00562808[0])->s31(1);
    ((ShadowSetupObj *)DAT_00562810[0])->s30(1);
    ((ShadowSetupObj *)DAT_00562818[0])->s30(0);
    black.r = 0.0f; black.g = 0.0f; black.b = 0.0f; black.a = 0.0f;
    ((ShadowColorObj *)DAT_00562838[0])->enabled = 1;
    ((ShadowModeObj *)DAT_00562848[0])->mode = 1;
    white.r = 1.0f; white.g = 1.0f; white.b = 1.0f; white.a = 1.0f;
    ((ShadowColorObj *)DAT_00562838[0])->setColor(white);
    ((ShadowColorObj *)DAT_00562840[0])->setColor(black);
    ((ShadowColorObj *)DAT_00562840[0])->enabled = 1;
    ((ShadowSetupObj *)DAT_00562858[0])->s30(1);
    ((ShadowSetupObj *)DAT_00562858[0])->s23(0);
    ((ShadowSetupObj *)DAT_00562860[0])->s30(1);
    ((ShadowSetupObj *)DAT_00562860[0])->s23(1);
    ((ShadowModeObj *)((ShadowSetupObj *)g_shadowTextureFunctionAttr0[0]))->mode = 1;
    ((ShadowSetupObj *)g_shadowTextureFunctionAttr0[0])->s23(0);
    ((ShadowModeObj *)((ShadowSetupObj *)DAT_00562870[0]))->mode = 1;
    ((ShadowSetupObj *)DAT_00562870[0])->s23(1);
    ((ShadowSetupObj *)DAT_00562878[0])->s30(1);
    ((ShadowSetupObj *)DAT_00562878[0])->s23(0);
    ((ShadowSetupObj *)DAT_00562880[0])->s30(1);
    ((ShadowSetupObj *)DAT_00562880[0])->s23(1);
    ((ShadowFogObj *)DAT_00562828[0])->s30(4);
    ((ShadowFogObj *)DAT_00562828[0])->s31(0.01f);
    ((ShadowSetupObj *)DAT_00562830[0])->s30(1);
    ((ShadowSetupObj *)DAT_005628d0[0])->s30(0);
}

void FUN_001d5430(void) {
    R_1d5430 *t;
    t = ((R_1d5430 * *)DAT_005628d8)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_005628d8)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_005627e8)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_005627e8)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_005627f0)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_005627f0)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_005627f8)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_005627f8)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562800)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562800)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562808)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562808)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562810)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562810)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562818)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562818)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562820)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562820)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562838)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562838)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562840)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562840)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562850)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562850)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562858)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562858)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562860)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562860)[0] = 0;
    }
    t = ((R_1d5430 * *)g_shadowTextureFunctionAttr0)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)g_shadowTextureFunctionAttr0)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562870)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562870)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562878)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562878)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562880)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562880)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562828)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562828)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562830)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562830)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_005628d0)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_005628d0)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_005627e0)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_005627e0)[0] = 0;
    }
    t = ((R_1d5430 * *)DAT_00562848)[0];
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)t);
        ((R_1d5430 * *)DAT_00562848)[0] = 0;
    }
}

namespace Gap {
namespace Sg {

void igProjectiveShadowShader::userDestruct()
{
    if (igMetaObject_CountInstances(getMeta(), 1) == 0)
        FUN_001d5430();
    igGroup::userDestruct();
}
}
}

int FUN_001d5a70(P *arg0, Q_1d5a70 *arg1) {
    V4_1d5a70 v;
    int s0 = arg1->w52;
    FUN_001dc500((A_1dc500 *)arg1->w68, 0, 0);
    float w = 1.0f - arg0->f68;
    v.x = 0; v.y = 0; v.z = 0;
    v.w = w;
    arg0->o116->v30(&v);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_00562820[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_00562850[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)arg0->w152);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)arg0->w156);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)arg0->w192);
    FUN_001d9ac0((struct A_1d9ac0 *)arg1->w68, DAT_00562840[0], s0);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s0, (igAttr *)arg0->w192);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_005627f8[0]);
    FUN_001b1030((igAttrStackManager *)s0, (igAttr *)arg0->w88);
    FUN_001b1030((igAttrStackManager *)s0, (igAttr *)arg0->w92);
    if (arg0->b237 != 0) {
        igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)((int)arg0->o116));
    }
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)arg0->w196);
    FUN_001d5ef0((struct S60 *)arg0, (int)arg1);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s0, (igAttr *)arg0->w196);
    if (arg0->b237 != 0) {
        igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s0, (igAttr *)((int)arg0->o116));
    }
    FUN_001b1100((struct A_1b1100 *)s0, (struct B_1b1100 *)arg0->w92);
    FUN_001b1100((struct A_1b1100 *)s0, (struct B_1b1100 *)arg0->w88);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_005627f8[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s0, (igAttr *)arg0->w156);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s0, (igAttr *)arg0->w152);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_00562850[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_00562820[0]);
    FUN_001dc610((igSorter *)arg1->w68);
    return arg0->w164;
}

void FUN_001d5c40(A0_1d5c40 *arg0, A1_1d5c40 *arg1) {
    int temp_s1;
    int temp_s0;

    temp_s0 = arg1->f34;
    FUN_001dc500((A_1dc500 *)arg1->f44, 0, 0);
    temp_s1 = FUN_001d5a70((P *)arg0, (Q_1d5a70 *)arg1);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg1->fe8);
    if (arg0->f94 != 0) {
        FUN_001d5e60((struct A_1d5e60 *)arg0, (int)arg1);
    }
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005627e8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)temp_s1);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_00562858[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)g_shadowTextureFunctionAttr0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg0->f90);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_00562878[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_00562810[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_00562800[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005628d0[0]);
    FUN_001d5e60((struct A_1d5e60 *)arg0, (int)arg1);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005628d0[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_00562800[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_00562810[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_00562878[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg0->f90);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)g_shadowTextureFunctionAttr0[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_00562858[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)temp_s1);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005627e8[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg1->fe8);
    FUN_001d5e00((void *)arg0, (S1_1d5e00 *)arg1);
    FUN_001dc610((igSorter *)arg1->f44);
}

void FUN_001d5e00(void *arg0, S1_1d5e00 *arg1) {
    if (*(unsigned char *)((char *)(arg0) + 236) != 0) {
        FUN_001d9ac0((struct A_1d9ac0 *)arg1->f44, *(int *)((char *)(arg0) + 228), arg1->f34);
        FUN_001d9ac0((struct A_1d9ac0 *)arg1->f44, *(int *)((char *)(arg0) + 232), arg1->f34);
    }
}

void FUN_001d5e60(struct A_1d5e60 *arg0, int arg1) {
    int n;
    int i;
    if (arg0->f28 != 0) {
        n = arg0->f28->count;
    } else {
        n = 0;
    }
    for (i = 0; i < n; i++) {
        ((Gap::Sg::igTraversal *)arg1)->dispatch((Gap::Core::igObject *)arg0->f28->data[i]);
    }
}

void FUN_001d5ef0(struct S60 *arg0, int arg1) {
    int n;
    int i;

    n = arg0->f60->count;
    for (i = 0; i < n; i++) {
        ((Gap::Sg::igTraversal *)arg1)->dispatch((Gap::Core::igObject *)arg0->f60->data[i]);
    }
}

void FUN_001d5f70(A_1d5f70 *arg0, int arg1, int *arg2, int *arg3, int *arg4) {
    int spA0[4];
    int sp90[4];
    int sp50[16];

    igMatrix44f_Copy((float *)arg4, (const float *)arg1);
    igMatrix44f_Multiply((float *)arg4, (const float *)arg4, (const float *)arg2);
    igMatrix44f_Multiply((float *)arg4, (const float *)arg4, (const float *)arg3);
    igMatrix44f_SetIdentity((float *)&sp50[0]);
    spA0[0] = 0x3F000000;
    spA0[2] = 0;
    spA0[1] = 0xBF000000;
    FUN_00190c60((float *)&sp50[0], (const float *)&spA0[0]);
    sp90[0] = 0x3F000000;
    sp90[2] = 0x3F800000;
    sp90[1] = 0x3F000000;
    igMatrix44f_SetTranslation((float *)&sp50[0], (float *)&sp90[0]);
    if (arg0->f208 != 0) {
        igMatrix44f_Multiply((float *)&sp50[0], (const float *)&sp50[0], g_projectiveShadowViewportMatrix.m);
    }
    igMatrix44f_Multiply((float *)arg4, (const float *)arg4, (const float *)&sp50[0]);
}

void FUN_001d6060(O_1d6060 *arg0, char *arg1) {
    float spF0[3];
    Mx spB0;
    Mx sp70;
    Mx sp30;
    float t;

    spF0[0] = arg0->f32 + arg0->f44;
    spF0[1] = arg0->f36 + arg0->f48;
    spF0[2] = arg0->f40 + arg0->f52;
    igMatrix44f_MakeLookAt((float *)&spB0, (const float *)&arg0->f32, spF0, (const float *)((char *)arg0 + 132));
    if (arg0->f208 != 0) {
        FUN_00191860(&sp70, arg0->f224, arg0->f220, arg0->f216, arg0->f212, arg0->f124, arg0->f128);
    } else {
        t = 0.0174532924f * (2.0f * arg0->f56);
        igMatrix44f_MakePerspective((float *)&sp70, t, t, 1.0f, arg0->f124, arg0->f128);
    }
    arg0->f88->vX(&spB0);
    arg0->f92->vX(&sp70);
    FUN_001d5f70((A_1d5f70 *)arg0, (int)arg1, (int *)&spB0, (int *)&sp70, (int *)&sp30);
    arg0->f144->vX(&sp30);
}

void FUN_001d6190(struct S_1d6190 *arg0, char *arg1) {
    struct Src_1d6190 *t;
    if (arg0->f104 == 0) {
        igProjectiveShadowShader_ConfigureSharedAttrs();
        igProjectiveShadowShader_Initialize((igProjectiveShadowShader *)arg0);
        arg0->f104 = 1;
    }
    t = arg0->src;
    if (t != 0) {
        arg0->f32 = t->f116;
        arg0->f36 = t->f120;
        arg0->f40 = t->f124;
        t = arg0->src;
        arg0->f44 = t->f128;
        arg0->f48 = t->f132;
        arg0->f52 = t->f136;
        arg0->f56 = arg0->src->f96;
    }
    FUN_001d6060((O_1d6060 *)arg0, (char *)(arg1 + 164));
    FUN_001d5c40((A0_1d5c40 *)arg0, (A1_1d5c40 *)arg1);
}

namespace Gap {
namespace Sg {

void igProjectiveShadowShader::userPostLoad()
{
    igGroup::userPostLoad();
    if (_shadowReceivers != 0) {
        int count = _shadowReceivers->getCount();
        for (int i = 0; i < count; i++)
            appendChild(_shadowReceivers->get(i));
        _shadowReceivers = 0;
    }
}

void igProjectiveShadowShader::reset()
{
    _pShadowTexRD->reset();
    _pBlurTexRD->reset();
}
}
}

namespace Gap {
namespace Sg {

void igSceneInfo::setSceneGraph(igNode *sceneGraphParam)
{
    _sceneGraph = sceneGraphParam;
}
}
}

