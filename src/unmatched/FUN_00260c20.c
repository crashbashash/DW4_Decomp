typedef struct {
    char id;
    char kind;
    unsigned short count;
    int arg0;
    int arg1;
    int arg2;
} LogEntry;

extern LogEntry DAT_0049a630[16];
extern unsigned short DAT_0049a730[16];
extern int DAT_0049a750;

/* matching construct: sweep of all 120 orders of the entry stores */
void FUN_00260c20(int id, int kind, int arg0, int arg1, int arg2)
{
    LogEntry *e;

    DAT_0049a750 = DAT_0049a750 % 16;
    e = &DAT_0049a630[DAT_0049a750];
    if (kind == 0) {
        DAT_0049a730[id]++;
    }
    e->arg2 = arg2;
    e->arg0 = arg0;
    e->arg1 = arg1;
    e->id = id;
    e->kind = kind;
    DAT_0049a750++;
    e->count = DAT_0049a730[id];
}
