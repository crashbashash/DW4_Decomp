namespace Gap {
namespace Sg {

igMetaObject *igTransformSequence1_5::_Meta;
igMetaField *igTransformSequence1_5::k_timeListLong;
igMetaField *igTransformSequence1_5::k_timeList;
igMetaField *igTransformSequence1_5::k_interpolationDataTranslation;
igMetaField *igTransformSequence1_5::k_interpolationDataRotation;
igMetaField *igTransformSequence1_5::k_interpolationDataScale;
igMetaField *igTransformSequence1_5::k_drivenChannels;
igMetaField *igTransformSequence1_5::k_interpolationMethod;
igMetaField *igTransformSequence1_5::k_keyframeTimeOffset;
igMetaField *igTransformSequence1_5::k_animationDuration;
igMetaField *igTransformSequence1_5::k_compressedDataObject;

igMetaObject *igTransformSequence1_5::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTransformSequence1_5::retrieveVTablePointer()
{
    igTransformSequence1_5 temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Sg {

void igTransformSequence1_5::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTransformSequence1_5::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igLongList::arkRegister, igVec3fList_EnsureRegistered, Gap::Sg::igCompressedTransformSequence1_5Data::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igTransformSequence::arkRegisterInternal,
        Gap::Sg::igTransformSequence::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTransformSequence1_5",
        sizeof(igTransformSequence1_5),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        thunk_FUN_001ddfd0,
        regFunctions
    );
}
}
}

