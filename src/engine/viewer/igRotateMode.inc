static const char *g_igRotateMode_CONSTRAINT_AXISNames[] = {
    "NONE", "CONSTRAINT_X", "CONSTRAINT_Y",
};
static int g_igRotateMode_CONSTRAINT_AXISValues[] = {
    0, 1, 2,
};
igMetaEnum *g_igRotateMode_CONSTRAINT_AXISMetaEnum;
namespace Gap {
namespace Viewer {

igMetaObject *igRotateMode::_Meta;
igMetaField *igRotateMode::k_distance;
igMetaField *igRotateMode::k_lastMousePos;
igMetaField *igRotateMode::k_leftMouseActive;
igMetaField *igRotateMode::k_middleMouseActive;
igMetaField *igRotateMode::k_rightMouseActive;
igMetaField *igRotateMode::k_joystickT;
igMetaField *igRotateMode::k_joystickR;
igMetaField *igRotateMode::k_constraint;
igMetaField *igRotateMode::k_constraintAxis;
igMetaField *igRotateMode::k_active;
igMetaField *igRotateMode::k_maya;
igMetaField *igRotateMode::k_head;
igMetaField *igRotateMode::k_roll;
igMetaField *igRotateMode::k_pitch;
igMetaField *igRotateMode::k_zoom;
igMetaField *igRotateMode::k_translation;
}
}

igMetaEnum *FUN_0045c540(void) {
    if (g_igRotateMode_CONSTRAINT_AXISMetaEnum == 0) {
        g_igRotateMode_CONSTRAINT_AXISMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("CONSTRAINT_AXIS", g_igRotateMode_CONSTRAINT_AXISNames, g_igRotateMode_CONSTRAINT_AXISValues, 3);
    }
    return g_igRotateMode_CONSTRAINT_AXISMetaEnum;
}

namespace Gap {
namespace Viewer {

igRotateMode *igRotateMode::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igRotateMode *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igRotateMode::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igRotateMode::retrieveVTablePointer()
{
    igRotateMode temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igRotateMode::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igRotateMode::arkRegisterInternal()
{
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Viewer::igViewMode::arkRegisterInternal,
        Gap::Viewer::igViewMode::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igRotateMode",
        sizeof(igRotateMode),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igRotateMode::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool, igBoolMetaField_Create, igEnumMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool };
    static const char *names[] = { "_distance", "_lastMousePos", "_leftMouseActive", "_middleMouseActive", "_rightMouseActive", "_joystickT", "_joystickR", "_constraint", "_constraintAxis", "_active", "_maya", "_head", "_roll", "_pitch", "_zoom", "_translation" };
    static igMetaField **enumStorage[] = { &k_distance, &k_lastMousePos, &k_leftMouseActive, &k_middleMouseActive, &k_rightMouseActive, &k_joystickT, &k_joystickR, &k_constraint, &k_constraintAxis, &k_active, &k_maya, &k_head, &k_roll, &k_pitch, &k_zoom, &k_translation };
    static int offsets[] = { 76, 80, 88, 89, 90, 92, 100, 108, 112, 116, 117, 120, 124, 128, 132, 136 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 16);
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(1.0f);
    }
    {
        igVec2fMetaField *metaField = (igVec2fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(igVec2f(0.0f, 0.0f));
    }
    {
        igVec2fMetaField *metaField = (igVec2fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(igVec2f(0.0f, 0.0f));
    }
    {
        igVec2fMetaField *metaField = (igVec2fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(igVec2f(0.0f, 0.0f));
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())FUN_0045c540;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->setDefault(1);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->setDefault(0.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->setDefault(0.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->setDefault(0.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 14);
        metaField->setDefault(1.0f);
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 15);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 0.0f));
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

