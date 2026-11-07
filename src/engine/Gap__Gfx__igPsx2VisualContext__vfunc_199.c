typedef struct Stk { int a; int b; int count; int c; char *data; } Stk;
typedef struct Obj { char pad[972]; Stk *s[12]; } Obj;
void List_Reserve(Stk *, int, int);

void Gap__Gfx__igPsx2VisualContext__vfunc_199(Obj *o, int k, int n) {
    switch (k) {
    case 0:
        if (n >= o->s[0]->count) List_Reserve(o->s[0], n, 64);
        break;
    case 1:
        if (n >= o->s[1]->count) List_Reserve(o->s[1], n, 64);
        break;
    case 2:
        if (n >= o->s[2]->count) List_Reserve(o->s[2], n, 64);
        break;
    case 10:
        if (n >= o->s[4]->count) List_Reserve(o->s[4], n, 64);
        if (n >= o->s[8]->count) List_Reserve(o->s[8], n, 64);
        break;
    case 11:
        if (n >= o->s[5]->count) List_Reserve(o->s[5], n, 64);
        if (n >= o->s[9]->count) List_Reserve(o->s[9], n, 64);
        break;
    case 12:
        if (n >= o->s[6]->count) List_Reserve(o->s[6], n, 64);
        if (n >= o->s[10]->count) List_Reserve(o->s[10], n, 64);
        break;
    case 13:
        if (n >= o->s[7]->count) List_Reserve(o->s[7], n, 64);
        if (n >= o->s[11]->count) List_Reserve(o->s[11], n, 64);
        break;
    }
}
