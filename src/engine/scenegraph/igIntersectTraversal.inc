namespace Gap {
namespace Sg {

igMetaObject *igIntersectTraversal::_Meta;
igMetaField *igIntersectTraversal::k_matStack;
igMetaField *igIntersectTraversal::k_nodeStack;
igMetaField *igIntersectTraversal::k_probe;
igMetaField *igIntersectTraversal::k_mode;
igMetaField *igIntersectTraversal::k_hitProc;
igMetaField *igIntersectTraversal::k_volumes;
igMetaField *igIntersectTraversal::k_ray;
igTraversalFunctionList *igIntersectTraversal::travProcs;

igMetaObject *igIntersectTraversal::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igIntersectTraversal::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igIntersectTraversal::retrieveVTablePointer()
{
    igIntersectTraversal temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

igIntersectTraversal *igIntersectTraversal_Destroy(igIntersectTraversal *self, short deleteFlag) {
    if (self) {
        self->_vtable = (int)&g_igIntersectTraversal_vtable[0];
        if (&self->_ray) {
            S1 *t = (S1 *)self->_ray;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        }
        if (&self->_volumes) {
            S1 *t = (S1 *)self->_volumes;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        }
        if (&self->_probe) {
            S1 *t = (S1 *)self->_probe;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        }
        if (&self->_nodeStack) {
            S1 *t = (S1 *)self->_nodeStack;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        }
        if (&self->_matStack) {
            S1 *t = (S1 *)self->_matStack;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        }
        if (self) {
            self->_vtable = (int)&g_igTraversal_vtable[0];
            if (&self->_travProcs) {
                S1 *t = (S1 *)self->_travProcs;
                if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
            }
        }
        if (deleteFlag > 0) Memory_FreeBufferAliasC(self);
    }
    return self;
}

namespace Gap {
namespace Sg {

void igIntersectTraversal::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igIntersectTraversal::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igMatrixStack_EnsureRegistered, Gap::Sg::igNodeList::arkRegister, Gap::Sg::igProbe::arkRegister, igVolumeList_EnsureRegistered, igRay_EnsureRegistered, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igTraversal::arkRegisterInternal,
        Gap::Sg::igTraversal::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igIntersectTraversal",
        sizeof(igIntersectTraversal),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        (igMetaObjectCallback)arkRegisterUser,
        regFunctions
    );
}

void igIntersectTraversal::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igRawRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_matStack", "_nodeStack", "_probe", "_mode", "_hitProc", "_volumes", "_ray" };
    static igMetaField **enumStorage[] = { &k_matStack, &k_nodeStack, &k_probe, &k_mode, &k_hitProc, &k_volumes, &k_ray };
    static int offsets[] = { 32, 36, 40, 44, 48, 52, 56 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igMatrixStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Sg::igNodeList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Sg::igProbe::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(5);
    }
    {
        igRawRefMetaField *metaField = (igRawRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)igVolumeList_GetOrCreateMetaObject();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)igRay_GetOrCreateMetaObject();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    igMetaObject_AddExitCallback((int)thunk_igIntersectTraversal_UserUnregister);
}

void igIntersectTraversal::arkRegisterUser() {
    userRegister();
    igMetaObject_AddRegistrationCallback((int)registerClass);
}
}
}

void thunk_igIntersectTraversal_UserUnregister(void) {
    Gap::Sg::igIntersectTraversal::userUnregister();
}

