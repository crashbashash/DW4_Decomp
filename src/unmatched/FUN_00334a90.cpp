extern "C" {
void *igFileNameList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00334a90(void);
}
void FUN_00334a90(void)
{
    igMetaObject_RunStaticInit(igFileNameList_Register);
}
