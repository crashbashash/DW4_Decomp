/* 0x0029da18 — FUN_0029da18 (76 bytes). Resets entry \`index\` of a 116-byte table: header (3, 1) via FUN_0029da68, body at +16 via FUN_0029da88. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdEntry {
    int f0;
    int f4;
    int f8;
    int f12;
    char body[100];         /* +16 */
} SfdEntry;

extern void FUN_0029da68(SfdEntry *entry, int a, int b);
extern void FUN_0029da88(void *body);

void FUN_0029da18(SfdEntry *table, int unused1, int unused2, int index) {
    SfdEntry *entry = &table[index];
    void *body = entry->body;

    FUN_0029da68(entry, 3, 1);
    FUN_0029da88(body);
}
