extern "C" {
void *beShadow01InfoList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00344a90(void);
}
void FUN_00344a90(void)
{
    igMetaObject_RunStaticInit(beShadow01InfoList_Register);
}
