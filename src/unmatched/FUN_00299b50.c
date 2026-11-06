/* When FUN_00299f88 reports 1, calls the hook at +32 of the table from FUN_00299f68 (if both
 * exist) with the handle's +20 value (read before the hook checks, as retail schedules it) and the
 * two arguments. */
struct Hooks00299b50 {
    char pad0[32];
    void (*hook)(int value, int a, int b); /* +32 */
};

struct Handle00299b50 {
    char pad0[20];
    int value; /* +20 */
};

int FUN_00299f88(void);
struct Hooks00299b50 *FUN_00299f68(void);

void FUN_00299b50(struct Handle00299b50 *handle, int a, int b) {
    struct Hooks00299b50 *hooks;
    int value;

    if (FUN_00299f88() == 1) {
        hooks = FUN_00299f68();
        value = handle->value;
        if (hooks != 0 && hooks->hook != 0) {
            hooks->hook(value, a, b);
        }
    }
}
