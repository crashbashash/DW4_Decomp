"""cc.py — the command line that turns one C file into an object.

MWCC builds run under wibo as `<wibo> <mwccps2.exe> -c <flags> <source> -o <object>`. A unit pinned to
the Sony EE GCC (`config/SLUS-20836/unit-compilers.tsv` names an `ee-gcc` executable) runs natively through
tools/eegcc_compile.py instead. Every compile site (verify, check, linkgen) builds its command here.
"""
import atexit
import os
import shutil
import sys
import tempfile
import threading

HERE = os.path.dirname(os.path.abspath(__file__))
_scratch = None
_scratch_lock = threading.Lock()


def scratch_dir():
    """This process's private temp folder, removed when it exits; every temporary file of the tools goes here.

    A compile under wibo costs time in proportion to the entries of the folder its object is written to, so
    objects written straight to a shared /tmp slow every later compile as leftovers pile up (finding #3896).
    """
    global _scratch
    with _scratch_lock:
        if _scratch is None:
            _scratch = tempfile.mkdtemp(prefix="dw4-")
            atexit.register(shutil.rmtree, _scratch, ignore_errors=True)
        return _scratch


def is_eegcc(compiler):
    return os.path.basename(str(compiler)) == "ee-gcc"


def compile_argv(wibo, compiler, flags, source, out):
    """argv for one compile; `flags` is the flag string of the unit."""
    if is_eegcc(compiler):
        return [sys.executable, os.path.join(HERE, "eegcc_compile.py"), str(compiler),
                *flags.split(), source, out]
    return [wibo, compiler, "-c", *flags.split(), source, "-o", out]
