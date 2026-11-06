/* Points the player at its embedded parameter block, resets it and opens a FUN_0028da88 decoder
 * with callback FUN_002a2c60, reporting errors 0xFF000D08/0xFF000D09. */
int FUN_0028d918();
void *FUN_0028da88();
void FUN_002a0bb8();
void FUN_002a2bd8();
void FUN_002a2c60();
void FUN_002a2cc8();

struct Params {
    void *handle;
};
struct Player2a2b10 {
    char pad0[8052];
    struct Params *params;                /* +8052 */
    char pad8056[8592 - 8056];
    struct Params storage;                /* +8592 */
};

void FUN_002a2b10(struct Player2a2b10 *player) {
    struct Params *params = &player->storage;
    void *decoder;

    player->params = params;
    FUN_002a2bd8(params);
    decoder = FUN_0028da88();
    if (decoder == 0) {
        FUN_002a0bb8(0, 0xFF000D08);
    } else if (FUN_0028d918(decoder, FUN_002a2c60, player) != 0) {
        FUN_002a2cc8(decoder);
        FUN_002a0bb8(0, 0xFF000D09);
    } else {
        params->handle = decoder;
    }
}
