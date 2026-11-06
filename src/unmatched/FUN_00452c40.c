int igCharMetricsMetaField_RunStaticInit();
extern int DAT_0058c650[4];
int FUN_00452c40(void) {
    if (DAT_0058c650[0] == 0) {
        igCharMetricsMetaField_RunStaticInit();
    }
    return DAT_0058c650[0];
}
