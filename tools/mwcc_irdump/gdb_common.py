"""gdb_common.py: start the compiler under gdb and wait until its image is loaded (imported by the gdb_*.py scripts).

The scripts run as `gdb -q -batch -x tools/mwcc_irdump/gdb_<name>.py --args local/wibo <mwccps2.exe> -c ...`.
wibo maps the Windows image itself, so a breakpoint in the compiler can only be set once the image's bytes are in
memory: the compiler is stopped at every `openat` until the bytes at a known address equal the executable's, which is
long before it opens the source file.
"""
import os
import shlex
import sys

import gdb

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import b52  # noqa: E402


def setting(command):
    try:
        gdb.execute(command)
    except gdb.error:
        pass


def start(probe):
    """Run the inferior until the compiler image is mapped; return the inferior. `probe` is a VA in `.text`."""
    for command in ("set pagination off", "set confirm off", "set debuginfod enabled off"):
        setting(command)
    args = shlex.split(gdb.parameter("args") or "")
    if not args or b52.known_builds().get(b52.sha256(args[0])) is None:
        raise gdb.GdbError("the first argument after the loader must be the 3.0b52-030722 compiler or its dump copy")
    with open(args[0], "rb") as fh:
        fh.seek(b52.file_offset(probe))
        expected = fh.read(4)
    gdb.execute("catch syscall openat")
    gdb.execute("run")
    inferior = gdb.selected_inferior()
    while True:
        try:
            if inferior.read_memory(probe, 4).tobytes() == expected:
                break
        except gdb.MemoryError:
            pass
        gdb.execute("continue")
    gdb.execute("delete")
    return inferior


def reader(inferior):
    def rd(address, size):
        return int.from_bytes(inferior.read_memory(address, size).tobytes(), "little")
    return rd


def esp():
    return int(gdb.parse_and_eval("$rsp")) & 0xFFFFFFFF


def register(name):
    return int(gdb.parse_and_eval("$" + name)) & 0xFFFFFFFF


def finish(out):
    out.close()
    try:
        gdb.execute("kill")
    except gdb.error:
        pass
