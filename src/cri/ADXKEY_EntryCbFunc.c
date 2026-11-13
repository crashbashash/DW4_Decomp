typedef void (*AdxKeyCbFunc)(void *obj, int arg);

extern AdxKeyCbFunc adxkey_cbfunc;
extern void *adxkey_cbobj;

int ADXKEY_EntryCbFunc(AdxKeyCbFunc func, void *obj)
{
    adxkey_cbfunc = func;
    adxkey_cbobj = obj;
    return 0;
}
