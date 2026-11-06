extern "C" {
void *beSvDeliver_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034b260(void);
}
void FUN_0034b260(void)
{
    igMetaObject_RunStaticInit(beSvDeliver_Register);
}
