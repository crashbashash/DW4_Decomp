extern char igAnimationStatePool_Register[];
void igAnimationStatePool_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igAnimationStatePool_Register);
}
