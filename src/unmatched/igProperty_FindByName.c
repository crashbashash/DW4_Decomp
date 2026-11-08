int strcmp();
struct L { char pad[8]; int n; int p12; int *arr; };
struct P { char pad[8]; int off; };
int igProperty_FindByName(struct L *arg0, struct P *arg1, int arg2) {
    int temp_a0;
    int var_s2;
    int temp_s1;
    int temp_s0;
    if ((arg1 == 0) || (arg2 == 0)) {
        return 0;
    }
    temp_s1 = arg0->n;
    for (var_s2 = 0; var_s2 < temp_s1; var_s2++) {
        temp_s0 = arg0->arr[var_s2];
        temp_a0 = *(int *)(temp_s0 + arg1->off);
        if ((temp_a0 != 0) && (strcmp(temp_a0, arg2) == 0)) {
            return temp_s0;
        }
    }
    return 0;
}
