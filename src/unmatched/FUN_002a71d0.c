/* 0x002a71d0 — FUN_002a71d0 (168 bytes). Delivers a decoded packet into the message's blob: copies type-3 payloads (memcpy) or hands the blob to FUN_002a73f0, after releasing kinds 1/2 to the context pool at +4116. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_002a7278();
void FUN_002a73f0();
void *memcpy();

struct Blob {
    char *data;
    int size;
};
struct Message2a71d0 {
    char pad0[84];
    struct Blob *blob;                    /* +84 */
    char pad88[112 - 88];
    int kind;                             /* +112 */
};
struct Player2a71d0 {
    char pad0[8120];
    char *context;                        /* +8120 */
};

void FUN_002a71d0(struct Player2a71d0 *player, struct Message2a71d0 *message, void *source) {
    char *context = player->context;
    int kind;
    char *data;
    int size;

    if ((unsigned int)(message->kind - 1) < 2) {
        FUN_002a73f0(context + 4116, message->blob);
    }
    FUN_002a7278(source, &kind, &data, &size);
    if (kind == 3) {
        memcpy(message->blob->data, data, size);
        message->blob->size = size;
    } else {
        FUN_002a73f0(message->blob, context + 4116);
    }
}
