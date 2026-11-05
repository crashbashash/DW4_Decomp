"""cc.py — the command line that turns one C file into an object.

MWCC builds run under wibo as `<wibo> <mwccps2.exe> -c <flags> <source> -o <object>`. A unit pinned to
the Sony EE GCC (`config/SLUS-20836/unit-compilers.tsv` names an `ee-gcc` executable) runs natively through
tools/eegcc_compile.py instead. Every compile site (verify, check, linkgen) builds its command here.
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))


def is_eegcc(compiler):
    return os.path.basename(str(compiler)) == "ee-gcc"


def compile_argv(wibo, compiler, flags, source, out):
    """argv for one compile; `flags` is the flag string of the unit."""
    if is_eegcc(compiler):
        return [sys.executable, os.path.join(HERE, "eegcc_compile.py"), str(compiler),
                *flags.split(), source, out]
    return [wibo, compiler, "-c", *flags.split(), source, "-o", out]
