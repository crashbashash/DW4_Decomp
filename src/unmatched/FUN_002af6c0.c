/* Returns 1 while the block at +0xA04 is enabled (+56); otherwise asks FUN_002af848 with the limit
 * at +176 and returns its verdict. */
void FUN_002af848(int obj, int a, int b, int *verdict, int limit);

struct BlockA04 {
    char pad0[56];
    int enabled; /* +56 */
    char pad60[176 - 60];
    int limit;   /* +176 */
};

int FUN_002af6c0(int obj, int a, int b) {
    struct BlockA04 *block = (struct BlockA04 *)(obj + 0xA04);
    int verdict;

    if (block->enabled != 0) {
        return 1;
    }
    FUN_002af848(obj, a, b, &verdict, block->limit);
    return verdict;
}
