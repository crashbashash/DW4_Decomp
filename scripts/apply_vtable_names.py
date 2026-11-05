# apply_vtable_names.py — apply the RTTI/vtable names recovered by
# dump_vtables.py to the current Ghidra program.
#
#   pyghidra-run <binary> --project-path ghidra-projects/dw4 \
#       --project-name dw4 --no-analysis -postScript apply_vtable_names.py \
#       --vtables ghidra-projects/dw4/vtables.json \
#       [--apply]
#
# Dry-run by default: reports what would change and writes --report JSON
# without mutating the program. Pass --apply to commit.
#
# What it does, in order:
#   1. Creates a function at every vfunc address that has none (the 16-byte
#      `jr ra` default stubs are frequently missed by auto-analysis).
#   2. Renames functions whose name is still an auto-analysis placeholder
#      (`FUN_*`, `thunk_FUN_*`, `LAB_*`, `SUB_*`, `undefined*`). A function
#      with any other name is left alone and reported: prior analysis outranks
#      a derived vfunc name.
#   3. Labels each `__RTTI__` record and each `__vt__` header with its class
#      name, and puts the class name in the vtable header's plate comment.
#
# Args:
#   --vtables PATH   dump_vtables.py output (required)
#   --apply          commit the changes (default: dry run)
#   --report PATH    write a JSON report of every action taken
#
# @category PS2
# @runtime PyGhidra

import json
import re
import typing

if typing.TYPE_CHECKING:
    from typing import Any

    currentProgram: Any = None
    getScriptArgs: Any = None

# Names auto-analysis generates and that therefore carry no information.
_PLACEHOLDER = re.compile(
    r"^(?:FUN_|thunk_FUN_|LAB_|SUB_|undefined|UNK_|DAT_|PTR_)"
)

# Ghidra's label validator is stricter than Function.setName and rejects
# template punctuation (`<`, `>`, `*`, `,`). Labels only need to be unique and
# findable, so collapse everything outside the safe set.
_LABEL_UNSAFE = re.compile(r"[^A-Za-z0-9_:.]")
_OURS = ("__RTTI__", "__vt__")

# A name this tool derived (`<Class>::vfunc_NN`). Re-asserting these is safe and
# necessary: renaming a thunk's target makes Ghidra propagate the target's name
# onto the thunk, which can clobber a name we gave the thunk directly.
_DERIVED = re.compile(r"::vfunc_\d+$")


def _label_safe(name):
    return _LABEL_UNSAFE.sub("_", name)


def _args(argv):
    vtables = None
    apply = False
    report = None
    i = 0
    while i < len(argv):
        a = argv[i]
        if a == "--vtables" and i + 1 < len(argv):
            vtables = argv[i + 1]
            i += 2
        elif a == "--report" and i + 1 < len(argv):
            report = argv[i + 1]
            i += 2
        elif a == "--apply":
            apply = True
            i += 1
        else:
            i += 1
    if not vtables:
        raise SystemExit("apply_vtable_names: --vtables PATH is required")
    return vtables, apply, report


