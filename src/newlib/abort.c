int raise(int sig);
void _exit(int status) __attribute__((noreturn));

void abort(void)
{
    for (;;) {
        raise(6);
        _exit(1);
    }
}
