void *FUN_001a2ef0(int arg0) {
    Gap::Sg::igCompileTraversal::arkRegister();
    return (void *)igMetaObject_CreateInstance((igMetaObject *)Gap::Sg::igCompileTraversal::getClassMeta(), (igMemoryPoolView *)arg0);
}

namespace Gap {
namespace Sg {

igMetaObject *igCompileTraversal::_Meta;
igMetaField *igCompileTraversal::k_mvmList;
igMetaField *igCompileTraversal::k_xformInfoList;
igMetaField *igCompileTraversal::k_moList;
igMetaField *igCompileTraversal::k_containsShader;
igMetaField *igCompileTraversal::k_bound;
igMetaField *igCompileTraversal::k_transformList;
igMetaField *igCompileTraversal::k_isSkin;
igMetaField *igCompileTraversal::k_environmentShader2List;
igMetaField *igCompileTraversal::k_bmpaList;
igMetaField *igCompileTraversal::k_jointChainCount;
igMetaField *igCompileTraversal::k_jointBaseMvmIndex;
igMetaField *igCompileTraversal::k_currentBoneIndex;

igMetaObject *igCompileTraversal::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igCompileTraversal::retrieveVTablePointer()
{
    igCompileTraversal temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Sg {

void igCompileTraversal::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igCompileTraversal::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igModelViewMatrixAttrList::arkRegister, igCompiledTransformList_EnsureRegistered, igNonRefCountedMatrixObjectList_EnsureRegistered, igAABox_EnsureRegistered, igNonRefCountedTransformList_EnsureRegistered, igEnvironmentMapShader2List_EnsureRegistered, Gap::Attrs::igBlendMatrixPaletteAttrList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igCommonTraversal::arkRegisterInternal,
        Gap::Sg::igCommonTraversal::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igCompileTraversal",
        sizeof(igCompileTraversal),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        (igMetaObjectCallback)arkRegisterUser,
        regFunctions
    );
}

void igCompileTraversal::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_mvmList", "_xformInfoList", "_moList", "_containsShader", "_bound", "_transformList", "_isSkin", "_environmentShader2List", "_bmpaList", "_jointChainCount", "_jointBaseMvmIndex", "_currentBoneIndex" };
    static igMetaField **enumStorage[] = { &k_mvmList, &k_xformInfoList, &k_moList, &k_containsShader, &k_bound, &k_transformList, &k_isSkin, &k_environmentShader2List, &k_bmpaList, &k_jointChainCount, &k_jointBaseMvmIndex, &k_currentBoneIndex };
    static int offsets[] = { 472, 476, 480, 484, 488, 492, 496, 500, 504, 508, 512, 516 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 12);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Attrs::igModelViewMatrixAttrList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igCompiledTransformList_GetOrCreateMetaObject();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)igNonRefCountedMatrixObjectList_GetOrCreateMetaObject();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)igAABox_GetOrCreateMetaObject();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)igNonRefCountedTransformList_GetOrCreateMetaObject();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)igEnvironmentMapShader2List_GetOrCreateMetaObject();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)Gap::Attrs::igBlendMatrixPaletteAttrList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    igMetaObject_AddExitCallback((int)thunk_FUN_001bb230);
}

void igCompileTraversal::arkRegisterUser() {
    userRegister();
    igMetaObject_AddRegistrationCallback((int)registerClass);
}
}
}

void thunk_FUN_001bb230(void) {
    Gap::Sg::igCompileTraversal::userUnregister();
}

