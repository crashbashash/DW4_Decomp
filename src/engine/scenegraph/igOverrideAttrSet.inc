namespace Gap {
namespace Sg {

igMetaObject *igOverrideAttrSet::_Meta;
}
}

igMetaObject *igOverrideAttrSet_GetOrCreateMetaObject(void) {
    if (Gap::Sg::igOverrideAttrSet::getClassMeta() == 0) {
        g_igOverrideAttrSet_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return Gap::Sg::igOverrideAttrSet::getClassMeta();
}

namespace Gap {
namespace Sg {

igMetaObject *igOverrideAttrSet::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igOverrideAttrSet::retrieveVTablePointer()
{
    igOverrideAttrSet temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igOverrideAttrSet::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igOverrideAttrSet::arkRegisterInternal()
{
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igAttrSet::arkRegisterInternal,
        Gap::Sg::igAttrSet::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igOverrideAttrSet",
        sizeof(igOverrideAttrSet),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

igSmartPointer<igObject> *igSmartPointer_igMetaObject_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

