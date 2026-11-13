typedef void (*AdxErrFunc)(int obj, char *msg);

void *memset(void *dst, int c, unsigned int n);
char *strncpy(char *dst, const char *src, unsigned int n);
char *strncat(char *dst, const char *src, unsigned int n);
unsigned int strlen(const char *s);
void FUN_0027e8a0(void);
void FUN_0027e2f0(char *msg);

extern AdxErrFunc DAT_00499cd8;
extern int DAT_00499cdc;
extern char DAT_00499ce0[256];
extern char DAT_0056df88[];
extern char DAT_004ed8c0[];

void FUN_00260750(void)
{
    memset(DAT_00499ce0, 0, 0x100);
    DAT_00499cd8 = 0;
    DAT_00499cdc = 0;
}

void FUN_00260788(void)
{
    memset(DAT_00499ce0, 0, 0x100);
    DAT_00499cd8 = 0;
    DAT_00499cdc = 0;
}

void FUN_002607c0(AdxErrFunc func, int obj)
{
    DAT_00499cd8 = func;
    DAT_00499cdc = obj;
    FUN_0027e8a0();
}

void ADXERR_CallErrFunc1(const char *msg)
{
    strncpy(DAT_00499ce0, msg, 0xFF);
    if (DAT_00499cd8 != 0) {
        DAT_00499cd8(DAT_00499cdc, DAT_00499ce0);
    }
    FUN_0027e2f0(DAT_00499ce0);
}

void ADXERR_CallErrFunc2(const char *code, const char *msg)
{
    strncpy(DAT_00499ce0, code, 0xFF);
    strncat(DAT_00499ce0, msg, 0xFF);
    if (DAT_00499cd8 != 0) {
        DAT_00499cd8(DAT_00499cdc, DAT_00499ce0);
    }
    FUN_0027e2f0(DAT_00499ce0);
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
    len = strlen(DAT_0056df88);
    if (len >= size - 1) {
        len = size - 1;
    }
    for (i = 0; i < len; i++) {
        dst[i] = DAT_0056df88[len - 1 - i];
    }
    dst[i] = 0;
}

void ADXERR_ItoA2(int value, int extra, char *text, int size)
{
    FUN_002608b0(value, text, size);
    strncat(text, DAT_004ed8c0, (size - strlen(text)) - 1);
    FUN_002608b0(extra, text + strlen(text), 4 - strlen(text));
}
