struct Layer002914d8 {
    int a;
    int b;
    int c;
};

struct Obj002914d8 {
    char pad0[944];
    int handle;                       /* +944 */
    char pad948[4];
    struct Layer002914d8 layers[4];   /* +952 */
    int w;                            /* +1000 */
    int h;                            /* +1004 */
    char rest[1];                     /* +1008 */
};

int FUN_00285160(void);
void FUN_00285368(int handle, int index, int a, int b, int c);
void FUN_00285390(int handle, int w, int h);
int FUN_002853e0(int handle, int arg);
void FUN_002853b8(int handle, int zero, void *rest);
void FUN_002915a0(struct Obj002914d8 *obj);

int FUN_002914d8(struct Obj002914d8 *obj, int arg) {
    struct Layer002914d8 *layer;
    int i;

    if (FUN_00285160() != 0) {
        for (i = 0, layer = obj->layers; i < 4; i++) {
            FUN_00285368(obj->handle, i, layer->a, layer->b, layer->c);
            layer++;
        }
        FUN_00285390(obj->handle, obj->w, obj->h);
        if (FUN_002853e0(obj->handle, arg) != 0) {
            return -2;
        }
        FUN_002853b8(obj->handle, 0, obj->rest);
        FUN_002915a0(obj);
        return 0;
    }
    return -1;
}
