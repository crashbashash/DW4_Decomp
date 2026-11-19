/* Default slot 21: constant 4. */
int Gap__Core__igObject__vfunc_21(void)
{
    return 4;
}

int FUN_00142bb0(igObjectList *list, igObject *const *key) {
    int mid;
    int lo;
    int hi;
    unsigned b;
    unsigned a;
    int cnt;
    lo = 0;
    cnt = list->_count;
    hi = cnt - 1;
    while (lo < hi) {
        b = (unsigned)*key;
        mid = (lo + hi) >> 1;
        a = ((unsigned *)list->_data)[mid];
        if (a < b) {
            lo = mid + 1;
        } else if (b < a) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (!cnt) {
        return 0;
    }
    return ((unsigned *)list->_data)[lo] < (unsigned)*key ? 1 + lo : lo;
}

