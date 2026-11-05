struct LL { int p[2]; int count; int pad; int data; };
int List_BinarySearchWords(struct LL *arg0, int arg1, int (*arg2)(int, int)) {
    int lo = 0;
    int hi = arg0->count - 1;
    int mid;
    int r;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        r = arg2(arg0->data + mid * 4, arg1);
        if (r < 0) {
            lo = mid + 1;
        } else if (r > 0) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (arg0->count == 0) {
        return -1;
    }
    if (arg2(arg0->data + lo * 4, arg1) == 0) {
        return lo;
    }
    return -1;
}
