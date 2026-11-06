extern "C" {
void *beGeneraterData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035fd50(void);
}
void FUN_0035fd50(void)
{
    igMetaObject_RunStaticInit(beGeneraterData_Register);
}
