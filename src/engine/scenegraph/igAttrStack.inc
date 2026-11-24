namespace Gap {
namespace Sg {

igAttrStack *igAttrStack::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igAttrStack *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igAttrStack::_Meta;
igMetaField *igAttrStack::k_default;
igMetaField *igAttrStack::k_cachedOverride;
igMetaField *igAttrStack::k_popProc;
igMetaField *igAttrStack::k_hasChangedFromLastIncrementalFlush;
igMetaField *igAttrStack::k_lastIncrementalFlushedAttr;
igMetaField *igAttrStack::k_hasChangedFromRoot;
igMetaField *igAttrStack::k_lastFlushedAttr;
igMetaField *igAttrStack::k_cachedRenderPackage;

igMetaObject *igAttrStack::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAttrStack::retrieveVTablePointer()
{
    igAttrStack temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igAttrStack::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAttrStack::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igAttr::arkRegister, Gap::Attrs::igAttr::arkRegister, Gap::Sg::igRenderPackage::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNonRefCountedObjectStack::arkRegisterInternal,
        Gap::Core::igNonRefCountedObjectStack::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAttrStack",
        sizeof(igAttrStack),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igAttrStack::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igRawRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_default", "_cachedOverride", "_popProc", "_hasChangedFromLastIncrementalFlush", "_lastIncrementalFlushedAttr", "_hasChangedFromRoot", "_lastFlushedAttr", "_cachedRenderPackage" };
    static igMetaField **enumStorage[] = { &k_default, &k_cachedOverride, &k_popProc, &k_hasChangedFromLastIncrementalFlush, &k_lastIncrementalFlushedAttr, &k_hasChangedFromRoot, &k_lastFlushedAttr, &k_cachedRenderPackage };
    static int offsets[] = { 20, 24, 28, 32, 36, 40, 44, 48 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 8);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Attrs::igAttr::getClassTypeLazy();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(-1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Attrs::igAttr::getClassTypeLazy();
        metaField->_refCounted = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)Gap::Attrs::igAttr::getClassTypeLazy();
        metaField->_refCounted = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)Gap::Sg::igRenderPackage::getClassTypeLazy();
        metaField->_refCounted = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

