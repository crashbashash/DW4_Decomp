namespace Gap {
namespace Attrs {

igMetaObject *igAlphaFunctionAttr::_Meta;
igMetaField *igAlphaFunctionAttr::k_func;
igMetaField *igAlphaFunctionAttr::k_refValue;

igAlphaFunctionAttr *igAlphaFunctionAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igAlphaFunctionAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igAlphaFunctionAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAlphaFunctionAttr::retrieveVTablePointer()
{
    igAlphaFunctionAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igAlphaFunctionAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAlphaFunctionAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAlphaFunctionAttr",
        sizeof(igAlphaFunctionAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}
}
}

int g_igAlphaFunctionAttr_funcDefault = 6;

namespace Gap {
namespace Attrs {

void igAlphaFunctionAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igEnumMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool };
    static const char *names[] = { "_func", "_refValue" };
    static igMetaField **enumStorage[] = { &k_func, &k_refValue };
    static int offsets[] = { 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(6);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_ALPHA_FUNCTION_GetMetaEnum;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}

void igAlphaFunctionAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetAlphaFunc((igPsx2VisualContext *)vc, getAlphaFunc());
    igPsx2VisualContext_SetAlphaRefValue((igPsx2VisualContext *)vc, getRefValue());
}

void igAlphaFunctionAttr::synchronizeDefault(igVisualContext *vc)
{
    setAlphaFunc(((igVisualContextDispatchView *)vc)->getAlphaFunc());
    setRefValue(((igVisualContextDispatchView *)vc)->getAlphaRefValue());
}

/* Setter: stores the alpha-test reference value (`_refValue`, an igFloatMetaField of the reflected
 * igAlphaFunctionAttr). */
void igAlphaFunctionAttr::setRefValue(float val)
{
    _refValue = val;
}

/* Setter for the alpha-test comparison function (`_func`, +12); `_refValue` at +16 is the
 * reference it compares to. */

void igAlphaFunctionAttr::setAlphaFunc(IG_GFX_ALPHA_FUNCTION afunc)
{
    _func = afunc;
}
}
}

