#!/usr/bin/env python3
"""m2c_loop.py — the per-function iteration harness for the m2c phase (M7).

`m2c_batch.py` sweeps; this drives **one** function until it matches. It is the
missing half of the loop the tracker describes: m2c's draft plus the instruction
diff, iterated with `tools/verify.py` as the oracle.

What it does for one function:

  1. builds the spimdisasm listing (`m2c_one.asm_for`) and runs m2c in-process;
  2. mechanically cleans the draft (`m2c_batch.clean`) in all three address
     forms, keeping the closest one, and writes it to `build/m2c/<name>.c`;
  3. compiles and diffs it (`verify.verify_one --verbose`) and prints an
     **aligned instruction table**: index, retail mnemonic, ours mnemonic, and a
     marker on the words that differ.

That table is the point. The raw verify report gives differing *words*, which is
useless for deciding whether m2c chose the wrong loop shape or the wrong
register; the disassembly shows both.

Usage:
  m2c_loop.py 0x00100240                 # prepare + print the diff
  m2c_loop.py FUN_00100240               # same, by name
  m2c_loop.py 0x00100240 --no-prepare    # re-diff an edited build/m2c/<name>.c
  m2c_loop.py --sample 12 --max-diffs 3  # a stratified sample from the worklist
  m2c_loop.py --sample 12 --band 64      # only 64..127-byte functions

Editing a candidate is `vim build/m2c/<name>.c` then `--no-prepare`; a match is
banked by copying it to `src/<name>.c` (verify first, always).
"""
import argparse
import collections
import os
import re
import struct
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)
sys.path.insert(0, os.environ.get("DW4_M2C_DIR", os.path.join(ROOT, "local", "m2c")))

import automatch as am            # noqa: E402
import m2c_one                    # noqa: E402
import m2c_batch                  # noqa: E402
import verify as vfy              # noqa: E402

