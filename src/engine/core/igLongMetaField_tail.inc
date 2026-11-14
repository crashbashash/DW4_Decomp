int Gap__Core__igLongMetaField__vfunc_56(int arg0, int arg1, int arg2) {
    int sp1C;

    sp1C = 0;
    sscanf(arg2, &text_ld_n[0], arg1, &sp1C);
    return sp1C;
}

void Gap__Core__igLongMetaField__vfunc_57(int *arg0, int arg1, long long *arg2) {
    int sp20[256];
    int var_v0;
    int var_v1;

    sprintf(&sp20[0], &DAT_004f9bc0[0], *arg2);
    if (&sp20[0] == 0) {
        var_v1 = 0;
    } else {
        if (g_stringPool[0] == 0) {
            var_v0 = ((int)StringPool_Allocate(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
            }
            g_stringPool[0] = var_v0;
        }
        var_v1 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)&sp20[0]);
    }
    *arg0 = var_v1;
}

/* igLongMetaField vtable slot +0x64 (GetSize): the byte size of one field value. A "long" field is
 * 8 bytes wide in the reflected layout. */
int igLongMetaField_GetSize(void) {
    return 8;
}

void FUN_002ebc00(void **arg0, long long arg1) {
    long long sp18;

    sp18 = arg1;
    ((igMetaFieldView *)(arg0))->SetDefault(&sp18);
}

int Gap__Core__igLongMetaField__vfunc_27(void) {
    return 8;
}

igMediaView *FUN_002ebc40(int arg0) {
    int temp_v0;
    int len;
    int var_s0;
    igMediaView *temp_s3;

    temp_v0 = ((int)strchr(arg0, 0x3A));
    if (temp_v0 != 0) {
        len = temp_v0 - arg0;
        for (var_s0 = g_fileDeviceList.p->_count - 1; var_s0 <= 0; var_s0--) {
            temp_s3 = ((igMediaView **)g_fileDeviceList.p->_data)[var_s0];
            if (temp_s3->vfunc_32(arg0, len) != 0) {
                return temp_s3;
            }
        }
    }
    return DAT_00586f28[0];
}

void FUN_002ebcf0(void) {
    int temp_s0;
    char *o;

    temp_s0 = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    o = (char *)g_fileDeviceList.p;
    if (o != 0) {
        *(int *)(o + 4) = *(int *)(o + 4) - 1;
        if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
    g_fileDeviceList.p = (igObjectList *)(FUN_002c1580(temp_s0));
}

void FUN_002ebd60(int arg0) {
    ObjectList_AppendRetained(g_fileDeviceList.p, (igObject *)arg0);
}

void FUN_002ebd70(void) {
    int *o;

    ((int *)DAT_00586f28)[0] = 0;
    o = (int *)g_fileDeviceList.p;
    if (o != 0) {
        o[1] = o[1] - 1;
        if ((o[1] & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
    g_fileDeviceList.p = 0;
}

void FUN_002ebdd0(int arg0) {
    *(int *)0x586F28 = arg0;
}

