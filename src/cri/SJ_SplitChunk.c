/* Splits a (pointer, length) chunk at max bytes: head gets the first min(length, max) bytes, rest
 * the remainder (a NULL pointer when nothing is left). */
typedef struct Chunk_27d470 {
    char *data;     /* 0x00 */
    int length;     /* 0x04 */
} Chunk_27d470;

void SJ_SplitChunk(Chunk_27d470 *chunk, int max, Chunk_27d470 *head, Chunk_27d470 *rest) {
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
