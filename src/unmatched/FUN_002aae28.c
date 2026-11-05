/* 0x002aae28 — FUN_002aae28 (112 bytes). Returns the result at +72, overridden to 6 when neither FUN_002ab3f0 nor FUN_002aaf08 fires and the state at +76 is 6. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002ab3f0(void *obj);
int FUN_002aaf08(void *obj);

struct StateObj {
    char pad0[72];
    int result; /* +72 */
    int state;  /* +76 */
};

int FUN_002aae28(struct StateObj *obj) {
    int state;
    int result;

    if (FUN_002ab3f0(obj) != 0 || FUN_002aaf08(obj) != 0) {
        return obj->result;
    }
    state = obj->state;
    result = obj->result;
    if (state >= 2) {
        if (state < 5) {
            return result;
        }
        if (state == 6) {
            result = 6;
        }
    }
    return result;
}
