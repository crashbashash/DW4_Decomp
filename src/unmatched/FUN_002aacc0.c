typedef struct AdxModeFlags {
    char pad[20];
    int a;
    int b;
} AdxModeFlags;

typedef struct AdxModeObj {
    char pad[2564];
    AdxModeFlags flags;
} AdxModeObj;

void FUN_002ada78(AdxModeObj *obj, int id, int value);
int FUN_002adc40(AdxModeObj *obj, int id);
int FUN_002b5b38(void);

void FUN_002aacc0(AdxModeObj *obj)
{
    AdxModeFlags *flags = &obj->flags;
    unsigned int mask;
    int value;

    mask = 0;
    if (flags->b == 1)
        mask = 1;
    if (flags->a == 1)
        mask |= 2;
    switch (mask) {
    case 1:
        value = 1;
        break;
    case 2:
        value = 2;
        break;
    case 3:
        value = FUN_002adc40(obj, 25);
        if (value == 0 && (FUN_002b5b38() != 0 || FUN_002adc40(obj, 72) == 0))
            value = 3;

        break;
    default:
        value = 3;
        break;
    }
    FUN_002ada78(obj, 25, value);
}
