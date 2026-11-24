namespace Gap {
namespace Sg {

igMetaObject *igActor::_Meta;
igMetaField *igActor::k_animationSystem;
igMetaField *igActor::k_boneMatrixCacheArray;
igMetaField *igActor::k_blendMatrixCacheArray;
igMetaField *igActor::k_appearance;
igMetaField *igActor::k_animationDatabase;
igMetaField *igActor::k_modifierList;
igMetaField *igActor::k_transform;
igMetaField *igActor::k_forceActorCacheUse;
igMetaField *igActor::k_actorCacheUsed;
igMetaField *igActor::k_mvmWhenTraversed;
igMetaField *igActor::k_inverseViewWhenTraversed;
igMetaField *igActor::k_update;
igMetaField *igActor::k_render;

igMetaObject *igActor::getClassTypeLazy()
{
    if (_Meta == 0) {
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return _Meta;
}

igMetaObject *igActor::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igActor::retrieveVTablePointer()
{
    igActor temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igActor::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igActor::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igAnimationSystem::arkRegister, Gap::Sg::igAppearance::arkRegister, Gap::Sg::igAnimationDatabase::arkRegister, Gap::Sg::igAnimationModifierList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igActor",
        sizeof(igActor),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igActor::arkRegisterInitialize() {
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igMemoryRefMetaField_Create, igMemoryRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, igBoolMetaField_Create, igBoolMetaField_Create, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, igBoolMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_animationSystem", "_boneMatrixCacheArray", "_blendMatrixCacheArray", "_appearance", "_animationDatabase", "_modifierList", "_transform", "_forceActorCacheUse", "_actorCacheUsed", "_mvmWhenTraversed", "_inverseViewWhenTraversed", "_update", "_render" };
    static igMetaField **enumStorage[] = { &k_animationSystem, &k_boneMatrixCacheArray, &k_blendMatrixCacheArray, &k_appearance, &k_animationDatabase, &k_modifierList, &k_transform, &k_forceActorCacheUse, &k_actorCacheUsed, &k_mvmWhenTraversed, &k_inverseViewWhenTraversed, &k_update, &k_render };
    static int offsets[] = { 32, 36, 40, 44, 48, 52, 56, 120, 121, 124, 188, 252, 253 };
    int temp_s1;
    void *temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_v0;
    void *temp_v0_2;

    temp_s0 = (void *)_Meta;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, instFuncs, 0xD);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)));
    ((::igObjectRefMetaField *)temp_s2)->_metaObject = (int)Gap::Sg::igAnimationSystem::getClassTypeLazy();
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)));
    ((::igMemoryRefMetaField *)temp_s2_2)->_memType = (int)Gap::Math::igMatrix44fMetaField::getMetaField();
    ((::igRefMetaField *)temp_s2_2)->_destruct = 1;
    ((::igMemoryRefMetaField *)temp_s2_2)->_releaseOnCopy = 1;
    ((::igMemoryRefMetaField *)temp_s2_2)->_releaseOnReset = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)));
    ((::igMemoryRefMetaField *)temp_s2_3)->_memType = (int)Gap::Math::igMatrix44fMetaField::getMetaField();
    ((::igRefMetaField *)temp_s2_3)->_destruct = 1;
    ((::igMemoryRefMetaField *)temp_s2_3)->_releaseOnCopy = 1;
    ((::igMemoryRefMetaField *)temp_s2_3)->_releaseOnReset = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3)));
    ((::igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)Gap::Sg::igAppearance::getClassTypeLazy();
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4)));
    ((::igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)Gap::Sg::igAnimationDatabase::getClassTypeLazy();
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5)));
    ((::igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)Gap::Sg::igAnimationModifierList::getClassTypeLazy();
    ((::igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6)));
    ((Gap::Math::igMatrix44fMetaField *)temp_s2_7)->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                       igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    ((::igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7)))->_persistent = 0;
    ((::igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8)))->_persistent = 0;
    temp_s2_8 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9)));
    ((Gap::Math::igMatrix44fMetaField *)temp_s2_8)->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                       igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    ((::igMetaField *)temp_s2_8)->_persistent = 0;
    temp_s2_9 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA)));
    ((Gap::Math::igMatrix44fMetaField *)temp_s2_9)->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                       igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    ((::igMetaField *)temp_s2_9)->_persistent = 0;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xB)));
    ((Gap::Core::igBoolMetaField *)temp_v0)->setDefault(1);
    ((::igMetaField *)temp_v0)->_persistent = 0;
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xC)));
    ((Gap::Core::igBoolMetaField *)temp_v0_2)->setDefault(1);
    ((::igMetaField *)temp_v0_2)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, names, enumStorage, offsets, temp_s1);
}
}
}

