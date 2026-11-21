void igDataPump_SetDestByFieldName(igDataPump *self, igObjectDispatchView **destObj, const char *destName) {
    igObject *object;
    igObject *old;
    igMetaField *fld;
    int name;
    int v;
    int newv;
    int oldv;
    object = (igObject *)*destObj;
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
    old = (igObject *)self->_destObj;
    if (old != 0) {
        --old->_refCount;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(old);
        }
    }
    self->_destObj = (int)object;
    fld = (igMetaField *)igMetaObject_FindFieldByName((*destObj)->GetMeta(), destName);
    if (fld != 0) {
        fld->_refCount = fld->_refCount + 1;
    }
    old = (igObject *)self->_destMeta;
    if (old != 0) {
        --old->_refCount;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(old);
        }
    }
    self->_destMeta = (int)fld;
    name = ((igMetaObject *)((igMetaField *)self->_destMeta)->_parentMetaObject)->_name;
    if (g_stringPool == 0) {
        v = (int)(StringPool_Allocate(16));
        if (v != 0) {
            v = (int)(StringPool_Construct((StringPool *)v));
        }
        g_stringPool = (StringPool *)v;
    }
    newv = (int)(StringPool_Intern(g_stringPool, (const char *)name));
    oldv = self->_destMetaClassName;
    if (oldv != 0) {
        int *a1 = (int *)oldv - 2;
        int v0 = ((int *)oldv)[-1] - 1;
        ((int *)oldv)[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*a1), (StringTokenHeader *)a1);
        }
    }
    self->_destMetaClassName = newv;
    name = ((igMetaField *)self->_destMeta)->_fieldName;
    if (g_stringPool == 0) {
        v = (int)(StringPool_Allocate(16));
        if (v != 0) {
            v = (int)(StringPool_Construct((StringPool *)v));
        }
        g_stringPool = (StringPool *)v;
    }
    newv = (int)(StringPool_Intern(g_stringPool, (const char *)name));
    oldv = self->_destMetaFieldName;
    if (oldv != 0) {
        int *a1 = (int *)oldv - 2;
        int v0 = ((int *)oldv)[-1] - 1;
        ((int *)oldv)[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*a1), (StringTokenHeader *)a1);
        }
    }
    self->_destMetaFieldName = newv;
}

