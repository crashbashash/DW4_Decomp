/* CRI CFG: a small table of named integer settings the other CRI libraries read at start-up. */

typedef struct CriCfgEntry {
    char name[12];
    int value;
} CriCfgEntry;

char *strncpy(char *dst, const char *src, unsigned int size);
int strncmp(const char *a, const char *b, unsigned int size);

extern CriCfgEntry *cricfg_table;
extern int cricfg_count;

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

int FUN_0026f4b0(const char *name, int *value)
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
