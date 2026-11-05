# decompile_funcs.py — decompile one or more functions by address from the
# current Ghidra program and write their C to a text file.
#
#   pyghidra-run <binary> --project-path ghidra-projects/dw4 \
#       --project-name dw4 -postScript decompile_funcs.py \
#       --addr 0x3d50c0 --addr 0x384c40 [--addr ...] --out /tmp/decomp.txt
#
# Args:
#   --addr ADDR      repeatable; accepts 0x-prefixed hex or decimal
#   --addr-file PATH one address per line (# comments allowed)
#   --out PATH       default stdout
#   --timeout SEC    decompiler timeout per function (default 60)
#
# @category PS2
# @runtime PyGhidra

import typing

if typing.TYPE_CHECKING:
    from typing import Any

    currentProgram: Any = None
    getScriptArgs: Any = None


def _args(argv):
    addrs, addr_file, out_path, timeout = [], None, None, 60
    i = 0
    while i < len(argv):
        a = argv[i]
        if a in ("--addr", "-a") and i + 1 < len(argv):
            addrs.append(argv[i + 1]); i += 2
        elif a == "--addr-file" and i + 1 < len(argv):
            addr_file = argv[i + 1]; i += 2
        elif a in ("--out", "-o") and i + 1 < len(argv):
            out_path = argv[i + 1]; i += 2
        elif a == "--timeout" and i + 1 < len(argv):
            timeout = int(argv[i + 1]); i += 2
        else:
            i += 1
    if addr_file:
        with open(addr_file) as fh:
            for line in fh:
                line = line.split("#", 1)[0].strip()
                if line:
                    addrs.append(line)
    return addrs, out_path, timeout


def _to_int(s):
    s = s.strip()
    return int(s, 16) if s.lower().startswith("0x") else int(s)


def main():
    addrs, out_path, timeout = _args(list(getScriptArgs()))
    if not addrs:
        print("decompile_funcs: no --addr given")
        return

    from ghidra.app.decompiler import DecompInterface
    from ghidra.util.task import ConsoleTaskMonitor
    from ghidra.program.model.address import Address

    fm = currentProgram.getFunctionManager()
    listing = currentProgram.getListing()
    dec = DecompInterface()
    dec.openProgram(currentProgram)
    monitor = ConsoleTaskMonitor()

    lines = []
    for spec in addrs:
        val = _to_int(spec)
        addr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(val)
        fn = fm.getFunctionAt(addr)
        if fn is None:
            # maybe the address is inside a function body
            fn = fm.getFunctionContaining(addr)
        if fn is None:
            lines.append("=" * 78)
            lines.append("0x%08x  <no function>" % val)
            continue
        lines.append("=" * 78)
        lines.append("%s @ 0x%08x  size=%d" % (fn.getName(), fn.getEntryPoint().getOffset(), fn.getBody().getNumAddresses()))
        res = dec.decompileFunction(fn, timeout, monitor)
        if res is None or not res.decompileCompleted():
            lines.append("<decompile failed: %s>" % (res.getErrorMessage() if res else "no result"))
            continue
        lines.append(res.getDecompiledFunction().getC())
        lines.append("")

    text = "\n".join(lines)
    if out_path:
        with open(out_path, "w") as fh:
            fh.write(text)
        print("decompile_funcs: wrote %d functions to %s" % (len(addrs), out_path))
    else:
        print(text)


main()
