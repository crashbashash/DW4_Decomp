extern "C" {
void *beGeneraterItemDataOne_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003609f0(void);
}
void FUN_003609f0(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemDataOne_Register);
}
