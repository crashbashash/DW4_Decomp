typedef struct AdxEntry { int a; int b; } AdxEntry;
typedef struct AdxTableHeader { int f0; int f4; int count; int nameLength; } AdxTableHeader;

extern AdxTableHeader DAT_004ab9f0;
int FUN_002763a8(const char *a, const char *b);

/* matching construct: 16-variant sweep — the address sum */
void FUN_00276a28(AdxEntry *out, const char *name, AdxEntry *entries, int n) {
    int i;
    for (i = 0; i < n; i++) {
        const char *entryName = (char *)entries + (DAT_004ab9f0.count * sizeof(AdxEntry) + i * (DAT_004ab9f0.nameLength + 1));
        if (FUN_002763a8(name, entryName) == 0) {
            out->a = entries[i].a;
            out->b = entries[i].b;
            return;
        }
    }
    out->a = 0;
    out->b = 0;
}
