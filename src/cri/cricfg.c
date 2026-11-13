/* CRI CFG: a small table of named integer settings the other CRI libraries read at start-up. */

typedef struct CriCfgEntry {
    char name[12];
    int value;
} CriCfgEntry;

void *memset(void *dst, int value, unsigned int size);
char *strncpy(char *dst, const char *src, unsigned int size);
int strncmp(const char *a, const char *b, unsigned int size);

extern char CRI_CFG_PS2EE_Ver_1_002_Build_Oct_6_2004_11_47_45[];
extern char *volatile cricfg_build;
extern CriCfgEntry *cricfg_table;
extern int cricfg_count;
extern char cricfg_work[256];

void CRICFG_Init(void)
{
    int pad;

    cricfg_build = CRI_CFG_PS2EE_Ver_1_002_Build_Oct_6_2004_11_47_45;
    memset(cricfg_work, 0, sizeof(cricfg_work));
    cricfg_table = (CriCfgEntry *)(((int)cricfg_work + 3) & ~3);
    pad = (char *)cricfg_table - cricfg_work;
    cricfg_count = ((int)sizeof(cricfg_work) - pad) / (int)sizeof(CriCfgEntry);
}

void CRICFG_Finish(void)
{
    cricfg_table = 0;
    cricfg_count = 0;
}

CriCfgEntry *cricfg_SearchFreeEntry(void)
{
    CriCfgEntry *entry = cricfg_table;
    int i;

    for (i = 0; i < cricfg_count; i++, entry++) {
        if (entry->name[0] == 0) {
            return entry;
        }
    }
    return 0;
}

CriCfgEntry *cricfg_SearchEntry(const char *name)
{
    CriCfgEntry *entry;
    int i;

    if (name[0] == 0) {
        return 0;
    }
    entry = cricfg_table;
    for (i = 0; i < cricfg_count; i++, entry++) {
        if (strncmp(entry->name, name, sizeof(entry->name)) == 0) {
            return entry;
        }
    }
    return 0;
}

int CRICFG_Write(const char *name, int value)
{
    CriCfgEntry *entry;

    if (cricfg_table == 0) {
        return -1;
    }
    entry = cricfg_SearchFreeEntry();
    if (entry == 0) {
        return -2;
    }
    strncpy(entry->name, name, sizeof(entry->name));
    entry->value = value;
    return 0;
}

int CRICFG_Read(const char *name, int *value)
{
    CriCfgEntry *entry;

    if (cricfg_table == 0) {
        return -1;
    }
    entry = cricfg_SearchEntry(name);
    if (entry == 0) {
        return -3;
    }
    *value = entry->value;
    return 0;
}
