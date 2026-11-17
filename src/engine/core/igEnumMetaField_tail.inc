int igEnumMetaField_ValueFromString(igEnumMetaField *self, int *value, int text) {
    int consumed;
    int named;
    int scanned;

    consumed = 0;
    scanned = sscanf((const char *)text, "%d%n", value, &consumed);
    if (((scanned == 0) || (scanned == -1)) && (text != 0)) {
        if (g_resultSuccess == igMetaEnum_GetValueByName((igMetaEnum *)(((int (*)())self->_getMetaEnumFunction)()), (const char *)text, &named)) {
            *value = named;
            consumed = strlen((const char *)text);
        }
    }
    return consumed;
}

igStringRef igEnumMetaField_ValueToString(igEnumArrayMetaField *self, int *value) {
    return igMetaEnum_GetNameByValue((const igMetaEnum *)(((int (*)())self->_getMetaEnumFunction)()), *value);
}

int **igEnumMetaField_Construct(int **self, int flags) {
    igMetaField_Construct((igMetaField *)self);
    *self = &g_igEnumMetaField_vtable[0];
    if (self != 0) {
        igEnumMetaField_Init(self);
    }
    return self;
}

int **igEnumMetaField_Init(int **self) {
    igMetaField_Init((igMetaField *)self);
    *self = &g_igEnumMetaField_vtable[0];
    return self;
}

int **igEnumMetaField_CopyConstruct(int **self, int source) {
    igMetaField_CopyConstruct((igMetaField *)self, (igMetaField *)source);
    *self = &g_igEnumMetaField_vtable[0];
    return self;
}

void igEnumMetaField_Destruct(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

/* Element size in bytes of the list's items: 4, the width of the igEnumMetaField element type that
 * slots 50/51 of this vtable return. */
int igEnumMetaField_GetSize(void) {
    return 4;
}

int igEnumMetaField_GetAlignment(void) {
    return 4;
}

int igErrorHandler_GetInstanceAlias()
{
    return igErrorHandler_GetInstance();
}

unsigned char g_igErrorHandler_released;
void *g_igErrorHandler_instance;

void igErrorHandler_ReleaseInstance(void) {
    if (g_igErrorHandler_instance != 0) {
        {
            igObject *held = (igObject *)g_igErrorHandler_instance;
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
    }
    g_igErrorHandler_instance = (void *)(0);
    g_igErrorHandler_released = 1;
}

int igErrorHandler_GetInstance(void) {
    if (((*(int *)&g_igErrorHandler_instance) == 0) && (g_igErrorHandler_metaObject != 0) && (g_igErrorHandler_released == 0)) {
        (*(int *)&g_igErrorHandler_instance) = igErrorHandler_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
    }
    return (*(int *)&g_igErrorHandler_instance);
}

