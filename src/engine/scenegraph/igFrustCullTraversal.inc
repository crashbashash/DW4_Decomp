igFrustCullTraversal *igFrustCullTraversal_Create(igMemoryPoolView *pool) {
    igFrustCullTraversal_EnsureRegistered();
    return (igFrustCullTraversal *)igMetaObject_CreateInstance(g_igFrustCullTraversal_metaObject, pool);
}

igMetaObject *g_igFrustCullTraversal_metaObject;
igMetaField *g_igFrustCullTraversal_compMatMetaField;
igMetaField *g_igFrustCullTraversal_curMVMatMetaField;
igMetaField *g_igFrustCullTraversal_curProjectionMatMetaField;
igMetaField *g_igFrustCullTraversal_cdMetaField;
igMetaField *g_igFrustCullTraversal_outerFrustCullScaleMetaField;
igMetaField *g_igFrustCullTraversal_outerScissorWindowScaleMetaField;
igMetaField *g_igFrustCullTraversal_boundingBoxMetaField;

igMetaObject *igFrustCullTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igFrustCullTraversal_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFrustCullTraversal_EnsureRegistered();
    return g_igFrustCullTraversal_metaObject;
}

int igFrustCullTraversal_GetVTable(void) {
    struct S_19fde0 s; char *p;
    int r;
    p = (char *)&s; FUN_001a10a0((igCommonTraversal *)p);
    s.vt = &g_igFrustCullTraversal_vtable[0];
    igSmartPointer_igAABox_Construct(&s.a);
    FUN_001510a0((int)s.b);
    FUN_001a1080((int *)(p + 548));
    r = *(int *)((char *)&s + g_objectSystem->vtableProbeOffset);
    s.vt = &g_igFrustCullTraversal_vtable[0];
    igSmartPointer_igClippingStateAttr_Destruct((void **)&s.c, -1);
    igSmartPointer_igAABox_Destruct((igSmartPointer<igObject> *)&s.a, -1);
    FUN_001a0910((Obj_19fde0 *)&s, 0);
    return r;
}

Obj_19fde0 *FUN_001a0910(Obj_19fde0 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = g_igCommonTraversal_vtable;
        arg0->rel(&arg0->m336);
        arg0->rel(&arg0->m268);
        arg0->rel(&arg0->m264);
        arg0->rel(&arg0->m260);
        arg0->rel(&arg0->m256);
        arg0->rel(&arg0->m252);
        arg0->rel(&arg0->m248);
        arg0->rel(&arg0->m244);
        arg0->rel(&arg0->m240);
        arg0->rel(&arg0->m236);
        arg0->rel(&arg0->m232);
        arg0->rel(&arg0->m96);
        arg0->rel(&arg0->m92);
        arg0->rel(&arg0->m88);
        arg0->rel(&arg0->m84);
        arg0->rel(&arg0->m80);
        arg0->rel(&arg0->m76);
        arg0->rel(&arg0->m72);
        arg0->rel(&arg0->m68);
        arg0->rel(&arg0->m64);
        arg0->rel(&arg0->m60);
        arg0->rel(&arg0->m56);
        arg0->rel(&arg0->m52);
        arg0->rel(&arg0->m36);
        arg0->rel(&arg0->m32);
        if (arg0) {
            arg0->vt = g_igTraversal_vtable;
            arg0->rel(&arg0->m28);
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void **igSmartPointer_igClippingStateAttr_Destruct(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

int *FUN_001a1080(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_igAABox_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void *FUN_001a10a0(igCommonTraversal *arg0) {
    igObject_InitHeader((igObject *)arg0);
    arg0->_vtable = (int)(&g_igTraversal_vtable[0]);
    arg0->_travProcs = 0;
    arg0->_vtable = (int)(&g_igCommonTraversal_vtable[0]);
    arg0->_capabilityManager = 0;
    arg0->_defaultManager = 0;
    arg0->_attrStack = 0;
    arg0->_transformStack = 0;
    arg0->_vc = 0;
    arg0->_flushedAttrs = 0;
    arg0->_sorter = 0;
    arg0->_matrixPool = 0;
    arg0->_timePool = 0;
    arg0->_blendMatrixPool = 0;
    arg0->_texMatPool = 0;
    arg0->_vertexBlendMatListPool = 0;
    arg0->_matrixObjectPool = 0;
    arg0->_projectionMatrixPool = 0;
    igMatrix44f_SetIdentity((float *)((char *)arg0 + 0x64));
    igMatrix44f_SetIdentity((float *)((char *)arg0 + 0xA4));
    arg0->_matrixOptimization = 0;
    arg0->_normalizeNormalsEnable = 0;
    arg0->_timeStack = 0;
    arg0->_matrixObjectList = 0;
    arg0->_boneMatrixPaletteList = 0;
    arg0->_blendMatrixPaletteList = 0;
    arg0->_blendMatrixPaletteLengths = 0;
    arg0->_segmentOverrideNames = 0;
    arg0->_segmentOverrideStacks = 0;
    arg0->_blendMatricesAttrPool = 0;
    igMatrix44f_SetIdentity((float *)((char *)arg0 + 0x110));
    arg0->_defaultTimeAttr = 0;
    igMatrix44f_SetIdentity((float *)((char *)arg0 + 0x158));
    igMatrix44f_SetIdentity((float *)((char *)arg0 + 0x198));
    return arg0;
}

void igFrustCullTraversal_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFrustCullTraversal_Register);
}

static igMetaObjectCallback g_igFrustCullTraversal_callbackList[] = { Gap::Attrs::igClippingStateAttr::arkRegister, igAABox_EnsureRegistered, 0 };

CallbackArray *igFrustCullTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFrustCullTraversal_metaObject,
        Gap::Sg::igCommonTraversal::arkRegisterInternal,
        Gap::Sg::igCommonTraversal::getClassMeta,
        igFrustCullTraversal_GetMetaObjectFunction,
        "igFrustCullTraversal",
        0x230, /* instance size */
        igFrustCullTraversal_GetVTable,
        &igFrustCullTraversal_InitFields,
        &FUN_001a13a0, /* extra callback item */
        g_igFrustCullTraversal_callbackList /* callback list */
    );
}

