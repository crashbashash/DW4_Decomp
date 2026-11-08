typedef int (*Callback0028d8e0)(void *arg);

struct Cb0028d8e0 {
    Callback0028d8e0 fn;
    void *arg;
    int flag;
};

int FUN_0028d8e0(struct Cb0028d8e0 *cb, int flag) {
    cb->flag = flag;
    if (flag != 0) {
        flag = (int)cb->fn;
        if (flag != 0) {
            flag = cb->fn(cb->arg);
        }
    }
    return flag;
}
