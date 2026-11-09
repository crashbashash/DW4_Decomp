unsigned int strlen(const char *);
int strncmp(const char *, const char *, unsigned int);
void FUN_0026f530(const char *message);
extern char DAT_004eef88[];

typedef struct {
    int value;
    char name[12];
} NameEntry;

extern NameEntry DAT_0056e220[32];

void FUN_0026f988(const char *name)
{
    unsigned int len;
    unsigned int i;

    if (name == 0) {
        FUN_0026f530(DAT_004eef88);
        return;
    }
    len = strlen(name);
    for (i = 0; i < 32; i++) {
        if (strncmp(name, DAT_0056e220[i].name, len) == 0) {
            DAT_0056e220[i].name[0] = 0;
            return;
        }
    }
}
