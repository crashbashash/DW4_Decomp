/* Creates an object of kind 2 with FUN_0026b348 over the buffer past its first 1024 bytes and, on
 * success, hands it the 1024-byte head through FUN_00278f20; returns the object or 0. */
void *FUN_0026b348(int kind, char *buffer, int size);
void FUN_00278f20(void *object, char *head, int size);

void *FUN_0026b658(char *buffer, int size) {
    void *object = FUN_0026b348(2, buffer + 1024, size - 1024);

    if (object == 0) {
        return 0;
    }
    FUN_00278f20(object, buffer, 1024);
    return object;
}
