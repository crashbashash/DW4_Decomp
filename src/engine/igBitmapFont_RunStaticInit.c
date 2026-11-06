void *igBitmapFont_Register(void);
void igBitmapFont_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igBitmapFont_Register);
}
