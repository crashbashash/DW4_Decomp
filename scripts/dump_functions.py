# dump_functions.py — dump the current Ghidra program's full function list.
#
# PyGhidra (CPython 3) GhidraScript using the FlatProgramAPI's function
# manager. Run through the pyghidra-run wrapper, which preserves the
# analyzeHeadless-style `-postScript` invocation:
#
#   pyghidra-run <binary> -postScript dump_functions.py --out functions.json
#   pyghidra-run <binary> -postScript dump_functions.py --out functions.txt --format txt
#
# Args: --out PATH (default stdout), --format json|txt (default json).
# Prints a one-line summary to stdout when --out is given.
#
# @category PS2
# @runtime PyGhidra

import json
import typing

if typing.TYPE_CHECKING:
    # PyGhidra injects `currentProgram` and `getScriptArgs` into the script
    # globals at runtime; declared here only for static analysis. Never assign
    # to these at runtime — PyGhidra's globals mapping treats them as readonly.
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
    if fmt not in ("json", "txt"):
        raise SystemExit("dump_functions: --format must be 'json' or 'txt'")
    return out_path, fmt


def _hex(addr):
    return f"0x{addr.getOffset():08x}"


def _prototype(func):
    try:
        return func.getPrototypeString(False, False)
    except Exception as exc:  # noqa: BLE001 - never abort the dump on a bad prototype
        print(f"dump_functions: prototype unavailable for {func.getName()}: {exc}")
        return "<unknown>"


def _size(func):
    try:
        body = func.getBody()
        return int(body.getNumAddresses()) if body is not None else 0
    except Exception as exc:  # noqa: BLE001 - malformed bodies must not abort the dump
        print(f"dump_functions: body unavailable for {func.getName()}: {exc}")
        return 0


def _write(path, text):
    try:
        with open(path, "w", encoding="utf-8") as handle:
            handle.write(text)
    except OSError as exc:
        raise SystemExit(f"dump_functions: cannot write {path}: {exc}") from exc


def main():
    out_path, fmt = _parse_args(list(getScriptArgs()))

    functions = []
    for func in currentProgram.getFunctionManager().getFunctions(True):
        functions.append(
            {
                "address": _hex(func.getEntryPoint()),
                "name": func.getName(),
                "signature": _prototype(func),
                "size": _size(func),
                "thunk": bool(func.isThunk()),
                "external": bool(func.isExternal()),
            }
        )
    functions.sort(key=lambda f: int(f["address"], 16))

    if fmt == "txt":
        text = "".join(
            f"{f['address']}  {f['name']:<40}  {f['signature']}\n" for f in functions
        )
    else:
        text = (
            json.dumps(
                {
                    "program": currentProgram.getName(),
                    "language": currentProgram.getLanguageID().toString(),
                    "count": len(functions),
                    "functions": functions,
                },
                indent=2,
            )
            + "\n"
        )

    if out_path:
        _write(out_path, text)
        print(f"dump_functions: {len(functions)} functions -> {out_path}")
    else:
        print(text, end="")


if __name__ == "__main__":
    main()
