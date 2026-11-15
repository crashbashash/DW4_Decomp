typedef void (*AdxErrFunc)(int obj, char *msg);

void *memset(void *dst, int c, unsigned int n);
char *strncpy(char *dst, const char *src, unsigned int n);
char *strncat(char *dst, const char *src, unsigned int n);
unsigned int strlen(const char *s);
void SVM_SetCbErr(void);
void SVM_CallErr(char *msg);

AdxErrFunc adxerr_func = 0;
int adxerr_obj = 0;
char adxerr_msg[256] = {0};
static char adxerr_digits[32];

void FUN_00260750(void)
{
    memset(adxerr_msg, 0, 0x100);
    adxerr_func = 0;
    adxerr_obj = 0;
}

void FUN_00260788(void)
{
    memset(adxerr_msg, 0, 0x100);
    adxerr_func = 0;
    adxerr_obj = 0;
}

void ADXERR_EntryErrFunc(AdxErrFunc func, int obj)
{
    adxerr_func = func;
    adxerr_obj = obj;
    SVM_SetCbErr();
}

void ADXERR_CallErrFunc1(const char *msg)
{
    strncpy(adxerr_msg, msg, 0xFF);
    if (adxerr_func != 0) {
        adxerr_func(adxerr_obj, adxerr_msg);
    }
    SVM_CallErr(adxerr_msg);
}

void ADXERR_CallErrFunc2(const char *code, const char *msg)
{
    strncpy(adxerr_msg, code, 0xFF);
    strncat(adxerr_msg, msg, 0xFF);
    if (adxerr_func != 0) {
        adxerr_func(adxerr_obj, adxerr_msg);
    }
    SVM_CallErr(adxerr_msg);
}

void FUN_002608b0(int value, char *dst, int size)
{
    int i;
    int len;

    for (i = 0; i < 32; i++) {
        dst[i] = value % 10;
        value /= 10;
        if (value == 0) {
            dst[i] = 0;
            break;
        }
    }
    len = strlen(adxerr_digits);
    if (len >= size - 1) {
        len = size - 1;
    }
    for (i = 0; i < len; i++) {
        dst[i] = adxerr_digits[len - 1 - i];
    }
    dst[i] = 0;
}

void ADXERR_ItoA2(int value, int extra, char *text, int size)
{
    FUN_002608b0(value, text, size);
    strncat(text, " ", (size - strlen(text)) - 1);
    FUN_002608b0(extra, text + strlen(text), 4 - strlen(text));
}
