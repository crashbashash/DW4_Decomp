extern "C" {
void *beDemoKeepMesList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00363b70(void);
}
void FUN_00363b70(void)
{
    igMetaObject_RunStaticInit(beDemoKeepMesList_Register);
}
