igMetaEnum *g_igGeometrySetAttr_attrFlagsMetaEnum;
namespace Gap {
namespace Attrs {

igMetaObject *igGeometrySetAttr::_Meta;
igMetaField *igGeometrySetAttr::k_vc;
igMetaField *igGeometrySetAttr::k_renderListHandle;
igMetaField *igGeometrySetAttr::k_geometryAttrList;
igMetaField *igGeometrySetAttr::k_renderListState;
igMetaField *igGeometrySetAttr::k_drawState;
}
}

static const char *g_igGeometrySetAttr_attrFlagsNames[] = {
    "IMMEDIATE",
    "USE_RENDER_LIST",
    "USE_RENDER_LIST_DELETE_ORIGINAL",
};
static int g_igGeometrySetAttr_attrFlagsValues[] = {
    0,
    1,
    2,
};

igMetaEnum *igGeometrySetAttr_GetAttrFlagsMetaEnum(void) {
    if (g_igGeometrySetAttr_attrFlagsMetaEnum == 0) {
        g_igGeometrySetAttr_attrFlagsMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("ATTR_FLAGS", g_igGeometrySetAttr_attrFlagsNames, g_igGeometrySetAttr_attrFlagsValues, 3);
    }
    return g_igGeometrySetAttr_attrFlagsMetaEnum;
}

namespace Gap {
namespace Attrs {

igMetaObject *igGeometrySetAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igGeometrySetAttr::retrieveVTablePointer()
{
    igGeometrySetAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

void **FUN_00136e10(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

namespace Gap {
namespace Attrs {

void igGeometrySetAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igGeometrySetAttr::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gfx::igVisualContext::arkRegister, Gap::Attrs::igGeometryAttrList::arkRegister, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igGeometrySetAttr",
        sizeof(igGeometrySetAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igGeometrySetAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create, igEnumMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_vc", "_renderListHandle", "_geometryAttrList", "_renderListState", "_drawState" };
    static igMetaField **enumStorage[] = { &k_vc, &k_renderListHandle, &k_geometryAttrList, &k_renderListState, &k_drawState };
    static int offsets[] = { 12, 16, 20, 24, 28 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Gfx::igVisualContext::getClassTypeLazy();
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 1;
        metaField->_shallowCopyMethod = 1;
        metaField->_isAlikeShallowMethod = 3;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 4;
        metaField->_shallowCopyMethod = 4;
        metaField->_isAlikeShallowMethod = 3;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Attrs::igGeometryAttrList::getClassTypeLazy();
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(0);
        metaField->_persistent = 0;
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igGeometrySetAttr_GetAttrFlagsMetaEnum;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

