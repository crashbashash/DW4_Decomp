/* Maps the state at +76 to a result code (2, 3, or 4 once FUN_002aaea0 allows it), defaulting to
 * the value at +72. */
int FUN_002aaea0(void *obj);
void FUN_002abe70(void *obj);

struct StateObj {
    char pad0[72];
    int result; /* +72 */
    int state;  /* +76 */
};

int FUN_002aad88(struct StateObj *obj) {
    int result = obj->result;

    switch (obj->state) {
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    case 4:
    case 6:
        if (FUN_002aaea0(obj) != 0) {
            result = 4;
            FUN_002abe70(obj);
        }
        break;
    }
    return result;
}
