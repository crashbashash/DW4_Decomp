int FUN_001005f0();
int FUN_001006d0();
int sprintf();
int strlen();
int FUN_001e3ab0();
int FUN_0023c860();
int FUN_00241f70();
int FUN_00241fe0();
int lua_settop();
int lua_pushvalue();
int lua_pushstring();
int lua_getglobals();
int lua_newtable();
int lua_rawset();
int lua_ref();
int lua_settag();
int lua_newtag();
int lua_settagmethod();
int List_InsertWords();
int lua_pushcclosure();
extern int DAT_004ea460[4];
extern int DAT_004ea660[4];
extern int DAT_004ea668[4];

int FUN_00240160();
int FUN_00240530();
int FUN_00240990();
int FUN_00240a40();
int FUN_00240bc0();
int FUN_00240de0();

struct Lst2 { int pad0[2]; int count; int pad1; int *data; };
struct Lst { int pad0[2]; int count; int pad1; int *data; };
extern struct Lst * DAT_0056de38[4];


void FUN_00242050(int *self, int ctx) {
    int mid;
    int idx;
    struct Lst *l;
    int lo;
    int e;
    int hi;
    struct Lst *l2;
    int t;
    int v;
    self[12] = lua_newtag(ctx);
    FUN_0023c860(ctx, self[3], self, self[12]);
    if (self[20] != 0) {
        t = FUN_001006d0(strlen(self[3]) + 5);
        sprintf(t, DAT_004ea660, self[3]);
        lua_getglobals(ctx);
        lua_pushstring(ctx, t);
        lua_pushcclosure(ctx, self[20], 0);
        lua_rawset(ctx, -3);
        lua_settop(ctx, -2);
        FUN_001005f0(t);
    }
    if ((void*)self[19] != 0) {
        FUN_00241f70(ctx, self, self[12], (void*)self[19], (void*)DAT_004ea460);
        self[10] = lua_newtag(ctx);
        lua_pushcclosure(ctx, self[16], 0);
        lua_settagmethod(ctx, self[10], DAT_004ea668);
        self[11] = lua_newtag(ctx);
        FUN_00241fe0(ctx, self, self[10], (void*)self[17], (void*)self[18]);
        FUN_00241fe0(ctx, self, self[11], (void*)self[17], (void*)self[18]);
        return;
    }
    if (self[4] != 0) {
        v = lua_newtag(ctx);
        self[11] = v;
        self[10] = v;
        l = DAT_0056de38[0];
        lo = 0;
        hi = l->count - 1;
        while (lo < hi) {
            mid = (lo + hi) >> 1;
            e = l->data[mid];
            if (e < self[10]) lo = mid + 1;
            else if (self[10] < e) hi = mid - 1;
            else { idx = mid; goto found; }
        }
        if (((struct Lst2 *)l)->count == 0) idx = -1;
        else {
            e = l->data[lo];
            if (self[10] < e || e < self[10]) idx = -1;
            else idx = lo;
        }
    found:
        if (idx < 0) {
            l2 = DAT_0056de38[0];
            List_InsertWords(l2, FUN_001e3ab0(l2, &self[10]), 1, &self[10]);
        }
        FUN_00241f70(ctx, self, self[10], (void*)FUN_00240530, (void*)DAT_004ea668);
        FUN_00241fe0(ctx, self, self[10], (void*)FUN_00240de0, (void*)FUN_00240bc0);
        FUN_00241f70(ctx, self, self[12], (void*)FUN_00240160, (void*)DAT_004ea460);
    } else {
        self[10] = lua_newtag(ctx);
        self[11] = lua_newtag(ctx);
        if ((void*)self[16] != 0)
            FUN_00241f70(ctx, self, self[10], (void*)self[16], (void*)DAT_004ea668);
        FUN_00241fe0(ctx, self, self[10], (void*)FUN_00240a40, (void*)FUN_00240990);
        FUN_00241fe0(ctx, self, self[11], (void*)FUN_00240a40, (void*)FUN_00240990);
    }
    lua_newtable(ctx);
    lua_settag(ctx, self[12]);
    lua_pushvalue(ctx, -1);
    self[13] = lua_ref(ctx, -1);
    FUN_00241fe0(ctx, self, self[12], (void*)FUN_00240a40, (void*)FUN_00240990);
}