def _main():
    vtables_path, apply, report_path = _args(list(getScriptArgs()))
    with open(vtables_path, encoding="utf-8") as fh:
        data = json.load(fh)

    from ghidra.program.model.symbol import SourceType

    fm = currentProgram.getFunctionManager()
    af = currentProgram.getAddressFactory().getDefaultAddressSpace()

    def addr(hex_s):
        return af.getAddress(hex_s)

    report = {
        "apply": apply,
        "named": [],
        "created": [],
        "renamed": [],
        "kept_existing": [],
        "uncreatable": [],
        "ambiguous_reset": [],
        "labels": [],
        "label_conflicts": [],
    }

    # --- 1 & 2. functions ------------------------------------------------
    # Targets before thunks: renaming a function makes Ghidra propagate the new
    # name to every thunk that jumps to it, which would clobber a vfunc name
    # already given to a thunk (one that a class's vtable points at directly).
    def _is_thunk(hex_addr):
        func = fm.getFunctionAt(addr(hex_addr))
        return bool(func is not None and func.isThunk())

    ordered = sorted(data["names"].items(), key=lambda kv: int(kv[0], 16))
    ordered.sort(key=lambda kv: _is_thunk(kv[0]))
    for hex_addr, info in ordered:
        a = addr(hex_addr)
        name = info["name"]
        func = fm.getFunctionAt(a)
        if func is None:
            if not apply:
                report["created"].append({"addr": hex_addr, "name": name})
                continue
            created = createFunction(a, name)
            if created is None:
                containing = fm.getFunctionContaining(a)
                report["uncreatable"].append(
                    {
                        "addr": hex_addr,
                        "name": name,
                        "inside": str(containing.getEntryPoint()) if containing else None,
                    }
                )
                continue
            report["created"].append({"addr": hex_addr, "name": name})
            report["named"].append({"addr": hex_addr, "name": name})
            continue

        current = func.getName()
        derived = bool(_DERIVED.match(current))
        if _PLACEHOLDER.match(current) or derived:
            if apply:
                func.setName(name, SourceType.ANALYSIS)
            report["renamed"].append(
                {"addr": hex_addr, "from": current, "to": name}
            )
            report["named"].append({"addr": hex_addr, "name": name})
        else:
            report["kept_existing"].append(
                {"addr": hex_addr, "existing": current, "proposed": name}
            )

    # --- 2b. demote ambiguous shared defaults ----------------------------
    # These were named on an earlier run under a rule that could hand the same
    # `<Class>::vfunc_NN` to several distinct bodies. The owner turns out to be
    # an intermediate base with no emitted vtable, so no correct name is
    # available; a duplicate symbol is worse than an honest default, so reset
    # the name and keep the knowledge in a comment.
    for item in data.get("ambiguous", []):
        a = addr(item["addr"])
        func = fm.getFunctionAt(a)
        if func is None:
            continue
        current = func.getName()
        if "::vfunc_" not in current:
            report["kept_existing"].append(
                {"addr": item["addr"], "existing": current, "proposed": None}
            )
            continue
        refs = item["refs"]
        shown = ", ".join(c for c, _ in refs[:6])
        if len(refs) > 6:
            shown += f" (+{len(refs) - 6} more)"
        note = (
            f"shared default, slot {item['slot']}\n"
            f"{len(refs)} vtables share this body; its owner is an intermediate\n"
            f"base with no emitted vtable ({item['resolved_owner']} is only the\n"
            f"deepest ancestor that has one). Left unnamed on purpose: any name\n"
            f"here would duplicate the widest group's.\n"
            f"referrers: {shown}"
        )
        report["ambiguous_reset"].append(
            {"addr": item["addr"], "was": current, "slot": item["slot"], "refs": len(refs)}
        )
        if apply:
            try:
                func.setName(None, SourceType.DEFAULT)
            except Exception:  # noqa: BLE001 - fall back to an explicit default
                func.setName(f"FUN_{a.getOffset():08x}", SourceType.DEFAULT)
            try:
                setPlateComment(a, note)
            except Exception:  # noqa: BLE001
                pass

    # --- 3. RTTI records and vtable headers ------------------------------
    def label(a, name, kind):
        name = _label_safe(name)
        existing = currentProgram.getSymbolTable().getPrimarySymbol(a)
        if existing is not None:
            current = existing.getName()
            if current == name:
                return
            if not (_PLACEHOLDER.match(current) or current.startswith(_OURS)):
                report["label_conflicts"].append(
                    {
                        "addr": str(a),
                        "kind": kind,
                        "existing": current,
                        "proposed": name,
                    }
                )
                return
            # Replacing a label we created earlier in a previous run.
            if apply:
                try:
                    existing.delete()
                except Exception as exc:  # noqa: BLE001
                    report["label_conflicts"].append(
                        {"addr": str(a), "kind": kind, "error": str(exc)}
                    )
                    return
        report["labels"].append({"addr": str(a), "kind": kind, "name": name})
        if apply:
            try:
                createLabel(a, name, True)
            except Exception as exc:  # noqa: BLE001 - never abort on one label
                report["label_conflicts"].append(
                    {"addr": str(a), "kind": kind, "name": name, "error": str(exc)}
                )

    for hex_rec, info in sorted(data["rtti"].items(), key=lambda kv: int(kv[0], 16)):
        label(addr(hex_rec), f"__RTTI__{info['name']}", "rtti")

    for hex_vt, info in sorted(data["vtables"].items(), key=lambda kv: int(kv[0], 16)):
        a = addr(hex_vt)
        label(a, f"__vt__{info['class']}", "vtable")
        if apply:
            try:
                setPlateComment(
                    a,
                    f"__vt__{info['class']}\n"
                    f"RTTI record: {info['rtti']}\n"
                    f"base class: "
                    f"{data['rtti'].get(info['rtti'], {}).get('base_name') or '(root)'}\n"
                    f"{len(info['vfuncs'])} virtual slots",
                )
            except Exception as exc:  # noqa: BLE001
                report["label_conflicts"].append(
                    {"addr": str(a), "kind": "plate", "error": str(exc)}
                )

    summary = {
        k: len(report[k])
        for k in (
            "created",
            "renamed",
            "kept_existing",
            "uncreatable",
            "ambiguous_reset",
            "labels",
            "label_conflicts",
        )
    }
    report["summary"] = summary
    if report_path:
        with open(report_path, "w", encoding="utf-8") as fh:
            json.dump(report, fh, indent=1)
    mode = "APPLIED" if apply else "DRY RUN"
    print(
        f"apply_vtable_names [{mode}]: "
        f"{len(data['names'])} candidate names -> "
        f"{summary['created']} created, {summary['renamed']} renamed, "
        f"{summary['kept_existing']} kept existing, "
        f"{summary['uncreatable']} uncreatable, "
        f"{summary['ambiguous_reset']} ambiguous reset, "
        f"{summary['labels']} labels (+{summary['label_conflicts']} conflicts)"
    )


def main():
    import traceback

    try:
        _main()
    except BaseException:
        traceback.print_exc()
        raise


main()
