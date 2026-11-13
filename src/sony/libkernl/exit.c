/* exit.c - leaving the program: ExecPS2, LoadExecPS2, Exit and ExecOSD, which hand the kernel their
 * arguments through the kernel's argument area. */
#include "dw4/libkernl.h"

/* argv slots at the start of the argument area; the strings follow them */
#define EXEC_ARG_SLOTS 16
#define EXEC_ARGC_MAX (EXEC_ARG_SLOTS - 1)

unsigned int strlen(const char *s);
int InitTLB(void);
int _ExecPS2(void *entry, void *gp, int argc, char **argv);
void _LoadExecPS2(const char *filename, int argc, char **argv);
void _Exit(int status);
void _ExecOSD(int argc, char **argv);

extern char *_kExecArg;
extern SyscallEntry SysEntry_exit;

/* system call 90 once kCopy is installed: a copy into kernel memory */
static int Copy(void *dst, const void *src, int size)
{
    __asm__("li $3, 90\n\tsyscall");
}

static int kCopy(unsigned char *dst, unsigned char *src, unsigned int size)
{
    unsigned int i;
    for (i = 0; i < size; i++) {
        *dst++ = *src++;
    }
    return 0;
}

/* SetSyscall */
static void setup(int number, void *handler)
{
    __asm__("li $3, 116\n\tsyscall");
}

/* Writes argv[0] = filename and argv[1..argc] into the kernel's argument area; returns the copied
 * filename. */
static char *SetArg(const char *filename, int argc, char **argv)
{
    char **slot = (char **)_kExecArg;
    char *data = (char *)(slot + EXEC_ARG_SLOTS);
    char *strings = data;
    int length;
    int i;
    setup(SysEntry_exit.number, SysEntry_exit.handler);
    if (argc > EXEC_ARGC_MAX) argc = EXEC_ARGC_MAX;
    Copy(slot, &data, 4);
    slot++;
    length = strlen(filename) + 1;
    Copy(data, filename, length);
    data += length;
    for (i = 0; i < argc; i++) {
        Copy(slot, &data, 4);
        slot++;
        length = strlen(argv[i]) + 1;
        Copy(data, argv[i], length);
        data += length;
    }
    return strings;
}

static void TerminateLibrary(void)
{
    InitTLB();
}

int ExecPS2(void *entry, void *gp, int argc, char **argv)
{
    int result;
    SetArg("", argc, argv);
    TerminateLibrary();
    result = _ExecPS2(entry, gp, argc, (char **)(_kExecArg + 4));
    return result;
}

void LoadExecPS2(const char *filename, int argc, char **argv)
{
    char *name = SetArg(filename, argc, argv);
    TerminateLibrary();
    _LoadExecPS2(name, argc, (char **)(_kExecArg + 4));
}

void Exit(int status)
{
    TerminateLibrary();
    _Exit(status);
}

void ExecOSD(int argc, char **argv)
{
    SetArg("", argc, argv);
    TerminateLibrary();
    _ExecOSD(argc, (char **)(_kExecArg + 4));
}