void igFrustCullTraversal_GetMetaObjectFunction(void) {
    igFrustCullTraversal_GetMetaObject();
}

namespace Gap {
namespace Sg {

igMetaObject *igCommonTraversal::_Meta;
igMetaField *igCommonTraversal::k_attrStack;
igMetaField *igCommonTraversal::k_transformStack;
igMetaField *igCommonTraversal::k_vc;
igMetaField *igCommonTraversal::k_capabilityManager;
igMetaField *igCommonTraversal::k_defaultManager;
igMetaField *igCommonTraversal::k_flushedAttrs;
igMetaField *igCommonTraversal::k_sorter;
igMetaField *igCommonTraversal::k_matrixPool;
igMetaField *igCommonTraversal::k_timePool;
igMetaField *igCommonTraversal::k_blendMatrixPool;
igMetaField *igCommonTraversal::k_texMatPool;
igMetaField *igCommonTraversal::k_vertexBlendMatListPool;
igMetaField *igCommonTraversal::k_matrixObjectPool;
igMetaField *igCommonTraversal::k_projectionMatrixPool;
igMetaField *igCommonTraversal::k_viewMat;
igMetaField *igCommonTraversal::k_viewMatInv;
igMetaField *igCommonTraversal::k_modeMask;
igMetaField *igCommonTraversal::k_matrixOptimization;
igMetaField *igCommonTraversal::k_normalizeNormalsEnable;
igMetaField *igCommonTraversal::k_timeStack;
igMetaField *igCommonTraversal::k_matrixObjectList;
igMetaField *igCommonTraversal::k_timeLongBuf;
igMetaField *igCommonTraversal::k_timeBuffered;
igMetaField *igCommonTraversal::k_boneMatrixPaletteList;
igMetaField *igCommonTraversal::k_blendMatrixPaletteList;
igMetaField *igCommonTraversal::k_blendMatrixPaletteLengths;
igMetaField *igCommonTraversal::k_segmentOverrideNames;
igMetaField *igCommonTraversal::k_segmentOverrideStacks;
igMetaField *igCommonTraversal::k_blendMatricesAttrPool;
igMetaField *igCommonTraversal::k_projMat;
igMetaField *igCommonTraversal::k_defaultTimeAttr;
igMetaField *igCommonTraversal::k_jointChainCount;
igMetaField *igCommonTraversal::k_jointMvmBase;
igMetaField *igCommonTraversal::k_jointMvmInverseBase;
igMetaField *igCommonTraversal::k_jointGraphRootTraversed;
igTraversalFunctionList *igCommonTraversal::travProcs;
}
}

static FieldFactory g_igFrustCullTraversal_ctorTable[] = {
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igFrustCullTraversal_fieldTable[] = {
    "_compMat",
    "_curMVMat",
    "_curProjectionMat",
    "_cd",
    "_outerFrustCullScale",
    "_outerScissorWindowScale",
    "_boundingBox",
};
static igMetaField **g_igFrustCullTraversal_fieldHandles[] = {
    &g_igFrustCullTraversal_compMatMetaField,
    &g_igFrustCullTraversal_curMVMatMetaField,
    &g_igFrustCullTraversal_curProjectionMatMetaField,
    &g_igFrustCullTraversal_cdMetaField,
    &g_igFrustCullTraversal_outerFrustCullScaleMetaField,
    &g_igFrustCullTraversal_outerScissorWindowScaleMetaField,
    &g_igFrustCullTraversal_boundingBoxMetaField,
};
static int g_igFrustCullTraversal_fieldOffsets[] = {
    476,
    540,
    544,
    548,
    552,
    556,
    472,
};

void igFrustCullTraversal_InitFields(void) {
    void *temp_s2_3;
    void *temp_s2_2;
    void *temp_s2;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_igFrustCullTraversal_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igFrustCullTraversal_ctorTable, 7);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    ((Gap::Math::igMatrix44fMetaField *)temp_s2)->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                     igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)Gap::Attrs::igClippingStateAttr::getClassTypeLazy();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4)))->setDefault(1.0f);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5)))->setDefault(2.0f);
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igAABox_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igFrustCullTraversal_fieldTable, g_igFrustCullTraversal_fieldHandles, g_igFrustCullTraversal_fieldOffsets, temp_s0);
    igMetaObject_AddExitCallback((int)&thunk_FUN_001c45d0);
}

void FUN_001a13a0(void) {
    FUN_001c45a0();
    igMetaObject_AddRegistrationCallback((int)((int *)FUN_001c4590));
}

void thunk_FUN_001c45d0(void) {
    FUN_001c45d0();
}

