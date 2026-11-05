void *igProperty_FindByName();
extern int DAT_00585be0[4];
int FUN_002d8e70(int arg0, int arg1) {
    void *temp_v0;

    temp_v0 = (void *)(igProperty_FindByName(arg0, DAT_00585be0[0], arg1));
    if (temp_v0 == 0) {
        return 0;
    }
    return *(int *)((char *)(temp_v0) + 24);
}
