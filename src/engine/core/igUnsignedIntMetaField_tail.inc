int Gap__Core__igUnsignedIntMetaField__vfunc_56(int arg0, int arg1, int arg2) {
    int sp1C;

    sp1C = 0;
    sscanf(arg2, &DAT_004fb440[0], arg1, &sp1C);
    return sp1C;
}

void Gap__Core__igUnsignedIntMetaField__vfunc_57(int *arg0, void *arg1, int *arg2) {
    int sp20[256];
    int var_v0;
    int var_v1;

    sprintf(sp20, &DAT_004fb448[0], *arg2);
    if (sp20 == 0) {
        var_v1 = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0 = ((int)FUN_002eb010(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
            }
            DAT_00586f20[0] = var_v0;
        }
        var_v1 = StringPool_Intern((StringPool *)DAT_00586f20[0], (const char *)sp20);
    }
    *arg0 = var_v1;
}

/* Vtable slot 53 of igNonRefCountedThreadList: a constant leaf returning 4. The list's element
 * type is igUnsignedIntMetaField (slots 50 and 51 hand out that class's metaobject and
 * descriptor), so 4 is read as the element size in bytes. The receiver is not touched, hence no
 * parameters. */
int FUN_0030e8d0(void) {
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

int **FUN_0030e960(int **arg0, int extra1) {
    igMetaField_CopyConstruct((igMetaField *)arg0, (igMetaField *)extra1);
    *arg0 = &DAT_00533430[0];
    return arg0;
}

void Gap__Core__igUnsignedIntMetaField__vfunc_02(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

void FUN_0030e9b0(void **arg0, int arg1) {
    int sp1C;

    sp1C = arg1;
    ((DW4VC_140_1 *)(arg0))->vX((int)(&sp1C));
}

int Gap__Core__igUnsignedIntMetaField__vfunc_27(void) {
    return 4;
}

