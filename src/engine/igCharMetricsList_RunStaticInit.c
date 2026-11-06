void *igCharMetricsList_Register(void);
void igCharMetricsList_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igCharMetricsList_Register);
}
