namespace Gap {
namespace Sg {

igMetaObject *igModelViewMatrixBoneSelectList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igModelViewMatrixBoneSelectList::retrieveVTablePointer()
{
    igModelViewMatrixBoneSelectList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igModelViewMatrixBoneSelectList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}
}
}

static igMetaObjectCallback g_igModelViewMatrixBoneSelectListSg_callbackList[] = { Gap::Sg::igModelViewMatrixBoneSelect::arkRegister, 0 };

namespace Gap {
namespace Sg {

CallbackArray *igModelViewMatrixBoneSelectList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igModelViewMatrixBoneSelect::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igModelViewMatrixBoneSelectList",
        sizeof(igModelViewMatrixBoneSelectList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

