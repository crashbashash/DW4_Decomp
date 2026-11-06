extern "C" {
void *beDemoManagerWorkList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00363710(void);
}
void FUN_00363710(void)
{
    igMetaObject_RunStaticInit(beDemoManagerWorkList_Register);
}