void igDataPump_SetDataPumpInterface(igDataPump *self, igObject **dpi) {
    igObject *old;
    igObject *interface;
    interface = *dpi;
    if (interface != 0) {
        interface->_refCount = (int)((int) (interface->_refCount + 1));
    }
    old = (igObject *)self->_dpi;
    if (old != 0) {
        old->_refCount = (int)((int) (old->_refCount - 1));
        if (((unsigned long long) ((long long) (int) old->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(old);
        }
    }
    self->_dpi = (int)interface;
}

int igDataPump_Update(ValueBinding *binding, long long time) {
    igSmartPointer<Value> value(binding->source->value(), kRetainReference);
    int sinkType = binding->sink->type();
    if (((igMetaObject_IsOfType((igMetaObject *)(value->type()), (igMetaObject *)sinkType) != 0) ^ 1) != 0) {
        return 0;
    }
    binding->source->select(time);
    binding->sink->write(binding->key, (int)binding->source + value->offset);
    static FieldDesc *invarianceFunctionField;
    if (invarianceFunctionField == 0) {
        invarianceFunctionField = (FieldDesc *)igMetaObject_FindFieldByName(Gap::Core::igMetaField::getClassMeta(), "_invarianceFunction");
    }
    Notify notify = *(Notify *)((char *)binding->sink + invarianceFunctionField->offset);
    if (notify != 0) {
        notify(binding->key);
    }
    return 1;
}

void igDataPump_UserPostLoad(igDataPump *pump) {
    igSmartPointer<igObject> meta;
    meta = (igObject *)igObjectSystem_FindMetaByNameDefault((const char *)pump->_destMetaClassName);
    if (meta.get() != 0) {
        igObject *field = igMetaObject_FindFieldByName((igMetaObject *)(meta.get()), (const char *)pump->_destMetaFieldName);
        igObject *old;
        if (field != 0) {
            field->_refCount = field->_refCount + 1;
        }
        old = (igObject *)pump->_destMeta;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        pump->_destMeta = (int)field;
    }
}

void igDataPump_UserPreWrite(void) {

}

igDataPumpList *igDataPumpInfo_GetList(igDataPumpInfo *self)
{
    return (igDataPumpList *)self->_dataPumpList;
}

int igDataPumpInfo_Append(igDataPumpInfo *self, igObject *pump) {
    ((Gap::Core::igObjectList *)self->_dataPumpList)->append((Gap::Core::igObject *)pump);
    return 1;
}

int igDataPumpManager_Update(igDataPumpManager *self, long long time) {
    int i;
    int n;

    n = ((igDataPumpList *)self->_dataPumpList)->_count;
    for (i = 0; i < n; i++) {
        igDataPump_Update(((ValueBinding **)((igDataPumpList *)self->_dataPumpList)->_data)[i], time);
    }
    return 1;
}

int igDataPumpManager_AppendList(igDataPumpManager *self, igDataPumpList *list) {
    int i;
    int n;

    n = list->_count;
    for (i = 0; i < n; i++) {
        ((Gap::Core::igObjectList *)self->_dataPumpList)->append((Gap::Core::igObject *)(((igObject **)list->_data)[i]));
    }
    return 1;
}

int igDataPumpManager_AppendInfo(igDataPumpManager *self, igDataPumpInfo *info) {
    igDataPumpManager_AppendList(self, igDataPumpInfo_GetList(info));
    return 1;
}

typedef float igMatrixStackEntry[16];

static inline int matrixCount(const igMatrixStack *stack) { return stack->_count; }

int igMatrixStack_PushPreMultiply(igMatrixStack *self, const float *matrix) {
    int index;
    int count;
    igMatrixStackEntry *matrices;

    index = self->_count;
    if (index == 0) {
        if (index < self->_capacity) {
            self->_count = matrixCount(self) + 1;
        } else {
            ((Gap::Core::igDataList *)self)->resizeAndSetCount(index + 1, 0x40);
        }
        igMatrix44f_Copy(((igMatrixStackEntry *)self->_data)[index], matrix);
    } else {
        count = matrixCount(self);
        if (count == 0) {
            index = 0;
        } else {
            if (index < self->_capacity) {
                self->_count = count + 1;
            } else {
                ((Gap::Core::igDataList *)self)->resizeAndSetCount(index + 1, 0x40);
            }
            matrices = (igMatrixStackEntry *)self->_data;
            igMatrix44f_Copy(matrices[index], matrices[index - 1]);
        }
        igMatrix44f_PreMultiply(((igMatrixStackEntry *)self->_data)[self->_count - 1], matrix);
    }
    return index;
}

int igMatrixStack_PushPostMultiply(igMatrixStack *self, const float *matrix) {
    float *top;
    igMatrixStackEntry *matrices;
    int count;
    int index;

    index = matrixCount(self);
    if (index == 0) {
        if (index < self->_capacity) {
            self->_count = self->_count + 1;
        } else {
            ((Gap::Core::igDataList *)self)->resizeAndSetCount(index + 1, 0x40);
        }
        igMatrix44f_Copy(((igMatrixStackEntry *)self->_data)[index], matrix);
    } else {
        count = self->_count;
        if (count == 0) {
            index = 0;
        } else {
            if (index < self->_capacity) {
                self->_count = count + 1;
            } else {
                ((Gap::Core::igDataList *)self)->resizeAndSetCount(index + 1, 0x40);
            }
            matrices = (igMatrixStackEntry *)self->_data;
            igMatrix44f_Copy(matrices[index], matrices[index - 1]);
        }
        top = ((igMatrixStackEntry *)self->_data)[self->_count - 1];
        igMatrix44f_Multiply(top, top, matrix);
    }
    return index;
}

void igMatrixStack_PreMultiply(igMatrixStack *self, const float *matrix) {
    igMatrix44f_PreMultiply(((igMatrixStackEntry *)self->_data)[self->_count - 1], matrix);
}

void igMatrixStack_PostMultiply(igMatrixStack *self, const float *matrix) {
    float *top;
    top = ((igMatrixStackEntry *)self->_data)[self->_count - 1];
    igMatrix44f_Multiply(top, top, matrix);
}

