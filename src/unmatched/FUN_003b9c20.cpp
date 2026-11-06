extern "C" {
void *beNDMWStatusCtrlDisk_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b9c20(void);
}
void FUN_003b9c20(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlDisk_Register);
}
