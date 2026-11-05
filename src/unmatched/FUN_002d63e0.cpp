extern "C" {
int FUN_002d60b0(...);
int igStrCmp(...);
}
struct E { char pad[8]; int f8; int name; };
struct Lst { char pad[16]; struct E **arr; };
struct A { char pad[8]; struct Lst *f8; int n; };
extern "C" int FUN_002d63e0(struct A *arg0, int arg1) {
    int i;
    bool found;
    struct E *e;

    e = 0;
    if (arg0->f8 == 0) {
        FUN_002d60b0();
    }
    i = 0;
    if (arg0->n <= 0) {
        return 0;
    }
    found = true;
    while (i < arg0->n && found) {
        e = arg0->f8->arr[i];
        if (igStrCmp(e->name, arg1) == 0) {
            found = false;
        } else {
            i += 1;
        }
    }
    if ((found & 0xFF) == 1) {
        return 0;
    }
    return e->f8;
}
