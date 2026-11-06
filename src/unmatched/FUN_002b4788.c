/* Fetches the value pair for `key` through FUN_002b4498 and forwards it with `arg` to
 * FUN_002b47d8. */
void FUN_002b4498(void *obj, int key, int *first, int *second);
void FUN_002b47d8(void *obj, int first, int second, int arg);

void FUN_002b4788(void *obj, int key, int arg) {
    int first;
    int second;

    FUN_002b4498(obj, key, &first, &second);
    FUN_002b47d8(obj, first, second, arg);
}
