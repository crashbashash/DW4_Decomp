extern "C" {
void *beNumVerInsideData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034df30(void);
}
void FUN_0034df30(void)
{
    igMetaObject_RunStaticInit(beNumVerInsideData_Register);
}
