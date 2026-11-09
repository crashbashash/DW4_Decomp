unsigned int strlen();
int strncmp();

typedef struct {
    int value;
    char name[12];
} NameEntry;

extern NameEntry DAT_0056e220[32];

int FUN_0026f890(char *name)
{
    unsigned int len;
    unsigned int i;

    len = strlen(name);
    for (i = 0; i < 32; i++) {
        if (strncmp(name, DAT_0056e220[i].name, len) == 0) {
            return DAT_0056e220[i].value;
        }
    }
    return 0;
}
