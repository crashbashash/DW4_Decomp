int Gap__Core__igEnumMetaField__vfunc_56(void *arg0, int *arg1, int arg2) {
    int sp4C;
    int sp48;
    int temp_v0;

    sp4C = 0;
    temp_v0 = sscanf(arg2, &DAT_004f9588[0], arg1, &sp4C);
    if (((temp_v0 == 0) || (temp_v0 == -1)) && (arg2 != 0)) {
        if (g_resultSuccess == igMetaEnum_GetValueByName((igMetaEnum *)(((int (*)())*(int *)((char *)(arg0) + 52))()), (const char *)arg2, &sp48)) {
            *arg1 = sp48;
            sp4C = strlen(arg2);
        }
    }
    return sp4C;
}

void Gap__Core__igEnumMetaField__vfunc_57(int result, igEnumArrayMetaField *self, int *value) {
    igMetaEnum_GetNameByValue((int *)result, (const igMetaEnum *)(((int (*)())self->_getMetaEnumFunction)()), *value);
}

int **FUN_002dc8c0(int **arg0, int extra1) {
    igMetaField_Construct((igMetaField *)arg0);
    *arg0 = &DAT_00532430[0];
    if (arg0 != 0) {
        FUN_002dc900(arg0);
    }
    return arg0;
}

int **FUN_002dc900(int **arg0) {
    igMetaField_Init((igMetaField *)arg0);
    *arg0 = &DAT_00532430[0];
    return arg0;
}

int **FUN_002dc940(int **arg0, int extra1) {
    igMetaField_CopyConstruct((igMetaField *)arg0, (igMetaField *)extra1);
    *arg0 = &DAT_00532430[0];
    return arg0;
}

void Gap__Core__igEnumMetaField__vfunc_02(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

/* Element size in bytes of the list's items: 4, the width of the igEnumMetaField element type that
 * slots 50/51 of this vtable return. */
int FUN_002dc990(void) {
    return 4;
}

int Gap__Core__igEnumMetaField__vfunc_27(void) {
    return 4;
}

int thunk_FUN_002dca20()
{
    return FUN_002dca20();
}

void FUN_002dc9c0(void) {
    if (DAT_00586df8[0] != 0) {
        {
            void *held = (void *)DAT_00586df8[0];
            *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
            if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
    }
    DAT_00586df8[0] = (void *)(0);
    GPR_00554bfc = 1;
}

int FUN_002dca20(void) {
    if ((((int *)DAT_00586df8)[0] == 0) && (g_igErrorHandler_metaObject[0] != 0) && (DAT_00554bfc == 0)) {
        ((int *)DAT_00586df8)[0] = FUN_002c5e10(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
    }
    return ((int *)DAT_00586df8)[0];
}

