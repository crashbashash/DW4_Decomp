# dump_strings.py — dump the string table with incoming cross-references.
#
# PyGhidra (CPython 3) GhidraScript. Enumerates defined string data in the
# current program and lists every reference to each string, so candidate
# game-state strings can be traced back to the code that uses them.
#
#   pyghidra-run <binary> -postScript dump_strings.py --out strings.json
#   pyghidra-run <binary> -postScript dump_strings.py --out strings.txt --format txt
#
# Args: --out PATH (default stdout), --format json|txt (default json),
#       --min-length N (default 4; shorter strings are skipped).
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
    out_path, fmt, min_length = None, "json", 4
    i = 0
    while i < len(argv):
        arg = argv[i]
        if arg in ("--out", "-o") and i + 1 < len(argv):
            out_path = argv[i + 1]
            i += 2
        elif arg == "--format" and i + 1 < len(argv):
            fmt = argv[i + 1].lower()
            i += 2
        elif arg == "--min-length" and i + 1 < len(argv):
            try:
                min_length = int(argv[i + 1])
            except ValueError as exc:
                raise SystemExit(
                    f"dump_strings: --min-length must be an integer: {exc}"
                ) from exc
            i += 2
        else:
            i += 1
    if fmt not in ("json", "txt"):
        raise SystemExit("dump_strings: --format must be 'json' or 'txt'")
    return out_path, fmt, min_length


def _hex(addr):
    return f"0x{addr.getOffset():08x}"


def _string_value(data):
    """Return the string value of a defined data item, or None."""
    try:
        if not data.hasStringValue():
            return None
        return str(data.getValue())
    except Exception as exc:  # noqa: BLE001 - skip unreadable data items
        print(
            f"dump_strings: skipping unreadable data at {_hex(data.getAddress())}: {exc}"
        )
        return None


def _write(path, text):
    try:
        with open(path, "w", encoding="utf-8") as handle:
            handle.write(text)
    except OSError as exc:
        raise SystemExit(f"dump_strings: cannot write {path}: {exc}") from exc


def main():
    out_path, fmt, min_length = _parse_args(list(getScriptArgs()))

    listing = currentProgram.getListing()
    ref_manager = currentProgram.getReferenceManager()

    strings = []
    for data in listing.getDefinedData(True):
        value = _string_value(data)
        if value is None or len(value) < min_length:
            continue
        xrefs = [
            {
                "from": _hex(ref.getFromAddress()),
                "type": str(ref.getReferenceType()),
            }
            for ref in ref_manager.getReferencesTo(data.getAddress())
        ]
        strings.append(
            {
                "address": _hex(data.getAddress()),
                "value": value,
                "length": len(value),
                "xrefs": xrefs,
            }
        )
    strings.sort(key=lambda s: int(s["address"], 16))

    if fmt == "txt":
        lines = []
        for item in strings:
            lines.append(f"{item['address']}  {item['value']!r}")
            for xref in item["xrefs"]:
                lines.append(f"    <- {xref['from']}  ({xref['type']})")
        text = "\n".join(lines) + ("\n" if lines else "")
    else:
        text = (
            json.dumps(
                {
                    "program": currentProgram.getName(),
                    "language": currentProgram.getLanguageID().toString(),
                    "count": len(strings),
                    "strings": strings,
                },
                indent=2,
            )
            + "\n"
        )

    if out_path:
        _write(out_path, text)
        print(f"dump_strings: {len(strings)} strings -> {out_path}")
    else:
        print(text, end="")


if __name__ == "__main__":
    main()
