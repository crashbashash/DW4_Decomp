/* 0x002b1908 — FUN_002b1908 (20 bytes). Fills a three-word record: valid flag 1, then the two arguments. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

struct Rec0C {
    int f0;                               /* set to 1 */
    int f4;
    int f8;
};

void FUN_002b1908(struct Rec0C *rec, int a, int b) {
    rec->f0 = 1;
    rec->f4 = a;
    rec->f8 = b;
}
