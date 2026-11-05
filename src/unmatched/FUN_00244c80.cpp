extern "C" {
struct N;
struct N *FUN_002413f0(...);
struct N *FUN_00241550(...);
int FUN_002467a0(...);
int lua_type(...);
int lua_tag(...);
int lua_tostring(...);
int lua_touserdata(...);
int lua_pushusertag(...);
extern int DAT_004ea910[4];
extern int DAT_004ea940[4];
int FUN_00244c80(int arg0);
}
struct N { char pad[20]; struct N *f20; char pad2[16]; int f40; int f44; };
int FUN_00244c80(int arg0) {
    int temp_s1;
    int temp_v0_3;
    bool var_a0;
    int var_a2;
    struct N *temp_v0;
    struct N *temp_v0_2;
    struct N *var_v1;
    struct N *var_v1_2;

    if (lua_type(arg0, 1) != 3) {
        FUN_002467a0(&DAT_004ea910[0]);
    }
    if (lua_type(arg0, 2) != 0) {
        FUN_002467a0(&DAT_004ea940[0]);
    }
    temp_s1 = lua_tostring(arg0, 1);
    temp_v0 = FUN_00241550(lua_tag(arg0, 2));
    if (temp_v0 == 0) {
        return 0;
    }
    temp_v0_2 = FUN_002413f0(temp_s1);
    if (temp_v0_2 == 0) {
        return 0;
    }
    temp_v0_3 = lua_touserdata(arg0, 2);
    var_a0 = 0;
    var_v1 = temp_v0_2;
    while (var_v1 != 0) {
        if (var_v1 == temp_v0) {
            var_a0 = 1;
        }
        var_v1 = var_v1->f20;
    }
    var_v1_2 = temp_v0_2;
    if (!(int)var_a0) {
        while (var_v1_2 != 0) {
            if (var_v1_2 == temp_v0) {
                var_a0 = 1;
            }
            var_v1_2 = var_v1_2->f20;
        }
    }
    if (!(int)var_a0) {
        return 0;
    }
    if (temp_v0->f40 != 0) {
        var_a2 = temp_v0_2->f40;
    } else {
        var_a2 = temp_v0_2->f44;
    }
    lua_pushusertag(arg0, temp_v0_3, var_a2);
    return 1;
}
