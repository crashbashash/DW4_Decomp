/* 0x0027d470 — FUN_0027d470 (92 bytes). Splits a (pointer, length) chunk at max bytes: head gets the first min(length, max) bytes, rest the remainder (a NULL pointer when nothing is left). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Chunk_27d470 {
    char *data;     /* 0x00 */
    int length;     /* 0x04 */
} Chunk_27d470;

void FUN_0027d470(Chunk_27d470 *chunk, int max, Chunk_27d470 *head, Chunk_27d470 *rest) {
    *head = *chunk;
    rest->length = head->length;
    if (max < head->length) {
        head->length = max;
    }
    rest->length -= head->length;
    if (rest->length == 0) {
        rest->data = 0;
    } else {
        rest->data = head->data + head->length;
    }
}
