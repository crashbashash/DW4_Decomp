igMetaObject *g_igBoolObject_metaObject;
igMetaField *g_igBoolObject_valueMetaField;

igMetaObject *igBoolObject_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolObject_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5ce0();
    return g_igBoolObject_metaObject;
}

int igBoolObject_GetVTable(void) {
    struct O o;
    igObject_InitHeader(&o.vt);
    o.vt = g_igBoolObject_vtable;
    return *(int *)((char *)&o.vt + *(int *)(g_objectSystem[0] + 916));
}

void FUN_001e5ce0(void)
{
    igMetaObject_RunStaticInit(igBoolObject_Register);
}

void igBoolObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBoolObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igBoolObject_GetMetaObject,
        "igBoolObject",
        0xC, /* instance size */
        igBoolObject_GetVTable,
        &igBoolObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBoolObject_GetMetaObject(void) {
    igBoolObject_GetMetaObject();
}

static FieldFactory g_igBoolObject_ctorTable[] = {
    igBoolMetaField_Create,
};
static const char *g_igBoolObject_fieldTable[] = {
    text_value,
};
static igMetaField **g_igBoolObject_fieldHandles[] = {
    &g_igBoolObject_valueMetaField,
};
static int g_igBoolObject_fieldOffsets[] = {
    8,
};

void igBoolObject_InitFields(void) {
    int firstField;
    igMetaObject *meta;

    meta = g_igBoolObject_metaObject;
    firstField = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igBoolObject_ctorTable, 1);
    igMetaObject_NameFields(meta, g_igBoolObject_fieldTable, g_igBoolObject_fieldHandles, g_igBoolObject_fieldOffsets, firstField);
}

/* matching construct: declaration-order sweep — v, scale, count, i order */
void FUN_001e5de0(Vec3fList *list, unsigned short *out, float base, float range) {
    float *v;
    float scale;
    int count;
    int i;
    float x;
    float y;
    float z;

    count = list->_count;
    scale = 65535 / range;
    for (i = 0; i < count; i++) {
        v = list->_data[i];
        x = v[0];
        y = v[1];
        z = v[2];
        *out++ = (unsigned int)(scale * (x - base));
        *out++ = (unsigned int)(scale * (y - base));
        *out++ = (unsigned int)(scale * (z - base));
    }
}

static inline void extend(float value, float *minimum, float *maximum) {
    if (value < *minimum) {
        *minimum = value;
    } else if (!(value <= *maximum)) {
        *maximum = value;
    }
}

void FUN_001e5f00(Vec3fList *list, unsigned short *quantized, float *minimum, float *range) {
    int i;
    int count;
    float maximum;
    const float *v;
    float y;
    float z;
    float x;

    count = list->_count;
    maximum = *minimum = list->_data[0][0];
    for (i = 0; i < count; i++) {
        v = list->_data[i];
        x = v[0];
        y = v[1];
        z = v[2];
        extend(x, minimum, &maximum);
        extend(y, minimum, &maximum);
        extend(z, minimum, &maximum);
    }
    *range = maximum - *minimum;
    FUN_001e5de0(list, quantized, *minimum, *range);
}

void FUN_001e5fe0(igQuaternionfList *list, short *quantized, float minimum, float range) {
    const float *q;
    float scale;
    int count;
    int i;
    float x;
    float y;
    float z;
    float w;

    count = list->_count;
    scale = 65535 / range;
    for (i = 0; i < count; i++) {
        q = (float *)list->_data + i * 4;
        x = q[0];
        y = q[1];
        z = q[2];
        w = q[3];
        *quantized++ = (unsigned int)(scale * (x - minimum));
        *quantized++ = (unsigned int)(scale * (y - minimum));
        *quantized++ = (unsigned int)(scale * (z - minimum));
        *quantized++ = (unsigned int)(scale * (w - minimum));
    }
}

void FUN_001e6130(igQuaternionfList *list, short *quantized, float *minimum, float *range) {
    int i;
    int count;
    float maximum;
    const float *q;
    float y;
    float z;
    float w;
    float x;

    count = list->_count;
    maximum = *minimum = *(float *)list->_data;
    for (i = 0; i < count; i++) {
        q = (float *)list->_data + i * 4;
        x = q[0];
        y = q[1];
        z = q[2];
        w = q[3];
        extend(x, minimum, &maximum);
        extend(y, minimum, &maximum);
        extend(z, minimum, &maximum);
        extend(w, minimum, &maximum);
    }
    *range = maximum - *minimum;
    FUN_001e5fe0(list, quantized, *minimum, *range);
}

