extern "C" {
void *beMatCtrlInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00359cd0(void);
}
void FUN_00359cd0(void)
{
    igMetaObject_RunStaticInit(beMatCtrlInfo_Register);
}
