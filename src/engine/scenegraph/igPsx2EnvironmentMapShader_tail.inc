namespace Gap {
namespace Sg {

igMetaObject *igPsx2EnvironmentMapShader::_Meta;
igMetaField *igPsx2EnvironmentMapShader::k_envMapBlendFunc;
igMetaField *igPsx2EnvironmentMapShader::k_envMapTexGenMatrix;
igMetaField *igPsx2EnvironmentMapShader::k_multiPassEnable;

igMetaObject *igPsx2EnvironmentMapShader::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPsx2EnvironmentMapShader::retrieveVTablePointer()
{
    igPsx2EnvironmentMapShader temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

igSmartPointer<igObject> *igSmartPointer_igBlendStateAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

namespace Gap {
namespace Sg {

void igPsx2EnvironmentMapShader::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPsx2EnvironmentMapShader::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igBlendFunctionAttr::arkRegister, Gap::Attrs::igTexGenMatrixAttr::arkRegister, Gap::Attrs::igMultiPassStateAttr::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igEnvironmentMapShader2::arkRegisterInternal,
        Gap::Sg::igEnvironmentMapShader2::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPsx2EnvironmentMapShader",
        sizeof(igPsx2EnvironmentMapShader),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igPsx2EnvironmentMapShader::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_envMapBlendFunc", "_envMapTexGenMatrix", "_multiPassEnable" };
    static igMetaField **enumStorage[] = { &k_envMapBlendFunc, &k_envMapTexGenMatrix, &k_multiPassEnable };
    static int offsets[] = { 112, 116, 120 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Attrs::igBlendFunctionAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Attrs::igTexGenMatrixAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Attrs::igMultiPassStateAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_writeProxy = (void (*)())Gap::Sg::igEnvironmentMapShader2::getClassMetaSafe;
}
}
}

int FUN_001ab6c0(S_1ab6c0 *arg0, int arg1) {
    int i;
    int n;
    int *s;

    n = arg0->f20->count;
    for (i = 0; i < n; i++) {
        s = arg0->f20->data[i]->f8;
        s = s != 0 ? s : (int *)emptyString;
        if (strcmp((char *)s, (char *)arg1) == 0) {
            return i;
        }
    }
    return -1;
}

int FUN_001ab770(void *arg0, void **arg1, void **arg2) {
    int temp_v0_2;
    int temp_a0;
    void *temp_v0;
    int var_s2;
    int temp_s1;
    int var_s0;
    temp_v0 = (void *)(((void *)Gap::Sg::igAnimationBinding::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool())));
    FUN_001abb50((S_1abb50 *)temp_v0, (A *)arg1);
    temp_s1 = ((DW4VC_96_0 *)(arg1))->vX();
    var_s0 = 0;
    for (var_s2 = 0; var_s2 < temp_s1; var_s2++) {
        temp_v0_2 = FUN_001ab6c0((S_1ab6c0 *)arg0, ((DW4VC_104_1 *)(arg1))->vX((int)(var_s2)));
        if (temp_v0_2 != -1) {
            var_s0 += 1;
        }
        *(int *)(*(int *)((char *)(temp_v0) + 12) + var_s2 * 4) = temp_v0_2;
    }
    if (var_s0 != 0) {
        *(int *)((char *)(temp_v0) + 16) = var_s0;
        ((Gap::Core::igObjectList *)(*(int *)((char *)(arg0) + 16)))->append((Gap::Core::igObject *)temp_v0);
        *arg2 = temp_v0;
    } else {
        *arg2 = 0;
    }
    ((S1_1ab770 *)temp_v0)->f4 = (int)((int) (((S1_1ab770 *)temp_v0)->f4 - 1));
    if (((unsigned long long) ((long long) ((S1_1ab770 *)temp_v0)->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_v0);
    }
    return var_s0;
}

int FUN_001ab8b0(int arg0, int arg1, void **arg2) {
    void *sp4C;

    sp4C = 0;
    FUN_001ab920((const H *)arg0, arg1, (T_1ab920 * *)&sp4C);
    if (sp4C != 0) {
        *arg2 = sp4C;
        return *(int *)((char *)sp4C + 16);
    }
    return FUN_001ab770((void *)arg0, (void * *)arg1, (void * *)arg2);
}

int FUN_001ab920(const H *a, int id, T_1ab920 **out) {
    int i;
    int n = a->list->cnt;
    for (i = 0; i < n; i++) {
        T_1ab920 *t = (T_1ab920 *)a->list->arr[i];
        unsigned b = t->busy != 0u;
        if (!b && t->id == id) { *out = t; return i; }
    }
    *out = 0;
    return -1;
}

