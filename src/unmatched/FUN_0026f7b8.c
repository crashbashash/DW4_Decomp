unsigned int strlen(const char *);
void *memcpy(void *, const void *, unsigned int);
void FUN_0026f928(char *name);
int FUN_0026f890(const char *name);

typedef struct {
    int value;
    char name[12];
} NameEntry;

extern NameEntry DAT_0056e220[32];

int FUN_0026f7b8(char *name, int (*get_interface)(void))
{
    int vtbl;
    int i;

    FUN_0026f928(name);
    vtbl = get_interface();
    i = 0;
    if (FUN_0026f890(name) != 0) {
        return vtbl;
    }
    for (; i < 32; i++) {
        if (DAT_0056e220[i].name[0] == 0) {
            break;
        }
    }
    if (i == 32) {
        return 0;
    }
    DAT_0056e220[i].value = vtbl;
    memcpy(DAT_0056e220[i].name, name, strlen(name) + 1);
    return vtbl;
}
