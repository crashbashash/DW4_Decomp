extern "C" {
void *beMatCtrlInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00359980(void);
}
void FUN_00359980(void)
{
    igMetaObject_RunStaticInit(beMatCtrlInfoRam_Register);
}
