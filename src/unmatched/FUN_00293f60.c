/* 0x00293f60 — FUN_00293f60 (52 bytes). Fetches a 16-byte record with FUN_002a3170(a, b, c, &record) and hands it to FUN_00294108 with `out`. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

struct Record00293f60 {
    int word[4];
};

void FUN_002a3170(int a, int b, int c, struct Record00293f60 *record);
void FUN_00294108(struct Record00293f60 *record, void *out);

void FUN_00293f60(int a, int b, int c, void *out) {
    struct Record00293f60 record;

    FUN_002a3170(a, b, c, &record);
    FUN_00294108(&record, out);
}
