#!/usr/bin/env python3
# rename_function_data_refs.py — refer to functions by their function name.
#
#   python3 scripts/rename_function_data_refs.py [--dry-run] [--verify] [--jobs N]
#       [--only PATH] [--units LIST] [--report PATH] [PATH ...]
#
# The verifier (tools/verify.py) refuses a data-style name (`DAT_00334510`,
# `PTR_…`, `g_…_00334510`) whose embedded address is a recorded function start in
# config/SLUS-20836/symbols.txt: a function must be referenced by its function name. The
# bootstrap units that take a function's address through a Ghidra data name
# (`igMetaObject_RunStaticInit(DAT_00334510)` for `igAdx_Register`) are repaired
# here, byte-neutrally:
#
#   * every data-style identifier whose address is a function start becomes the
#     function's symbol name from config/SLUS-20836/symbols.txt (already sanitised there);
#   * its `extern char NAME[];` / `extern int NAME[4];` / `void NAME(void);`
#     declaration becomes a function prototype. A static-init callback passed to
#     igMetaObject_RunStaticInit is declared `void *NAME(void);` and the local
#     `igMetaObject_RunStaticInit(char *)` prototype becomes the project's
#     `void igMetaObject_RunStaticInit(void *(*)(void));` (src/engine/object-base-ensure.c).
#     A function the unit calls gets a prototype of the call's arity; any other
#     address-taken function is `void NAME(void); /* address-taken; signature not recovered */`;
#   * use sites stay readable: `&NAME[0]` and `&NAME` become `NAME`, casts the
#     code already had are kept, and a bare argument to a prototyped callee whose
#     parameter is an object pointer is cast to that parameter type;
#   * in a C++ unit the prototype goes inside the unit's `extern "C" {` block so
#     the relocation carries the unmangled symbol.
#
# Units come from positional paths, `--units LIST` (one path per line, or the
# verifier sweep's `va name path …` rows), or `--all` (every unit under src/
# except src/asmbody/). `--only PATH` restricts the run to that unit.
#
# Idempotent: a unit with no offending identifier is left untouched. With
# `--verify`, every edited unit is re-verified with tools/verify.py (address from
# the list, the unit's header comment, or config/SLUS-20836/symbols.txt by file name) and
# rolled back unless the result is MATCH; the report lists the diagnostics.
# Dry-run prints the plan and writes nothing.

import argparse
import concurrent.futures
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import verify  # noqa: E402  (tools/verify.py: symbol map, name-style rules)

SYMBOLS = "config/SLUS-20836/symbols.txt"
IDENT = re.compile(r"\b[A-Za-z_][A-Za-z0-9_]*\b")
HEADER_VA = re.compile(r"/\*\s*0x([0-9a-fA-F]+)\s")
RUN_STATIC_INIT = "igMetaObject_RunStaticInit"
NOT_RECOVERED = "/* address-taken; signature not recovered */"


def function_start_name(ident):
    """Symbol name of the function `ident` (a data-style name) points at, or None."""
    if not verify.DATA_STYLE.match(ident):
        return None
    va = verify.address_in_name(ident)
    if va is None:
        return None
    owner = verify.code_owner(va, SYMBOLS)
    if owner is None or owner[0] != va:
        return None
    return verify.sanitize(owner[1])


def strip_comments(text):
    text = re.sub(r"/\*.*?\*/", lambda m: " " * len(m.group(0)), text, flags=re.S)
    return re.sub(r"//[^\n]*", "", text)


def split_args(arglist):
    """Top-level comma split of a call's argument text."""
    out, depth, cur = [], 0, []
    for ch in arglist:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == "," and depth == 0:
            out.append("".join(cur).strip())
            cur = []
        else:
            cur.append(ch)
    if cur or out:
        out.append("".join(cur).strip())
    return out


