/* Initialises each of `count` 16-byte entries with FUN_002b18f0. */
struct Entry16 {
    int words[4];
};

void FUN_002b18f0(struct Entry16 *entry);

void FUN_002b1920(int count, struct Entry16 *entries) {
    int i;

    for (i = 0; i < count; i++) {
        FUN_002b18f0(&entries[i]);
    }
}
