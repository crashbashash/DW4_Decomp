void FUN_001d8ab0(void) {
    igShaderFactoryList_EnsureRegistered();
    igSmartPointer<igObject> info((igObject *)FUN_00198cc0((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
    ((Gap::Core::igNamedObject *)info.p)->setName("shaderInfo");
    igSmartPointer<igObject> list = igResource_GetDirectory(g_globalContext, (const char *)text_system);
    ((Gap::Core::igDirectory *)list.p)->appendInfo((Gap::Core::igInfo *)info.p);
}

void FUN_001d8b90(void) {
    igSmartPointer<igObject> list = igResource_GetDirectory(g_globalContext, (const char *)text_system);
    ((Gap::Core::igDirectory *)list.p)->removeInfo((char const *)("shaderInfo"));
}

int igShaderInfo_FindObjectReference(ShaderFieldTable *self, int arg1, ShaderFieldRecord *key) {
    igTDataList<ShaderFieldRecord *> *list = self->list;
    int idx = list->find(key);
    ShaderFieldRecord *e;
    int *name;
    if (idx == -1) {
        return 0;
    }
    e = self->list->_data[idx];
    if (e->kind == 2) {
        return 0;
    }
    name = e->name;
    name = name != 0 ? name : (int *)emptyString;
    igDirectory_AddExternalInfoRef((Gap::Core::igDirectory *)arg1, (Gap::Core::igInfo *)self, (char *)name, (Gap::Core::igObject *)key);
    return 1;
}

int Gap__Sg__igShaderInfo__vfunc_24(struct S1d *arg0, int *arg1) {
    int r = (int)((Gap::Core::igObjectList *)arg0->f20)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, (const char *)arg1);
    if (r != 0) {
        return r;
    }
    return (int)((Gap::Core::igObjectList *)arg0->f20)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, "empty");
}

