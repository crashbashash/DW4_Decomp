typedef struct { int pad[5]; int a; int b; } S;
extern S _sif_cmd_data;
int FUN_0010d498(int arg0, int arg1) {
    S *p = &_sif_cmd_data;
    int r = p->a;
    p->a = arg0;
    p->b = arg1;
    return r;
}
