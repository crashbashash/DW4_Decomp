int igUnsignedIntMetaField_ValueFromString(int arg0, int arg1, int arg2) {
    int sp1C;

    sp1C = 0;
    sscanf(arg2, &DAT_004fb440[0], arg1, &sp1C);
    return sp1C;
}

void igUnsignedIntMetaField_ValueToString(int *arg0, void *arg1, int *arg2) {
    int sp20[256];
    int var_v0;
    int var_v1;

    sprintf(sp20, &DAT_004fb448[0], *arg2);
    if (sp20 == 0) {
        var_v1 = 0;
    } else {
        if (g_stringPool[0] == 0) {
            var_v0 = ((int)StringPool_Allocate(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((StringPool *)var_v0));
            }
            g_stringPool[0] = var_v0;
        }
        var_v1 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)sp20);
    }
    *arg0 = var_v1;
}

/* Vtable slot 53 of igNonRefCountedThreadList: a constant leaf returning 4. The list's element
 * type is igUnsignedIntMetaField (slots 50 and 51 hand out that class's metaobject and
 * descriptor), so 4 is read as the element size in bytes. The receiver is not touched, hence no
 * parameters. */
int igUnsignedIntMetaField_GetSize(void) {
    return 4;
}

void *igUnsignedIntMetaField_Construct(igMetaField *self, int extra1) {
    igMetaField_Construct(self);
    self->_vtable = (int)g_igUnsignedIntMetaField_vtable;
    if (self) {
        igUnsignedIntMetaField_Init(self);
    }
    return self;
}

void *igUnsignedIntMetaField_Init(igMetaField *self) {
    igMetaField_Init(self);
    self->_vtable = (int)g_igUnsignedIntMetaField_vtable;
    return self;
}

int **igUnsignedIntMetaField_CopyConstruct(int **arg0, int extra1) {
    igMetaField_CopyConstruct((igMetaField *)arg0, (igMetaField *)extra1);
    *arg0 = &g_igUnsignedIntMetaField_vtable[0];
    return arg0;
}

void igUnsignedIntMetaField_Destruct(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

void igUnsignedIntMetaField_SetDefaultValue(void **arg0, int arg1) {
    int sp1C;

    sp1C = arg1;
    ((igMetaFieldView *)(arg0))->SetDefault(&sp1C);
}

int igUnsignedIntMetaField_GetAlignment(void) {
    return 4;
}

