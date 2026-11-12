void FUN_001d8b90(void) {
    void *sp1C;

    FUN_003087a0(&sp1C, DAT_00586dd0[0], ((char *)DAT_004fb3a8));
    FUN_002d81f0(sp1C, &DAT_004e4870[0]);
    if (sp1C != 0) {
        *(int *)((char *)sp1C + 4) = (int) (*(int *)((char *)sp1C + 4) - 1);
        if (((unsigned long long) ((long long) *(int *)((char *)sp1C + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)sp1C);
        }
    }
}

int Gap__Sg__igShaderInfo__vfunc_23(ShaderFieldTable *self, int arg1, ShaderFieldRecord *key) {
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
    name = name != 0 ? name : &DAT_004e0858[0];
    FUN_002e2d30(arg1, self, name, key, idx, list, self);
    return 1;
}

int Gap__Sg__igShaderInfo__vfunc_24(struct S1d *arg0, int *arg1) {
    int r = igProperty_FindByName(arg0->f20, DAT_00585be0[0], arg1);
    if (r != 0) {
        return r;
    }
    return igProperty_FindByName(arg0->f20, DAT_00585be0[0], &DAT_004e4868[0]);
}

