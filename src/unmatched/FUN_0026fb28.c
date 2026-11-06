/* Returns 1 when the first length characters of name match the name of one of the 32 entries of
 * the device table DAT_0056e220 (FUN_0012aba0 returning 0), else 0. */
typedef struct CvFsDevEntry_26fb28 {
    void *device;   /* 0x00: interface table */
    char name[12];  /* 0x04 */
} CvFsDevEntry_26fb28;

extern CvFsDevEntry_26fb28 DAT_0056e220[32];
int FUN_0012aba0(const char *a, const char *b, int length);

int FUN_0026fb28(const char *name, int length) {
    int i;

    for (i = 0; i < 32; i++) {
        if (FUN_0012aba0(name, DAT_0056e220[i].name, length) == 0) {
            return 1;
        }
    }
    return 0;
}
