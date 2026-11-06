extern "C" {
void *beNumVerData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034db60(void);
}
void FUN_0034db60(void)
{
    igMetaObject_RunStaticInit(beNumVerData_Register);
}
