# dump_symbols.py — dump EVERY named location in the Ghidra program: functions
# AND data. `dump_functions.py` gives the code layout; this gives the *addresses*
# of everything a relocation can point at, which is what a candidate C file's
# undefined symbols have to be resolved against.
#
# Why it is needed: an unlinked object stores relocations, not addresses, so
# verifying a function that touches a global requires knowing that global's retail
# address. Ghidra has them; nothing else in data/ does.
#
#   ghidra-post game.elf --project-path .../dw4 --project-name dw4 --no-analysis \
#       -postScript scripts/dump_symbols.py --out .../symbols.json
#
# Args: --out PATH (default stdout), --format json|tsv (default json).
# Prints a one-line summary to stdout when --out is given.
#
# @category PS2
# @runtime PyGhidra

import json
import typing

if typing.TYPE_CHECKING:
    from typing import Any

    currentProgram: Any = None
    getScriptArgs: Any = None


def _parse_args(argv):
    out_path, fmt = None, "json"
    i = 0
    while i < len(argv):
        arg = argv[i]
        if arg in ("--out", "-o") and i + 1 < len(argv):
            out_path = argv[i + 1]
            i += 2
        elif arg == "--format" and i + 1 < len(argv):
            fmt = argv[i + 1].lower()
            i += 2
        else:
            i += 1
    if fmt not in ("json", "tsv"):
        raise SystemExit("dump_symbols: --format must be 'json' or 'tsv'")
    return out_path, fmt


_WARNED = set()


def _warn_once(what, exc):
    if what not in _WARNED:
        _WARNED.add(what)
        print(f"dump_symbols: {what} failed: {type(exc).__name__}: {exc}")


def _kind(sym):
    """Coarse type the consumer switches on: func / data / label / external.

    Uses SymbolType (reliable across Ghidra versions) rather than probing with
    isFunction()/isExternal(), which is what made an earlier revision classify all
    98,265 symbols as 'other'.
    """
    try:
        stype = str(sym.getSymbolType())
    except Exception as exc:  # noqa: BLE001
        _warn_once("getSymbolType", exc)
        return "other"
    if stype == "Function":
        return "func"
    if stype == "Label":
        return "label"
    try:
        at = sym.getAddress()
        if at is not None and currentProgram.getListing().getDefinedDataAt(at) is not None:
            return "data"
    except Exception as exc:  # noqa: BLE001
        _warn_once("getDefinedDataAt", exc)
    return stype.lower() if stype else "other"


def _size(sym):
    """Byte extent: a function's body, or a data item's length."""
    try:
        if str(sym.getSymbolType()) == "Function":
            # FunctionSymbol has no getFunction(); go through the manager.
            fn = currentProgram.getFunctionManager().getFunctionAt(sym.getAddress())
            body = fn.getBody() if fn is not None else None
            return int(body.getNumAddresses()) if body is not None else 0
    except Exception as exc:  # noqa: BLE001
        _warn_once("function body size", exc)
    try:
        data = currentProgram.getListing().getDefinedDataAt(sym.getAddress())
        if data is not None:
            return int(data.getLength())
    except Exception as exc:  # noqa: BLE001
        _warn_once("data size", exc)
    return 0


def _write(path, text):
    try:
        with open(path, "w", encoding="utf-8") as handle:
            handle.write(text)
    except OSError as exc:
        raise SystemExit(f"dump_symbols: cannot write {path}: {exc}") from exc


def main():
    out_path, fmt = _parse_args(list(getScriptArgs()))

    rows = []
    table = currentProgram.getSymbolTable()
    for sym in table.getAllSymbols(True):
        try:
            at = sym.getAddress()
            if at is None or at.getAddressSpace().isOverlaySpace():
                continue
            rows.append({
                "address": f"0x{at.getOffset():08x}",
                "size": _size(sym),
                "name": sym.getName(True),
                "kind": _kind(sym),
            })
        except Exception as exc:  # noqa: BLE001 - keep going, report at the end
            print(f"dump_symbols: skipped a symbol: {exc}")

    # deterministic: address, then name
    rows.sort(key=lambda r: (int(r["address"], 16), r["name"]))

    counts = {}
    for r in rows:
        counts[r["kind"]] = counts.get(r["kind"], 0) + 1

    if fmt == "json":
        text = json.dumps({"counts": counts, "count": len(rows), "symbols": rows}, indent=1)
    else:
        text = "\n".join(f'{r["address"]}\t{r["size"]}\t{r["kind"]}\t{r["name"]}' for r in rows)

    if out_path:
        _write(out_path, text + "\n")
        print(f"dump_symbols: {len(rows)} symbols ({counts}) -> {out_path}")
    else:
        print(text)


main()
