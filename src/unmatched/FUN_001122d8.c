void sceSifFreeSysMemory(void);
void FUN_001122d8(void);
void FUN_001122d8(void)
{
    /* matching construct: hand search — inside the loop the call is not a tail call, so the frame stays */
    do {
        sceSifFreeSysMemory();
    } while (0);
}