def call_args(code, callee, start=0):
    """Argument lists of every `callee(...)` call in `code` (comment-free text)."""
    calls = []
    declaration = re.compile(r"^[ \t]*(?:extern\s+)?(?:\"C\"\s+)?(?!return\b|else\b|case\b|goto\b)"
                             r"[\w\s\*]*\w[\s\*]+$")
    for m in re.finditer(r"\b" + re.escape(callee) + r"\s*\(", code[start:]):
        before = code[:m.start() + start]
        if declaration.match(before[before.rfind("\n") + 1:]):
            continue      # `void callee(char *);` is a prototype, not a call
        i, depth = m.end() + start, 1
        j = i
        while j < len(code) and depth:
            if code[j] == "(":
                depth += 1
            elif code[j] == ")":
                depth -= 1
            j += 1
        calls.append((m.start() + start, split_args(code[i:j - 1])))
    return calls


def declaration_params(code, callee):
    """Parameter type texts of the unit's prototype for `callee`, or None if unprototyped."""
    m = re.search(r"^[ \t]*(?:extern\s+)?[\w\s\*]+?\b" + re.escape(callee)
                  + r"\s*\(([^;{]*)\)\s*;", code, flags=re.M)
    if not m:
        return None
    params = [p.strip() for p in split_args(m.group(1))]
    if params in ([], ["void"]):
        return None
    return params


def is_object_pointer(param):
    """`char *`, `int *` and friends: a parameter a function designator cannot be passed to."""
    return "(" not in param and "*" in param


