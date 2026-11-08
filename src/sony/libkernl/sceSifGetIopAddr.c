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

int sceSifGetIopAddr(unsigned int id, void *value, unsigned int type)
{
    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if (type >= 3) {
        return 0xFFFEFFFE;
    }
    D_00559440.head.w = id;
    D_00559440.type = type;
    if (FUN_0010e2a8(D_00559640, 3, 0, &D_00559440, 32, &D_00559440, 32, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    if (type == 0) {
        *(unsigned char *)value = D_00559440.head.b;
    } else if (type == 1) {
        *(unsigned short *)value = D_00559440.head.h;
    } else if (type == 2) {
        *(unsigned int *)value = D_00559440.head.w;
    } else {
        return 0xFFFEFFFE;
    }
    return 0;
}
