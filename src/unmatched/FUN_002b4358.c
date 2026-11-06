/* Marks the entry's parameter block at +8 valid (1) with the two arguments, then tail-calls
 * FUN_002b4380 on the entry. */
int FUN_002b4380();

struct EntryParams {
    int f0;                               /* set to 1 */
    int f4;
    int f8;
};

struct Entry14 {
    int inUse;
    int f4;
    struct EntryParams params;            /* +8 */
};

void FUN_002b4358(struct Entry14 *entry, int a, int b) {
    struct EntryParams *params = &entry->params;

    params->f0 = 1;
    params->f4 = a;
    params->f8 = b;
    FUN_002b4380(entry);
}
