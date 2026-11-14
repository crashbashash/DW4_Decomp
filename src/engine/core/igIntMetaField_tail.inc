int Gap__Core__igIntMetaField__vfunc_56(int arg0, int arg1, int arg2) {
    int sp1C;

    sp1C = 0;
    sscanf(arg2, &DAT_004f9588[0], arg1, &sp1C);
    return sp1C;
}

void Gap__Core__igIntMetaField__vfunc_57(int *arg0, int arg1, int *arg2) {
    int sp20[256];
    int var_v0;
    int var_v1;

    sprintf(&sp20[0], &DAT_004f95c0[0], *arg2);
    if (&sp20[0] == 0) {
        var_v1 = 0;
    } else {
        if (g_stringPool[0] == 0) {
            var_v0 = ((int)StringPool_Allocate(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((StringPool *)var_v0));
            }
            g_stringPool[0] = var_v0;
        }
        var_v1 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)&sp20[0]);
    }
    *arg0 = var_v1;
}

int FUN_002ea3d0(void) {
    return 4;
}

void *igIntMetaField_Construct(igMetaField *self, int extra1) {
    igMetaField_Construct(self);
    self->_vtable = (int)g_igIntMetaField_vtable;
    if (self) {
        igIntMetaField_Init(self);
    }
    return self;
}

void *igIntMetaField_Init(igMetaField *self) {
    igMetaField_Init(self);
    self->_vtable = (int)g_igIntMetaField_vtable;
    return self;
}

int **FUN_002ea460(int **arg0, int extra1) {
    igMetaField_CopyConstruct((igMetaField *)arg0, (igMetaField *)extra1);
    *arg0 = &g_igIntMetaField_vtable[0];
    return arg0;
}

void Gap__Core__igIntMetaField__vfunc_02(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

void FUN_002ea4b0(void **arg0, int arg1) {
    int sp1C;

    sp1C = arg1;
    ((igMetaFieldView *)(arg0))->SetDefault(&sp1C);
}

int Gap__Core__igIntMetaField__vfunc_27(void) {
    return 4;
}

