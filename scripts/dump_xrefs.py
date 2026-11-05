# dump_xrefs.py — dump cross-references into and/or out of a target.
#
# PyGhidra (CPython 3) GhidraScript. The target may be a hex address
# (`0x00123456`) or a symbol/function name. Incoming references come from the
# reference manager; outgoing references are every reference from the
# instructions of the function containing the target (or from the target
# address itself when it is not inside a function).
#
#   pyghidra-run <binary> -postScript dump_xrefs.py --target 0x00100000 --out xrefs.json
#   pyghidra-run <binary> -postScript dump_xrefs.py --target strlen_stub \
#       --direction in --format txt
#
# Args: --target (required), --direction in|out|both (default both),
#       --out PATH (default stdout), --format json|txt (default json).
#
# @category PS2
# @runtime PyGhidra

import json
import typing

if typing.TYPE_CHECKING:
    # Injected into the script globals by PyGhidra at runtime; declared here
    # only for static analysis. Never assign to these at runtime.
    from typing import Any

    currentProgram: Any = None
    getScriptArgs: Any = None
    toAddr: Any = None


def _parse_args(argv):
    target, direction, out_path, fmt = None, "both", None, "json"
    i = 0
    while i < len(argv):
        arg = argv[i]
        if arg == "--target" and i + 1 < len(argv):
            target = argv[i + 1]
            i += 2
        elif arg == "--direction" and i + 1 < len(argv):
            direction = argv[i + 1].lower()
            i += 2
        elif arg in ("--out", "-o") and i + 1 < len(argv):
            out_path = argv[i + 1]
            i += 2
        elif arg == "--format" and i + 1 < len(argv):
            fmt = argv[i + 1].lower()
            i += 2
        else:
            i += 1
    if target is None:
        raise SystemExit("dump_xrefs: --target <address|symbol> is required")
    if direction not in ("in", "out", "both"):
        raise SystemExit("dump_xrefs: --direction must be 'in', 'out' or 'both'")
    if fmt not in ("json", "txt"):
        raise SystemExit("dump_xrefs: --format must be 'json' or 'txt'")
    return target, direction, out_path, fmt


def _hex(addr):
    return f"0x{addr.getOffset():08x}"


def _resolve(target):
    """Resolve a hex address or a function/symbol name to an Address."""
    text = target.strip()
    if text.lower().startswith("0x"):
        try:
            return toAddr(int(text, 16))
        except ValueError as exc:
            raise SystemExit(f"dump_xrefs: invalid address {target!r}: {exc}") from exc

    function_manager = currentProgram.getFunctionManager()
    for func in function_manager.getFunctions(True):
        if func.getName() == text:
            return func.getEntryPoint()

    try:
        symbols = list(currentProgram.getSymbolTable().getSymbols(text))
    except Exception as exc:  # noqa: BLE001 - symbol lookup is best-effort
        print(f"dump_xrefs: symbol lookup for {text!r} failed: {exc}")
        symbols = []
    if symbols:
        return symbols[0].getAddress()

    raise SystemExit(
        f"dump_xrefs: cannot resolve target {target!r} (no such address/function/symbol)"
    )


def _refs_to(addr):
    ref_manager = currentProgram.getReferenceManager()
    return [
        {
            "direction": "in",
            "from": _hex(ref.getFromAddress()),
            "to": _hex(addr),
            "type": str(ref.getReferenceType()),
            "mnemonic": "",
        }
        for ref in ref_manager.getReferencesTo(addr)
    ]


def _refs_from(addr):
    ref_manager = currentProgram.getReferenceManager()
    listing = currentProgram.getListing()
    func = currentProgram.getFunctionManager().getFunctionContaining(addr)

    entries = []
    if func is not None:
        instructions = listing.getInstructions(func.getBody(), True)
    else:
        instructions = listing.getInstructions(addr, True)

    for ins in instructions:
        for ref in ref_manager.getReferencesFrom(ins.getAddress()):
            entries.append(
                {
                    "direction": "out",
                    "from": _hex(ins.getAddress()),
                    "to": _hex(ref.getToAddress()),
                    "type": str(ref.getReferenceType()),
                    "mnemonic": str(ins.getMnemonicString()),
                }
            )
    return entries


def _write(path, text):
    try:
        with open(path, "w", encoding="utf-8") as handle:
            handle.write(text)
    except OSError as exc:
        raise SystemExit(f"dump_xrefs: cannot write {path}: {exc}") from exc


def main():
    target, direction, out_path, fmt = _parse_args(list(getScriptArgs()))
    address = _resolve(target)

    references = []
    if direction in ("in", "both"):
        references.extend(_refs_to(address))
    if direction in ("out", "both"):
        references.extend(_refs_from(address))

    if fmt == "txt":
        lines = [
            f"{r['direction']:<3} {r['from']} -> {r['to']}  {r['type']}"
            + (f"  [{r['mnemonic']}]" if r["mnemonic"] else "")
            for r in references
        ]
        text = "\n".join(lines) + ("\n" if lines else "")
    else:
        text = (
            json.dumps(
                {
                    "program": currentProgram.getName(),
                    "language": currentProgram.getLanguageID().toString(),
                    "target": _hex(address),
                    "direction": direction,
                    "count": len(references),
                    "references": references,
                },
                indent=2,
            )
            + "\n"
        )

    if out_path:
        _write(out_path, text)
        print(
            f"dump_xrefs: {len(references)} references for {_hex(address)} ({direction}) -> {out_path}"
        )
    else:
        print(text, end="")


if __name__ == "__main__":
    main()
