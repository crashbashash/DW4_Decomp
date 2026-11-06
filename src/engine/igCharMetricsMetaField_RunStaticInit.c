void *igCharMetricsMetaField_Register(void);
void igCharMetricsMetaField_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igCharMetricsMetaField_Register);
}
