int memcpy();
struct MemoryFileBody { char p[44]; unsigned char open; char p2[3]; char *data; int size; int pos; };

int Gap__Core__igMemoryFile__vfunc_27(struct MemoryFileBody *arg0, void *arg1, int arg2, int arg3) {
    int n; 
    int pos; 
    int left; 

    if (arg0->open == 0) {
        return -1;
    }
    pos = arg0->pos;
    n = arg2 * arg3;
    left = arg0->size - pos;
    if (left < n) {
        n = left;
    }
    if (n <= 0) {
        return 0;
    }
    memcpy(arg1, arg0->data + pos, n);
    arg0->pos += n;
    return n / arg2;
}
