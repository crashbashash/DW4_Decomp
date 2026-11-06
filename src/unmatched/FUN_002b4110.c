/* Forwards the word pair at +96 of the object to FUN_002b5360. */
int FUN_002b5360();

struct WordPair {
    int f0;
    int f4;
};

struct Obj0060 {
    char pad[96];
    struct WordPair pair;                 /* +96 (0x60) */
};

void FUN_002b4110(struct Obj0060 *obj) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    struct WordPair *pair = &obj->pair;

    FUN_002b5360(pair->f0, pair->f4);
}