ELF_DEFAULT = os.environ.get("DW4_ELF", os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36"))
SYMBOLS_DEFAULT = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")
CAND_DIR = os.path.join(ROOT, "build", "m2c")
WORKLIST = os.path.join(ROOT, "build", "m2c_worklist.tsv")

VERBOSE_WORD_RE = re.compile(
    r"^\s+(!{2}|\s{2})\[\s*(\d+)\]\s+retail ([0-9a-f]{8})\s+ours ([0-9a-f]{8})\s*$")


def disasm_words(words, va):
    """[(mnemonic, operands)] for little-endian words placed at `va`."""
    import tempfile
    blob = b"".join(struct.pack("<I", w) for w in words)
    with tempfile.NamedTemporaryFile(suffix=".bin", delete=False) as fh:
        fh.write(blob)
        path = fh.name
    out = subprocess.run(["mipsel-linux-gnu-objdump", "-D", "-z", "-b", "binary",
                          "-m", "mips:5900", "-EL", "--adjust-vma", hex(va), path],
                         capture_output=True, text=True).stdout
    os.unlink(path)
    res = {}
    for ln in out.splitlines():
        m = re.match(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)\s*(.*)$", ln)
        if m:
            res[int(m.group(1), 16)] = (m.group(3), m.group(4).strip())
    return res


def parse_verbose(report):
    """The aligned word lists `verify_one(verbose=True)` printed."""
    ours, retail = {}, {}
    for ln in report.splitlines():
        m = VERBOSE_WORD_RE.match(ln)
        if m:
            i = int(m.group(2))
            retail[i] = int(m.group(3), 16)
            ours[i] = int(m.group(4), 16)
    return ours, retail


def mwcc_error(src):
    """Full compiler output — verify.py keeps only its first line."""
    env = dict(os.environ, MWCIncludes=os.path.dirname(os.path.abspath(src)))
    r = subprocess.run([vfy.WIBO_DEFAULT, vfy.MWCC_DEFAULT, "-c", vfy.FLAGS_DEFAULT,
                        src, "-o", "/tmp/m2c_loop_err_%d.o" % os.getpid()],
                       capture_output=True, text=True, env=env)
    return (r.stdout + r.stderr).strip()


_ENV_CACHE = {}


def load_env(elf=ELF_DEFAULT, symbols=SYMBOLS_DEFAULT):
    """Symbols + the whole-image disassembly, cached per (elf, symbols).

    `prepare` is called in a loop, and re-disassembling the 4.5 MB image for every
    function costs ~1.5 s — more than the actual m2c + compile work.
    """
    key = (elf, symbols)
    if key not in _ENV_CACHE:
        img = open(elf, "rb").read()
        syms = am.load_symbols(symbols)
        lo = min(v for v, _, _ in syms)
        hi = max(v + s for v, s, _ in syms)
        _ENV_CACHE[key] = {
            "img": img, "syms": syms,
            "table": am.disassemble(img, lo, hi),
            "bounds": m2c_one.load_bounds(elf),
            "gp": m2c_one.load_gp(elf),
            "names": {v: n for v, s, n in syms},
            "jtabs": m2c_one.load_jtables(elf, symbols),
        }
    return _ENV_CACHE[key]


def prepare(va, name, size, symbols=SYMBOLS_DEFAULT, elf=ELF_DEFAULT, show=True,
            target="mipsee-mwcc-c", ee_abi=True):
    """Run m2c + cleaner, keep the best address mode, write build/m2c/<name>.c."""
    env = load_env(elf, symbols)
    table, names, bounds = env["table"], env["names"], env["bounds"]
    jtabs = env["jtabs"]
    t0 = time.time()
    asm = m2c_one.asm_for(va, name, size, table, names, bounds=bounds,
                          jtables=jtabs.get(va, {}), gp=env["gp"], ee_abi=ee_abi)
    try:
        draft = m2c_batch.run_m2c(asm, name, "/tmp/m2c_loop_%d.s" % os.getpid(),
                                  target=target)
    except Exception as exc:                                  # noqa: BLE001
        return None, "m2c failed: %s" % exc, time.time() - t0
    if not draft.strip() or "Decompilation failure" in draft or "Decompilation error" in draft:
        return None, "m2c could not decompile:\n" + draft[:600], time.time() - t0
    best = None
    for mode in ("hybrid", "symbol", "literal"):
        src = m2c_batch.clean(draft, addr_mode=mode, bounds=bounds)
        fit = m2c_batch.fit_widths(src, va, size, table)
        variants = [(src, mode)] + ([(fit, mode + "+w")] if fit != src else [])
        for base, tag in list(variants):
            ptr = m2c_batch.retype_global_loads(base)
            if ptr != base:
                variants.append((ptr, tag + "+p"))
                od = m2c_batch.order_pointer_decls(ptr)
                if od != ptr:
                    variants.append((od, tag + "+po"))
            od = m2c_batch.order_pointer_decls(base)
            if od != base and all(od != v for v, _ in variants):
                variants.append((od, tag + "+o"))
        for base, tag in list(variants):
            vc = m2c_batch.virtualize_calls(base, name)
            if vc and all(vc != v for v, _ in variants):
                variants.append((vc, tag + "+vcpp"))
            sret = m2c_batch.virtualize_calls(base, name, sret=True)
            if sret and all(sret != v for v, _ in variants):
                variants.append((sret, tag + "+sretvcpp"))
        for vsrc, vmode in variants:
            tmp = "/tmp/m2c_loop_%d%s" % (os.getpid(),
                                           ".cpp" if vmode.endswith("vcpp") else ".c")
            open(tmp, "w").write("/* %s */\n" % name + vsrc)
            # verbose: the aligned word lists are the loop's input, so the report
            # has to carry every word, not only the differing ones.
            ok, rep = vfy.verify_one(va, tmp, symbols=symbols, elf=elf, verbose=True)
            first = rep.splitlines()[0]
            if "compile failed" in first:
                nb = 10 ** 9
            else:
                ours, retail = parse_verbose(rep)
                nb = sum(1 for i in ours if ours.get(i) != retail.get(i))
                if "size:" in rep:
                    nb += 1
            if best is None or nb < best[0]:
                best = (nb, vmode, vsrc, ok, rep)
            if ok:
                break
        if best is not None and best[3]:
            break
    nb, mode, src, ok, rep = best
    os.makedirs(CAND_DIR, exist_ok=True)
    dest = os.path.join(CAND_DIR, name + ".c")
    header = ("/* 0x%08x — %s, m2c draft (%s mode), %s.\n"
              " * Iterate here; a match is copied to src/%s.c only after verify.py agrees. */\n"
              % (va, name, mode, "MATCHES retail" if ok else "does not match yet", name))
    open(dest, "w").write(header + src)
    return (va, name, size, mode, nb, ok, src, rep), None, time.time() - t0


def print_diff(va, name, size, mode, nb, ok, src, rep, symbols=SYMBOLS_DEFAULT,
               elf=ELF_DEFAULT, show_c=True):
    print("==== %s  0x%06x  %dB  mode=%s  diffs=%s  %s"
          % (name, va, size, mode, nb, "MATCH" if ok else "differ"))
    if show_c:
        print("---- candidate (%s)" % os.path.join("build/m2c", name + ".c"))
        print(src)
    ours, retail = parse_verbose(rep)
    if not ours:
        print(rep)
        if nb >= 10 ** 9:
            print("   ---- compiler output")
            for ln in mwcc_error(os.path.join(CAND_DIR, name + ".c")).splitlines()[:12]:
                print("   " + ln)
        return
    n = max(len(ours), len(retail))
    ra = disasm_words([retail.get(i, 0) for i in range(n)], va)
    oa = disasm_words([ours.get(i, 0) for i in range(n)], va)
    print("---- diff (%d words)" % n)
    for i in range(n):
        a = retail.get(i)
        b = ours.get(i)
        if a == b and a is not None:
            continue
        rm = "%s %s" % ra.get(va + 4 * i, ("word", ""))
        om = "%s %s" % oa.get(va + 4 * i, ("word", ""))
        tag = "!!" if (a is None or b is None) else "= "
        print("   %s[%3d] retail %s | ours %s" % (tag, i, rm.ljust(34), om))
    for ln in rep.splitlines():
        if VERBOSE_WORD_RE.match(ln) or ln.startswith(("MATCH", "DIFFER")):
            continue
        print("   " + ln.strip())


def bank(name, va, note="m2c draft, hand-fixed"):
    """Copy a verified build/m2c/<name>.c into src/, dropping the iteration header.

    The iteration file always has a ``.c`` suffix, but a virtual-call winner was
    compiled as C++ and must be banked as ``.cpp`` or MWCC will switch front ends
    and lose the ABI call shape.
    """
    src = os.path.join(CAND_DIR, name + ".c")
    text = open(src).read()
    lines = text.splitlines(keepends=True)
    # drop m2c_loop's provenance block and m2c's own leading `/* <name> */` comment
    while lines and (lines[0].startswith("/* 0x") or lines[0].startswith(" * ")
                     or lines[0].startswith("/* %s */" % name)):
        lines.pop(0)
    ext = ".cpp" if "vcpp mode" in text.splitlines()[0] else ".c"
    dest = os.path.join(ROOT, "src", "unmatched", name + ext)
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    open(dest, "w").write("".join(lines).lstrip("\n"))
    return dest


def read_worklist(path):
    rows = []
    with open(path) as fh:
        head = fh.readline()
        for ln in fh:
            p = ln.rstrip("\n").split("\t")
            if len(p) >= 6:
                rows.append({"name": p[0], "va": int(p[1], 0), "size": int(p[2]),
                             "status": p[3], "diffs": int(p[4]), "mode": p[5]})
    return rows


def sample(rows, n, max_diffs, band=None, status="mismatch"):
    """Deterministic stratified pick: split the size range into n quantiles.

    `diffs` is -1 for a candidate whose best address form does not compile, so a cap can
    only be applied to rows that are comparable at all: the `compile` tier carries -1 by
    construction (it is what makes it that tier), and requiring `0 <= diffs` selected
    nothing from it. Only the rows that *have* a diff count are capped.
    """
    pool = [r for r in rows if r["status"] == status
            and (r["diffs"] < 0 or r["diffs"] <= max_diffs)]
    if band:
        pool = [r for r in pool if band[0] <= r["size"] <= band[1]]
    pool.sort(key=lambda r: (r["size"], r["va"]))
    if not pool:
        return []
    out, seen = [], set()
    for i in range(n):
        idx = round(i * (len(pool) - 1) / max(n - 1, 1))
        if idx not in seen:
            seen.add(idx)
            out.append(pool[idx])
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("target", nargs="?", help="VA (0x...) or function name")
    ap.add_argument("--elf", default=ELF_DEFAULT)
    ap.add_argument("--symbols", default=SYMBOLS_DEFAULT)
    ap.add_argument("--worklist", default=WORKLIST)
    ap.add_argument("--sample", type=int, default=0,
                    help="print a stratified sample of N candidates and exit")
    ap.add_argument("--max-diffs", type=int, default=3)
    ap.add_argument("--band", default=None, help="size band LO-HI for --sample")
    ap.add_argument("--status", default="mismatch")
    ap.add_argument("--all", action="store_true", help="sample: ignore the diff cap")
    ap.add_argument("--process", action="store_true",
                    help="with --sample: prepare every picked candidate and report its new status"
                         " (measure a tier; combine with --bank to keep the matches)")
    ap.add_argument("--no-prepare", action="store_true",
                    help="re-diff the existing build/m2c/<name>.c instead of regenerating")
    ap.add_argument("--no-c", action="store_true", help="do not print the candidate source")
    ap.add_argument("--bank", action="store_true",
                    help="on a match, copy build/m2c/<name>.c into src/ (stripping the header)")
    a = ap.parse_args(argv)

    band = None
    if a.band:
        lo, _, hi = a.band.partition("-")
        band = (int(lo), int(hi or 10 ** 9))

    if a.sample:
        rows = read_worklist(a.worklist)
        picks = sample(rows, a.sample, 10 ** 9 if a.all else a.max_diffs,
                       band=band, status=a.status)
        if not a.process:
            for r in picks:
                print("%s\t0x%08x\t%d\t%s\tdiffs=%d" % (r["name"], r["va"], r["size"],
                                                       r["status"], r["diffs"]))
            return 0
        # measure: regenerate each candidate with the *current* pipeline and report what
        # the tier is now. prepare() tries all three address forms and keeps the closest.
        t0 = time.time()
        out = collections.Counter()
        matched = []
        for r in picks:
            res, err, _dt = prepare(r["va"], r["name"], r["size"], a.symbols, a.elf)
            if err:
                out["m2c-fail"] += 1
                print("%-32s %5dB  %-8s -> m2c-fail" % (r["name"], r["size"], r["status"]))
                continue
            va, name, size, mode, nb, ok, src, rep = res
            new = "match" if ok else ("compile" if nb >= 10 ** 9 else "mismatch")
            out[new] += 1
            if ok:
                matched.append(name)
                if a.bank:
                    bank(name, va, "m2c draft, %s" % mode)
            print("%-32s %5dB  %-8s -> %-8s %s"
                  % (name, size, r["status"], new,
                     "diffs=%s mode=%s" % ("compile" if nb >= 10 ** 9 else nb, mode)))
        print("\n%d picked: %s   [%.0fs]"
              % (len(picks), "  ".join("%s=%d" % kv for kv in sorted(out.items())),
                 time.time() - t0))
        if matched:
            print("matched: %s%s" % (", ".join(matched[:12]),
                                      " ..." if len(matched) > 12 else ""))
        return 0

    if not a.target:
        ap.error("give a VA/name, or --sample N")
    syms = {(v, n): (s, v) for v, s, n in am.load_symbols(a.symbols)}
    if a.target.startswith("0x"):
        va = int(a.target, 0)
        hit = [s for (v, n), (s, vv) in syms.items() if vv == va]
        if not hit:
            ap.error("0x%x is not in %s" % (va, a.symbols))
        size, va = hit[0], va
        name = [n for (v, n), (s, vv) in syms.items() if vv == va][0]
    else:
        name = a.target
        hit = [(s, v) for (v, n), (s, v) in syms.items() if n == name]
        if not hit:
            ap.error("%s is not in %s" % (name, a.symbols))
        size, va = hit[0]

    if a.no_prepare:
        cand = os.path.join(CAND_DIR, name + ".c")
        if not os.path.exists(cand):
            ap.error("no %s — run without --no-prepare first" % cand)
        ok, rep = vfy.verify_one(va, cand, symbols=a.symbols, elf=a.elf, verbose=True)
        src = open(cand).read()
        if "compile failed" in rep.splitlines()[0]:
            nb = 10 ** 9
        else:
            _ours, _retail = parse_verbose(rep)
            nb = sum(1 for i in _ours if _ours.get(i) != _retail.get(i))
            if "size:" in rep:
                nb += 1
        print_diff(va, name, size, "edited", nb, ok, src, rep, a.symbols, a.elf,
                   show_c=not a.no_c)
        if a.bank and ok:
            print("   banked -> %s" % bank(name, va, "m2c draft, hand-fixed"))
        return 0 if ok else 1

    res, err, dt = prepare(va, name, size, a.symbols, a.elf)
    if err:
        print("==== %s 0x%06x\n%s" % (name, va, err))
        return 2
    print_diff(*res, symbols=a.symbols, elf=a.elf, show_c=not a.no_c)
    if a.bank and res[5]:
        print("   banked -> %s" % bank(name, va))
    print("   [%.2fs]" % dt)
    return 0


if __name__ == "__main__":
    sys.exit(main())
