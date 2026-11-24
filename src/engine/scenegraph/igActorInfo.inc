namespace Gap {
namespace Sg {

igMetaObject *igActorInfo::_Meta;
igMetaField *igActorInfo::k_actor;
igMetaField *igActorInfo::k_actorList;
igMetaField *igActorInfo::k_animationDatabase;
igMetaField *igActorInfo::k_combinerList;
igMetaField *igActorInfo::k_appearanceList;

igMetaObject *igActorInfo::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igActorInfo::retrieveVTablePointer()
{
    igActorInfo temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igActorInfo::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igActorInfo::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igActor::arkRegister, Gap::Sg::igActorList::arkRegister, Gap::Sg::igAnimationDatabase::arkRegister, Gap::Sg::igAnimationCombinerList::arkRegister, Gap::Sg::igAppearanceList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igInfo::arkRegisterInternal,
        Gap::Core::igInfo::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igActorInfo",
        sizeof(igActorInfo),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igActorInfo::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_actor", "_actorList", "_animationDatabase", "_combinerList", "_appearanceList" };
    static igMetaField **enumStorage[] = { &k_actor, &k_actorList, &k_animationDatabase, &k_combinerList, &k_appearanceList };
    static int offsets[] = { 20, 24, 28, 32, 36 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igActor::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Sg::igActorList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Sg::igAnimationDatabase::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Sg::igAnimationCombinerList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Sg::igAppearanceList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

