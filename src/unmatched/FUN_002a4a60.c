typedef struct Stream2a4a60 Stream2a4a60;
typedef struct {
    char pad0[24];
    void (*read)(Stream2a4a60 *, int, int, int *);
    void (*end)(Stream2a4a60 *, int, int *);
    void (*skip)(Stream2a4a60 *, int, int *);
} StreamOps2a4a60;
struct Stream2a4a60 {
    StreamOps2a4a60 *ops;
};

int FUN_0028dc78(int);
void FUN_002a4b20(int, int);

void FUN_002a4a60(int ctx, Stream2a4a60 *s) {
    int buf[4];

    for (;;) {
        s->ops->read(s, 1, 4, buf);
        if (buf[1] != 4 || FUN_0028dc78(buf[0]) != 128) {
            break;
        }
        s->ops->skip(s, 0, buf);
        FUN_002a4b20(ctx, 4);
    }
    s->ops->end(s, 1, buf);
}
