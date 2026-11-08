int sscanf();
int igMetaEnum_GetValueByName();
int strlen();
extern int DAT_004f9588[4];
extern int DAT_004fb410[4];
int Gap__Core__igEnumMetaField__vfunc_56(void *arg0, int *arg1, int arg2) {
    int sp4C;
    int sp48;
    int sp44;
    int temp_v0;

    sp4C = 0;
    temp_v0 = sscanf(arg2, &DAT_004f9588[0], arg1, &sp4C);
    if (((temp_v0 == 0) || (temp_v0 == -1)) && (arg2 != 0)) {
        igMetaEnum_GetValueByName(&sp44, ((int (*)())*(int *)((char *)(arg0) + 52))(), arg2, &sp48);
        if (DAT_004fb410[0] == sp44) {
            *arg1 = sp48;
            sp4C = strlen(arg2);
        }
    }
    return sp4C;
}
