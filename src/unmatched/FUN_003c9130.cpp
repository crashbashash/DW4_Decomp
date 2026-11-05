/* 0x003c9130 - FUN_003c9130. Near-miss sweep fix (alternate compiler), verified byte-identical to retail by tools/verify.py. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_0058bf88[4];
int FUN_003c9130(void) {
    if (DAT_0058bf88[0] == 0) {
        DAT_0058bf88[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058bf88[0];
}
} /* extern "C" */
