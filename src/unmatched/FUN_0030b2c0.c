int igRefMetaField_CopyConstruct();
extern int DAT_00533180[4];
void *FUN_0030b2c0(void *arg0, void *arg1) {
    igRefMetaField_CopyConstruct();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00533180[0]);
    *(unsigned char *)((char *)(arg0) + 56) = (unsigned char) *(unsigned char *)((char *)(arg1) + 56);
    return arg0;
}
