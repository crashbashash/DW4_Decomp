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

void FUN_0028b0c0(int, void *, int);

int FUN_002a1fd0(Stream *s, void *dst, int size) {
    int buf[4];

    s->ops->read(s, 0, size, buf);
    FUN_0028b0c0(buf[0], dst, buf[1]);
    s->ops->skip(s, 1, buf);
    return buf[1];
}
