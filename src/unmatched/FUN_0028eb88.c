typedef int (*Callback0028eb88)(void *arg);

struct Cb0028eb88 {
    Callback0028eb88 fn;
    void *arg;
    int flag;
};

int FUN_0028eb88(struct Cb0028eb88 *cb, int flag) {
    cb->flag = flag;
    if (flag != 0) {
        flag = (int)cb->fn;
        if (flag != 0) {
            flag = cb->fn(cb->arg);
        }
    }
    return flag;
}