class Unit:
    def __init__(self, path):
        self.path = path
        self.text = open(path, encoding="utf-8").read()
        self.is_cpp = path.endswith((".cpp", ".cc", ".cxx"))
        self.renames = {}
        self.notes = []

    def plan(self):
        code = strip_comments(self.text)
        for ident in sorted(set(IDENT.findall(code))):
            name = function_start_name(ident)
            if name:
                self.renames[ident] = name
        return bool(self.renames)

    def is_defined_or_declared(self, name, code):
        return re.search(r"\b" + re.escape(name) + r"\b", code) is not None

    def rewrite(self):
        text = self.text
        code = strip_comments(text)
        lines = text.split("\n")
        new_decls = []          # (insert position line index or None, declaration text)
        removed = set()
        declared_names = set()
        register_style = set()  # new names passed to igMetaObject_RunStaticInit

        # Which renamed identifiers are static-init callbacks?
        rsi_args = call_args(code, RUN_STATIC_INIT)
        rsi_decl_params = declaration_params(code, RUN_STATIC_INIT)
        rsi_all_functions = bool(rsi_args) and all(
            len(args) == 1 and args[0] in self.renames for _, args in rsi_args)
        for ident, name in self.renames.items():
            if any(args == [ident] for _, args in rsi_args):
                register_style.add(name)

        # Remove the old declarations and compose the new prototypes.
        decl_re = {ident: re.compile(
            r"^[ \t]*(?:extern\s+)?(?:\"C\"\s+)?[\w\s\*]*?\b" + re.escape(ident)
            + r"\b\s*(?:\[[^\]]*\])?\s*(?:\([^)]*\))?\s*;[ \t]*(?:/\*.*?\*/)?[ \t]*$")
            for ident in self.renames}
        first_removed = {}
        for i, line in enumerate(lines):
            for ident, rx in decl_re.items():
                if rx.match(line) and not line.lstrip().startswith(("typedef", "struct", "return")):
                    removed.add(i)
                    first_removed.setdefault(ident, i)
        for ident, name in self.renames.items():
            if name in declared_names:
                continue
            if self.is_defined_or_declared(name, code):
                self.notes.append(f"{name} already appears in the unit; no prototype added")
                declared_names.add(name)
                continue
            calls = [args for _, args in call_args(code, ident)]
            if calls:
                arity = len(calls[0])
                params = ", ".join(["int"] * arity) if arity else "void"
                decl = f"int {name}({params}); /* arity from the unit's call; types not recovered */"
            elif name in register_style:
                decl = f"void *{name}(void);"
            else:
                decl = f"void {name}(void); {NOT_RECOVERED}"
            new_decls.append((first_removed.get(ident), decl))
            declared_names.add(name)

        # Rewrite igMetaObject_RunStaticInit's local prototype to the project form
        # when every argument it receives is a function; otherwise cast per site.
        site_casts = {}
        if rsi_all_functions and rsi_decl_params and len(rsi_decl_params) == 1 \
                and is_object_pointer(rsi_decl_params[0]):
            for i, line in enumerate(lines):
                if re.match(r"^[ \t]*(?:extern\s+)?void\s+" + RUN_STATIC_INIT + r"\s*\([^)]*\)\s*;", line):
                    lines[i] = re.sub(r"\([^)]*\)", "(void *(*)(void))", line, count=1)
        else:
            self._collect_site_casts(code, site_casts, exclude=None)

        # Replace the use sites.
        out = []
        for i, line in enumerate(lines):
            if i in removed:
                continue
            out.append(self._rewrite_line(line, site_casts))
        text = "\n".join(out)

        # Insert the prototypes: C++ inside the extern "C" block, C where the old
        # declaration stood (or before the first function otherwise).
        text = self._insert_declarations(text, new_decls, removed)
        return text

    def _collect_site_casts(self, code, site_casts, exclude):
        """Bare renamed arguments to prototyped callees with object-pointer params."""
        for callee in set(re.findall(r"\b([A-Za-z_]\w*)\s*\(", code)):
            params = declaration_params(code, callee)
            if not params:
                continue
            for _, args in call_args(code, callee):
                for k, arg in enumerate(args):
                    if arg in self.renames and k < len(params) and is_object_pointer(params[k]):
                        site_casts[(callee, arg)] = re.sub(r"\s*\w+\s*$", "", params[k]) \
                            if re.search(r"\*\s*\w+$", params[k]) else params[k]

    def _rewrite_line(self, line, site_casts):
        for ident, name in self.renames.items():
            rx = re.escape(ident)
            # `(&DAT_x[0])`, `&DAT_x[0]`, `&DAT_x` used as the function's address.
            line = re.sub(r"\(\s*&\s*" + rx + r"\s*\[\s*0\s*\]\s*\)", name, line)
            line = re.sub(r"&\s*" + rx + r"\s*\[\s*0\s*\]", name, line)
            line = re.sub(r"&\s*" + rx + r"\b(?!\s*\[)", name, line)
            for (callee, arg), cast in site_casts.items():
                if arg == ident:
                    line = re.sub(r"(\b" + re.escape(callee) + r"\s*\([^;]*?)(?<![\w\)])\b"
                                  + rx + r"\b", lambda m: m.group(1) + f"({cast}){name}", line)
            line = re.sub(r"\b" + rx + r"\b", name, line)
        return line

    def _insert_declarations(self, text, new_decls, removed):
        if not new_decls:
            return text
        lines = text.split("\n")
        decl_lines = [d for _, d in new_decls]
        if self.is_cpp:
            for i, line in enumerate(lines):
                if re.match(r'^\s*extern\s+"C"\s*\{\s*$', line):
                    lines[i + 1:i + 1] = decl_lines
                    return "\n".join(lines)
            decl_lines = ['extern "C" ' + d for d in decl_lines]
        # C (or a C++ unit without an extern "C" block): at the first removed
        # declaration's position, else before the first non-comment, non-extern line.
        at = min((p for p, _ in new_decls if p is not None), default=None)
        if at is None:
            at = 0
            depth = 0
            for i, line in enumerate(lines):
                depth += line.count("/*") - line.count("*/")
                if depth == 0 and line.strip() and not line.strip().startswith(("/*", "*", "#")):
                    at = i
                    break
        else:
            at = at - sum(1 for r in removed if r < at)
        lines[at:at] = decl_lines
        return "\n".join(lines)


def unit_address(path, text, listed):
    if path in listed:
        return listed[path]
    m = HEADER_VA.search(text)
    if m:
        return int(m.group(1), 16)
    by_name, _ = verify.load_symbols(SYMBOLS)
    base = os.path.splitext(os.path.basename(path))[0]
    return by_name.get(base, (None,))[0]


