/* Posts event (7, 8) with a value through FUN_002b0338. */
extern int FUN_002b0338(void *handle, int group, int event, int a, int b);

/* matching construct: hand — the long return type (callee returns int) is what keeps
   retail's plain jal instead of a sibling tail call */
long FUN_002aa4c8(void *handle, int value) {
    return FUN_002b0338(handle, 7, 8, value, 0);
}
