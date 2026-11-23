namespace Gap {
namespace Sg {

void igGroup::transform(const igMatrix44f &matrix)
{
    unsigned int count = getChildCount();
    for (unsigned int i = 0; i < count; i++) {
        _childList->get(i)->transform(matrix);
    }
}
}
}

char g_invarianceFunctionFieldResolved;

void *g_invarianceFunctionMetaField;

void FUN_001c63e0(int arg0, int arg1) {
    int (*temp_v1)(int);

    if (g_invarianceFunctionFieldResolved == 0) {
        g_invarianceFunctionMetaField = (void *)(((void *)igMetaObject_FindFieldByName(Gap::Core::igMetaField::getClassMeta(), "_invarianceFunction")));
        g_invarianceFunctionFieldResolved = 1;
    }
    temp_v1 = (int (*)(int))(*(int *)(arg0 + *(int *)((char *)(g_invarianceFunctionMetaField) + 8)));
    if (temp_v1 != 0) {
        temp_v1(arg1);
    }
}

igSmartPointer<igObject> *igSmartPointer_igStringRefList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

