namespace Gap {
namespace Attrs {

igMetaObject *igGeometryAttr1_5::_Meta;
igMetaField *igGeometryAttr1_5::k_stripLengths;
}
}

void **FUN_001372e0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy((igObject *)p);
        }
        if (flag > 0) operator delete(self);
    }
    return (void **)self;
}

void **FUN_00137360(void **arg0, long long arg1) {
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
namespace Attrs {

igMetaObject *igGeometryAttr1_5::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igGeometryAttr1_5::retrieveVTablePointer()
{
    igGeometryAttr1_5 temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

igSmartPointer<igObject> *igSmartPointer_igVec3fList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

namespace Gap {
namespace Attrs {

void igGeometryAttr1_5::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igGeometryAttr1_5::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gfx::igPrimLengthArray::arkRegister, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igGeometryAttr::arkRegisterInternal,
        Gap::Attrs::igGeometryAttr::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igGeometryAttr1_5",
        sizeof(igGeometryAttr1_5),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igGeometryAttr1_5::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_stripLengths" };
    static igMetaField **enumStorage[] = { &k_stripLengths };
    static int offsets[] = { 48 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Gfx::igPrimLengthArray::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

