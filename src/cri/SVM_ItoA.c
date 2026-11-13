/* Decimal conversion with a size limit: writes the digits of `value` into buf, then copies the
 * work string svm_itoa_work into buf in reverse, at most size - 1 bytes, and terminates it. */
unsigned int strlen(const char *s);

extern char svm_itoa_work[];

void SVM_ItoA(long value, char *buf, long size) {
    long i;
    long len;

    for (i = 0; i < 32; i++) {
        buf[i] = value % 10;
        value /= 10;
        if (value == 0) {
            buf[i] = 0;
            break;
        }
    }
    len = strlen(svm_itoa_work);
    if (len >= size - 1) {
        len = size - 1;
    }
    for (i = 0; i < len; i++) {
        buf[i] = svm_itoa_work[len - 1 - i];
    }
    buf[i] = 0;
}
