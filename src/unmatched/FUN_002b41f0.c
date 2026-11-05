/* 0x002b41f0 — FUN_002b41f0 (32 bytes). Forwards the word pair at +96 of the object to FUN_002b5678. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b5678();

struct WordPair {
    int f0;
    int f4;
};

struct Obj0060 {
    char pad[96];
    struct WordPair pair;                 /* +96 (0x60) */
};

void FUN_002b41f0(struct Obj0060 *obj) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    struct WordPair *pair = &obj->pair;

    FUN_002b5678(pair->f0, pair->f4);
}
