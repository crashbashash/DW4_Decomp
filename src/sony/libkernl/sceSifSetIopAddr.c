typedef union {
    unsigned char b;
    unsigned short h;
    unsigned int w;
} ConfigValue;

typedef struct {
    ConfigValue head;
    int type;
    ConfigValue value;
    int pad[5];
} ConfigRequest;

int FUN_0010e2a8(void *client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, void *end_func, void *end_param);
int _lf_bind(void);
extern char D_00559640[];
extern ConfigRequest D_00559440;

int sceSifSetIopAddr(unsigned int id, void *value, int type)
{
    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    D_00559440.head.w = id;
    D_00559440.type = type;
    if (type == 0) {
        D_00559440.value.b = *(unsigned char *)value;
    } else if (type == 1) {
        D_00559440.value.h = *(unsigned short *)value;
    } else if (type == 2) {
        D_00559440.value.w = *(unsigned int *)value;
    } else {
        return 0xFFFEFFFE;
    }
    if (FUN_0010e2a8(D_00559640, 2, 0, &D_00559440, 32, &D_00559440, 16, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    return 0;
}
