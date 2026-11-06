/* Refreshes the video block at +2316 from the stream's FUN_0028d4a8/FUN_0028d510 info and fills
 * its unset (-1) fields from the parameters. */
void FUN_0028d4a8();
void FUN_0028d510();

struct Params {
    int handle;
    int f4;
    int f8;
};
struct Video {
    char pad0[24];
    int f24;
    int f28;
    int pad32;
    int f36;
    int f40;
};
struct Player2a2888 {
    char pad0[2316];
    struct Video video;                   /* +2316 */
    char pad2360[8052 - 2316 - (int)sizeof(struct Video)];
    struct Params *params;                /* +8052 */
};
/* Filled by FUN_0028d4a8 / FUN_0028d510; only the words read here are named. */
struct InfoA {
    int f0, f4, f8;
    int f12;
};
struct InfoB {
    int f0, f4, f8, f12;
    int f16;
    int rest[3];
};

void FUN_002a2888(struct Player2a2888 *player) {
    struct Video *video = &player->video;
    struct Params *params = player->params;
    int handle = params->handle;
    struct InfoA a;
    struct InfoB b;

    FUN_0028d4a8(handle, &a);
    if (a.f12 > 0) {
        video->f24 = a.f12;
    }
    FUN_0028d510(handle, &b, 1);
    if (b.f16 != -1) {
        video->f28 = b.f16;
    }
    if (video->f36 == -1) {
        video->f36 = params->f8;
    }
    if (video->f40 == -1) {
        video->f40 = params->f4;
    }
}
