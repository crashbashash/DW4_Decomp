void _sceSifLoadModuleBuffer(void);
void FUN_00112df0(void);
void FUN_00112df0(void)
{
    /* matching construct: hand search — inside the loop the call is not a tail call, so the frame stays */
    do {
        _sceSifLoadModuleBuffer();
    } while (0);
}
