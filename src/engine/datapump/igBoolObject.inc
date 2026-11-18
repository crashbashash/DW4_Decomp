igMetaObject *g_igBoolObject_metaObject;
igMetaField *g_igBoolObject_valueMetaField;

igMetaObject *igBoolObject_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolObject_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBoolObject_EnsureRegistered();
    return g_igBoolObject_metaObject;
}

int igBoolObject_GetVTable(void) {
    struct O o;
    igObject_InitHeader((igObject *)&o.vt);
    o.vt = g_igBoolObject_vtable;
    return *(int *)((char *)&o.vt + g_objectSystem->vtableProbeOffset);
}

void igBoolObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBoolObject_Register);
}

CallbackArray *igBoolObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBoolObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igBoolObject_GetMetaObjectFunction,
        "igBoolObject",
        0xC, /* instance size */
        igBoolObject_GetVTable,
        &igBoolObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igBoolObject_GetMetaObjectFunction(void) {
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
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igBoolObject_ctorTable, 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igBoolObject_fieldTable, g_igBoolObject_fieldHandles, g_igBoolObject_fieldOffsets, firstField);
}

/* matching construct: declaration-order sweep — v, scale, count, i order */
void igCompressVec3fListRange(Vec3fList *list, unsigned short *out, float base, float range) {
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

void igCompressVec3fList(igVec3fList *vecList, unsigned short *quantized, float *minimum, float *range) {
    Vec3fList *list = (Vec3fList *)vecList;
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
    igCompressVec3fListRange(list, quantized, *minimum, *range);
}

void igCompressVec4fListRange(igQuaternionfList *list, short *quantized, float minimum, float range) {
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

void igCompressVec4fList(igQuaternionfList *list, short *quantized, float *minimum, float *range) {
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
    igCompressVec4fListRange(list, quantized, *minimum, *range);
}

