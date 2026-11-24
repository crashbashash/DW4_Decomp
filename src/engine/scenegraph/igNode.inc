namespace Gap {
namespace Sg {

unsigned int igNode::flagMask = 3;

igMetaObject *igNode::_Meta;
igMetaField *igNode::k_bound;
igMetaField *igNode::k_parentList;
igMetaField *igNode::k_flags;
igMetaField *igNode::k_handle;

igMetaObject *igNode::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igNode::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igNode::retrieveVTablePointer()
{
    igNode temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igNode::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igNode::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igVolume_EnsureRegistered, Gap::Sg::igNonRefCountedNodeList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igNode",
        sizeof(igNode),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igNode::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_bound", "_parentList", "_flags", "_handle" };
    static igMetaField **enumStorage[] = { &k_bound, &k_parentList, &k_flags, &k_handle };
    static int offsets[] = { 12, 16, 20, 24 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igVolume_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Sg::igNonRefCountedNodeList::getClassTypeLazy();
        metaField->_resetMethod = 3;
        metaField->_construct = 1;
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 4;
        metaField->_shallowCopyMethod = 4;
        metaField->_constructCopyMethod = 4;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

namespace Gap {
namespace Sg {

igMetaObject *igGeometry::_Meta;
igMetaField *igGeometry::k_trigger;
igMetaField *igGeometry::k_renderList;
}
}

/* Retail's out-of-line getClassMeta, named by address only from the game's ParticleTimer registration: it stays the
 * C function it was (as igInfo's getMeta copy), since no unit that takes the inline's address emits it here. */
igMetaObject *igGeometry_GetPublishedMetaObject(void) {
    return Gap::Sg::igGeometry::getClassMeta();
}

int *igSmartPointer_igFloatList_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

igSmartPointer<igObject> *igSmartPointer_igIntListList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

namespace Gap {
namespace Sg {

igMetaObject *igModelViewMatrixBoneSelectList::_Meta;

igMetaObject *igModelViewMatrixBoneSelectList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}
}
}

