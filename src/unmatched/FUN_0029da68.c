/* Initialises an entry header: two caller values, two zeroed words and 9 at +76/+80. */
typedef struct SfdEntryHeader {
    int f0;
    int f4;
    int f8;
    int f12;
    char pad16[60];
    int f76;                /* +76 */
    int f80;                /* +80 */
} SfdEntryHeader;

void FUN_0029da68(SfdEntryHeader *entry, int a, int b) {
    entry->f0 = a;
    entry->f4 = b;
    entry->f8 = 0;
    entry->f12 = 0;
    entry->f76 = 9;
    entry->f80 = 9;
}
