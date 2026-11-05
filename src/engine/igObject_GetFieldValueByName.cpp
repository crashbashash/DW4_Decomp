extern "C" {
void *igMetaObject_FindFieldByName(...);
int igObject_GetFieldValueByName(void **arg0, int arg1);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
int igObject_GetFieldValueByName(void **arg0, int arg1) {
    void *temp_v0;

    if (arg1 == 0) {
        return 0;
    }
    temp_v0 = (void *)(igMetaObject_FindFieldByName(((DW4VC_88_0 *)(arg0))->vX(), arg1));
    if (temp_v0 == 0) {
        return 0;
    }
    return *(int *)((char *)arg0 + *(int *)((char *)(temp_v0) + 8));
}
