namespace Gap {
namespace Insight {

igMetaObject *igMessageFilter::_Meta;
igMetaField *igMessageFilter::k_msgType;
igMetaField *igMessageFilter::k_receivers;

igMessageFilter *igMessageFilter::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igMessageFilter *)igMetaObject_CreateInstance(_Meta, pool);
}

/* The kit defines this in the class body; igMessage is declared after igMessageFilter in reflected.h, whose
 * inline bodies need it complete, so it is defined here (retail's copy is this unit's). */
int igMessageFilter::acceptMessage(igMessage *msg)
{
    return msg->isOfType(_msgType);
}

igMetaObject *igMessageFilter::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMessageFilter::retrieveVTablePointer()
{
    igMessageFilter temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMessageFilter::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMessageFilter::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igMetaObject_EnsureRegistered, Gap::Insight::igMessageReceiverList::arkRegister, 0 };

    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMessageFilter",
        sizeof(igMessageFilter),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igMessageFilter::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_msgType", "_receivers" };
    static igMetaField **enumStorage[] = { &k_msgType, &k_receivers };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Insight::igMessageReceiverList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

