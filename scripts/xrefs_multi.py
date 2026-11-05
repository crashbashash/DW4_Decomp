# xrefs_multi.py — dump incoming xrefs for several addresses in one session.
#
#   pyghidra-run <binary> -postScript xrefs_multi.py \
#       --targets 0x512330,0x5122c8,0x519200,0x51b608 --out xrefs.json
#
# @category PS2
# @runtime PyGhidra

import json
import typing

if typing.TYPE_CHECKING:
    from typing import Any
    currentProgram: Any = None
    getScriptArgs: Any = None
    toAddr: Any = None


def _hex(addr):
    return f"0x{addr.getOffset():08x}"


def main():
    args = list(getScriptArgs())
    targets, out_path = None, None
    i = 0
    while i < len(args):
        if args[i] == "--targets" and i + 1 < len(args):
            targets = [t.strip() for t in args[i + 1].split(",") if t.strip()]
            i += 2
        elif args[i] in ("--out", "-o") and i + 1 < len(args):
            out_path = args[i + 1]
            i += 2
        else:
            i += 1
    if not targets:
        raise SystemExit("xrefs_multi: --targets addr,addr,... required")

    ref_manager = currentProgram.getReferenceManager()
    func_manager = currentProgram.getFunctionManager()
    sym_table = currentProgram.getSymbolTable()

    result = {}
    for t in targets:
        addr = toAddr(int(t, 16))
        entries = []
        for ref in ref_manager.getReferencesTo(addr):
            frm = ref.getFromAddress()
            func = func_manager.getFunctionContaining(frm)
            entry = {
                "from": _hex(frm),
                "type": str(ref.getReferenceType()),
                "function": func.getName() if func else None,
            }
            # try to get a symbol at the from address for context
            syms = sym_table.getSymbols(frm)
            if syms:
                entry["symbol"] = syms[0].getName()
            entries.append(entry)
        result[t] = entries
        print(f"{t}: {len(entries)} incoming refs")

    text = json.dumps(result, indent=2)
    if out_path:
        with open(out_path, "w", encoding="utf-8") as fh:
            fh.write(text)
        print(f"wrote {out_path}")
    else:
        print(text)


main()
