namespace Gap {
namespace Attrs {

igMetaObject *igFogAttr::_Meta;
igMetaField *igFogAttr::k_mode;
igMetaField *igFogAttr::k_nearVal;
igMetaField *igFogAttr::k_farVal;
igMetaField *igFogAttr::k_density;
igMetaField *igFogAttr::k_color;

igMetaObject *igFogAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igFogAttr::retrieveVTablePointer()
{
    igFogAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igFogAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igFogAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igFogAttr",
        sizeof(igFogAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}
}
}

int g_igFogAttr_modeDefault = 2;

namespace Gap {
namespace Attrs {

void igFogAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igEnumMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool };
    static const char *names[] = { "_mode", "_nearVal", "_farVal", "_density", "_color" };
    static igMetaField **enumStorage[] = { &k_mode, &k_nearVal, &k_farVal, &k_density, &k_color };
    static int offsets[] = { 12, 16, 20, 24, 28 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(2);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_FOG_MODE_GetMetaEnum;
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(1000.0f);
    }
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(igVec4f(0.0f, 0.0f, 0.0f, 1.0f));
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