def run_verify(path, va):
    env = dict(os.environ)
    env.setdefault("DW4_ELF", os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36"))
    proc = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "verify.py"),
                           f"0x{va:x}", path], cwd=ROOT, env=env,
                          capture_output=True, text=True)
    out = (proc.stdout + proc.stderr).strip().split("\n")
    ok = bool(out) and out[0].startswith("MATCH")
    diag = [l.strip() for l in out[1:] if l.strip()][:4]
    if not ok and proc.returncode and not out[0].startswith(("MATCH", "DIFFER")):
        diag = out[:4]
    return ok, "; ".join(diag) or out[0]


def collect_units(args):
    listed = {}
    units = []
    if args.units:
        for ln in open(args.units):
            parts = ln.split()
            if not parts or ln.startswith("#"):
                continue
            if len(parts) >= 3 and re.fullmatch(r"[0-9a-fA-F]{6,8}", parts[0]) and parts[2].startswith("src/"):
                listed[parts[2]] = int(parts[0], 16)
                units.append(parts[2])
            else:
                units.append(parts[0])
    units += args.paths
    if args.all:
        for d, _, files in os.walk("src"):
            if d.startswith("src/asmbody"):
                continue
            units += [os.path.join(d, f) for f in files if f.endswith((".c", ".cpp"))]
    units = sorted(set(units))
    if args.only:
        units = [u for u in units if u == args.only] or [args.only]
    return units, listed


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__ or "rename function data refs")
    ap.add_argument("paths", nargs="*", help="units to repair (repository-relative)")
    ap.add_argument("--units", help="list of units: one path per line, or verifier sweep rows")
    ap.add_argument("--all", action="store_true", help="scan every unit under src/ (not src/asmbody/)")
    ap.add_argument("--only", help="restrict the run to this unit")
    ap.add_argument("--dry-run", action="store_true", help="print the plan; write nothing")
    ap.add_argument("--verify", action="store_true",
                    help="re-verify each edited unit with tools/verify.py; roll back non-MATCH")
    ap.add_argument("--jobs", type=int, default=8, help="parallel verifications (default 8)")
    ap.add_argument("--report", help="write a JSON report of edits, verifications and rollbacks")
    args = ap.parse_args(argv)
    os.chdir(ROOT)

    units, listed = collect_units(args)
    edited, untouched, missing, rolled_back, matched = [], [], [], [], []
    pending = []
    for path in units:
        if not os.path.exists(path):
            missing.append(path)
            continue
        unit = Unit(path)
        if not unit.plan():
            untouched.append(path)
            continue
        new_text = unit.rewrite()
        summary = ", ".join(f"{a} -> {b}" for a, b in sorted(unit.renames.items()))
        print(f"{'would edit' if args.dry_run else 'edit'} {path}: {summary}")
        for note in unit.notes:
            print(f"   note: {note}")
        if args.dry_run:
            if args.only:
                print(new_text)
            continue
        with open(path, "w", encoding="utf-8") as fh:
            fh.write(new_text)
        edited.append(path)
        pending.append((path, unit.text, new_text))

    if args.verify and pending:
        def check(item):
            path, old, new = item
            va = unit_address(path, new, listed)
            if va is None:
                return path, old, False, "no address for the unit (not listed, no header, not in symbols)"
            ok, diag = run_verify(path, va)
            return path, old, ok, diag
        with concurrent.futures.ThreadPoolExecutor(max_workers=max(1, args.jobs)) as pool:
            for path, old, ok, diag in pool.map(check, pending):
                if ok:
                    matched.append(path)
                else:
                    with open(path, "w", encoding="utf-8") as fh:
                        fh.write(old)
                    rolled_back.append((path, diag))
                    print(f"ROLLBACK {path}: {diag}")

    print(f"\n{len(units)} units: {len(edited)} edited, {len(untouched)} untouched, "
          f"{len(missing)} missing"
          + (f"; verified MATCH {len(matched)}, rolled back {len(rolled_back)}" if args.verify else ""))
    if args.report:
        with open(args.report, "w") as fh:
            json.dump({"edited": edited, "untouched": untouched, "missing": missing,
                       "matched": matched, "rolled_back": rolled_back}, fh, indent=1)
    return 1 if rolled_back or missing else 0


if __name__ == "__main__":
    sys.exit(main())
