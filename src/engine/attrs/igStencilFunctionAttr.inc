namespace Gap {
namespace Attrs {

igMetaObject *igStencilFunctionAttr::_Meta;
igMetaField *igStencilFunctionAttr::k_refVal;
igMetaField *igStencilFunctionAttr::k_func;
igMetaField *igStencilFunctionAttr::k_writeMask;
igMetaField *igStencilFunctionAttr::k_readMask;
igMetaField *igStencilFunctionAttr::k_stenFailOp;
igMetaField *igStencilFunctionAttr::k_stenPassZPassOp;
igMetaField *igStencilFunctionAttr::k_stenPassZFailOp;

igStencilFunctionAttr *igStencilFunctionAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igStencilFunctionAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igStencilFunctionAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igStencilFunctionAttr::retrieveVTablePointer()
{
    igStencilFunctionAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igStencilFunctionAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igStencilFunctionAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igStencilFunctionAttr",
        sizeof(igStencilFunctionAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}
}
}

int g_igStencilFunctionAttr_funcDefault = 7;

namespace Gap {
namespace Attrs {

void igStencilFunctionAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igUnsignedIntMetaField_Create, igEnumMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create };
    static const char *names[] = { "_refVal", "_func", "_writeMask", "_readMask", "_stenFailOp", "_stenPassZPassOp", "_stenPassZFailOp" };
    static igMetaField **enumStorage[] = { &k_refVal, &k_func, &k_writeMask, &k_readMask, &k_stenFailOp, &k_stenPassZPassOp, &k_stenPassZFailOp };
    static int offsets[] = { 12, 16, 20, 24, 28, 32, 36 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(7);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_STENCIL_FUNCTION_GetMetaEnum;
    }
    {
        igUnsignedIntMetaField *metaField = (igUnsignedIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(-1);
    }
    {
        igUnsignedIntMetaField *metaField = (igUnsignedIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(-1);
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_STENCIL_OPERATION_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_STENCIL_OPERATION_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_STENCIL_OPERATION_GetMetaEnum;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

igSmartPointer<igObject> *igSmartPointer_igVertexArray_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

