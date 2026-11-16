"""cc.py — the command line that turns one C file into an object.

MWCC builds run under wibo as `<wibo> <mwccps2.exe> -c <flags> <source> -o <object>`. A unit pinned to
the Sony EE GCC (`config/SLUS-20836/unit-compilers.tsv` names an `ee-gcc` executable) runs natively through
tools/eegcc_compile.py instead. Every compile site (verify, check, linkgen) builds its command here.

A source that includes a libkernl kernel patch's bytes (`#include "tlbsrc.inc"`) gets the patch built first
and its include directory added (tools/kpatch.py).

A profile whose flags carry `-session-prelude <file>` (repository-relative, MWCC only) compiles that file and
then the unit's source in one MWCC process, as the original build compiled several files in one session: the
compiler keeps state from one file to the next (docs/build-system.md#session-preludes). The process writes each
source's object into a private folder and only the unit's object becomes `out`; this module runs itself as
`python3 tools/cc.py --session <out> <compiler argv>` for that.
"""
import atexit
import os
import shutil
import subprocess
import sys
import tempfile
import threading

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
SESSION_PRELUDE = "-session-prelude"
_scratch = None
_scratch_lock = threading.Lock()


def scratch_dir():
    """This process's private temp folder, removed when it exits; every temporary file of the tools goes here.

    A compile under wibo costs time in proportion to the entries of the folder its object is written to, so
    objects written straight to a shared /tmp slow every later compile as leftovers pile up.
    """
    global _scratch
    with _scratch_lock:
        if _scratch is None:
            _scratch = tempfile.mkdtemp(prefix="dw4-")
            atexit.register(shutil.rmtree, _scratch, ignore_errors=True)
        return _scratch


def is_eegcc(compiler):
    return os.path.basename(str(compiler)) == "ee-gcc"


def split_session_preludes(flags):
    """-> (flags without the `-session-prelude <file>` pairs, [the prelude files as written, in order]).

    Raises ValueError for a `-session-prelude` without a file."""
    tokens, preludes = flags.split(), []
    while SESSION_PRELUDE in tokens:
        i = tokens.index(SESSION_PRELUDE)
        if i + 1 >= len(tokens):
            raise ValueError("%s needs a file" % SESSION_PRELUDE)
        preludes.append(tokens[i + 1])
        del tokens[i:i + 2]
    return " ".join(tokens), preludes


def session_prelude_path(prelude, root=ROOT):
    """The file a `-session-prelude` value names (repository-relative unless absolute)."""
    return prelude if os.path.isabs(prelude) else os.path.join(root, prelude)


def compile_argv(wibo, compiler, flags, source, out):
    """argv for one compile; `flags` is the flag string of the unit."""
    import kpatch
    flags, preludes = split_session_preludes(flags)
    extra = []
    if not source.endswith(".S"):
        include = kpatch.include_dir_for(source)
        if include:
            extra = ["-I" + include]
    if is_eegcc(compiler):
        if preludes:
            raise ValueError("%s is an MWCC setting and %s is the Sony EE GCC" % (SESSION_PRELUDE, compiler))
        return [sys.executable, os.path.join(HERE, "eegcc_compile.py"), str(compiler),
                *flags.split(), *extra, source, out]
    if not preludes:
        return [wibo, compiler, "-c", *flags.split(), *extra, source, "-o", out]
    paths = [session_prelude_path(p) for p in preludes]
    stem = os.path.splitext(os.path.basename(source))[0].lower()
    if any(os.path.splitext(os.path.basename(p))[0].lower() == stem for p in paths):
        # the session folder holds one object per source name, and wibo resolves names case-insensitively
        raise ValueError("a session prelude and %s would write the same object name" % source)
    return [sys.executable, os.path.abspath(__file__), "--session", out,
            wibo, compiler, "-c", *flags.split(), *extra, *paths, source]


def run_session(out, argv):
    """Run `argv`, an MWCC command whose last argument is the unit's source (after its preludes), with a private
    output folder, and move the unit's object to `out`. -> the compiler's exit status."""
    folder = tempfile.mkdtemp(prefix="session-", dir=os.path.dirname(os.path.abspath(out)))
    try:
        status = subprocess.call([*argv, "-o", folder + "/"])
        built = os.path.join(folder, os.path.splitext(os.path.basename(argv[-1]))[0] + ".o")
        if status == 0 and os.path.exists(built):
            os.replace(built, out)
        return status
    finally:
        shutil.rmtree(folder, ignore_errors=True)


if __name__ == "__main__":
    if len(sys.argv) < 4 or sys.argv[1] != "--session":
        sys.exit("usage: cc.py --session <out> <compiler argv ending with the sources>")
    sys.exit(run_session(sys.argv[2], sys.argv[3:]))
