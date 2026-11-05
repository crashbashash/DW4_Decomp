struct O { int *vt; int p; };
int igObject_InitHeader(void *);
extern int DAT_00523a20[4];
extern char *DAT_00586dc8[4];
int igGenericAttrDefaultManager_GetVTable(void) {
    struct O o;
    int pad[2];
    igObject_InitHeader(&o);
    o.vt = DAT_00523a20;
    return *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
}
