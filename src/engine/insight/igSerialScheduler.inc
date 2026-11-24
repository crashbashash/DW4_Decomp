namespace Gap {
namespace Insight {

igMetaObject *igSerialScheduler::_Meta;
igMetaField *igSerialScheduler::k_managerList;
igMetaField *igSerialScheduler::k_cachedManagerList;

igMetaObject *igSerialScheduler::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igSerialScheduler::retrieveVTablePointer()
{
    igSerialScheduler temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

void **igSmartPointer_igInfoManagerOrderedList_Destruct(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
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
namespace Insight {

void igSerialScheduler::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igSerialScheduler::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Insight::igInfoManagerOrderedList::arkRegister, Gap::Insight::igInfoManagerList::arkRegister, 0 };

    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Insight::igInsightScheduler::arkRegisterInternal,
        Gap::Insight::igInsightScheduler::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igSerialScheduler",
        sizeof(igSerialScheduler),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igSerialScheduler::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_managerList", "_cachedManagerList" };
    static igMetaField **enumStorage[] = { &k_managerList, &k_cachedManagerList };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Insight::igInfoManagerOrderedList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Insight::igInfoManagerList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

