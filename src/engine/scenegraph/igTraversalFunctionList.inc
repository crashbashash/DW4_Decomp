namespace Gap {
namespace Sg {

igTraversalFunctionList *igTraversalFunctionList::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igTraversalFunctionList *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igTraversalFunctionList::_Meta;

igMetaObject *igTraversalFunctionList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTraversalFunctionList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTraversalFunctionList::retrieveVTablePointer()
{
    igTraversalFunctionList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTraversalFunctionList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTraversalFunctionList::arkRegisterInternal()
{
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTraversalFunctionList",
        sizeof(igTraversalFunctionList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

igSmartPointer<igObject> *igSmartPointer_igProjectionMatrixAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igSetRenderDestinationAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igCopyRenderDestinationAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igTextureBindAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igTexGenMatrixAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igColorAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igViewportAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

int *igSmartPointer_igColorAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igTexGenMatrixAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igLightAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igViewportAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igCopyRenderDestinationAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igTextureBindAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igTextureAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igSetRenderDestinationAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igRenderDestinationAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igTextureMatrixAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igProjectionMatrixAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igModelViewMatrixAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igNodeList_Construct(int *p)
{
    *p = 0;
    return p;
}

int FUN_0019ace0(int a0)
{
    return a0;
}

void *FUN_0019acf0(igGroup *arg0) {
    igObject_InitHeader((igObject *)arg0);
    arg0->_vtable = (int)(&g_igNamedObject_vtable[0]);
    arg0->_name = 0;
    arg0->_vtable = (int)(&g_igNode_vtable[0]);
    arg0->_bound = 0;
    arg0->_parentList = 0;
    arg0->_vtable = (int)(&g_igGroup_vtable[0]);
    arg0->_childList = 0;
    return arg0;
}

