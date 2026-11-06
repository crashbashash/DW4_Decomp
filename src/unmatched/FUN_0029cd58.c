/* Reads a coordinate pair from source via FUN_002af540 and stores FUN_002916f8(target, x, y) in
 * *result. */
int FUN_002916f8();
int FUN_002af540();

void FUN_0029cd58(void *source, int *result, int target) {
    int x;
    int y;

    FUN_002af540(source, &x, &y);
    *result = FUN_002916f8(target, x, y);
}
