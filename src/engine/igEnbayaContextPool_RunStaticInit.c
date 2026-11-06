extern char igEnbayaContextPool_Register[];
void igEnbayaContextPool_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igEnbayaContextPool_Register);
}
