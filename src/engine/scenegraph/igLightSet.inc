namespace Gap {
namespace Sg {

igMetaObject *igLightSet::_Meta;
igMetaField *igLightSet::k_lights;

igMetaObject *igLightSet::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igLightSet::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igLightSet::retrieveVTablePointer()
{
    igLightSet temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igLightSet::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igLightSet::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igLightList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igNode::arkRegisterInternal,
        Gap::Sg::igNode::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igLightSet",
        sizeof(igLightSet),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igLightSet::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_lights" };
    static igMetaField **enumStorage[] = { &k_lights };
    static int offsets[] = { 28 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Attrs::igLightList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_deepCopyMethod = 0;
        metaField->_shallowCopyMethod = 2;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

/* Retail's out-of-line copy of the inline getClassMeta, here for the registrars that name it in other units. */
igMetaObject *igTransform_GetPublishedMetaObject(void) {
    return Gap::Sg::igTransform::getClassMeta();
}

igMetaObject *g_igAnimationSequence_metaObject;

igMetaObject *igAnimationSequence_GetPublishedMetaObject(void) {
    return g_igAnimationSequence_metaObject;
}

igSmartPointer<igObject> *igSmartPointer_igAnimationTransitionDefinitionList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igAnimationTrackList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igAnimationBindingList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

