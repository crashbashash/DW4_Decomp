typedef struct Stream Stream;
typedef struct {
    char pad0[24];
    void (*read)(Stream *, int, int, int *);
    void (*end)(Stream *, int, int *);
    void (*skip)(Stream *, int, int *);
} StreamOps;
struct Stream {
    StreamOps *ops;
};

int FUN_0029e160(Stream *s, int flag, int size) {
    int buf[4];
    int other = flag == 0;

    s->ops->read(s, flag, size, buf);
    s->ops->skip(s, other, buf);
    return buf[1];
}
