#!/usr/bin/env python3
"""region_board.py — per-0x100-byte region scoreboard for one function of a candidate unit.

  region_board.py --unit-va 0x001f0d10 --function p2SubmitVertices --cand <unit file>
                  [--repo <worktree>] [--unit-objects <json>] [--board-dir <dir>] [--words]
                  [--record <label> [--draft-file <file with the body>]]
  region_board.py --show <function> [--board-dir <dir>]

Compiles --cand exactly as `tools/check.py --function <unit-va> --cand <file>` does (the repository's
units.standalone / unitprofiles / cc.compile_argv / verify internals; --repo defaults to this checkout), then
compares the named function against retail:

  * verify mode: the repository's verify (verify_emitted_unit for a unit-objects group,
    _verify_standalone otherwise) accepted the object and printed the function's word diffs —
    relocations applied exactly as check.py does. Authoritative.
  * aligned mode: verify rejected the object (another member's extent, unowned data, ...) or the
    draft's size differs from retail. The function's body is cut from the object, its relocations
    applied with verify's resolver rules; a field verify could not resolve (anonymous data, literal
    pools, jump tables) is masked on both sides. Same size: word-for-word. Different size: the
    instructions are aligned with difflib (immediates masked for the alignment key), branches are
    compared by mapped target, and every deleted/replaced/inserted word is charged to the retail
    region at that point.

Output: one line per retail region R<k> = [k*0x100, (k+1)*0x100): EXACT or `n/m words differ`
(+e extra draft words inserted there), then the total.

--record <label> keeps <board-dir>/<function>/board.json (default build/regions): per region the best
differing count (n + extra), the draft and bundle that achieved it, the label and a timestamp.
An improving run keeps drafts/<stamp>_<label>_<sha8>/: the primary draft (--draft-file, default --cand)
and bundle.tar.gz of every worktree file differing from HEAD, untracked files under src/ and include/,
and the cand/--draft-file when outside the worktree (as external/<name>). Prints the regions that improved.
"""
import argparse
import contextlib
import datetime
import difflib
import fcntl
import json
import os
import shutil
import struct
import subprocess
import sys
import hashlib
import tarfile
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REGION = 0x100


# ---------------------------------------------------------------- compile (check.py's path)

def load_repo(repo):
    repo = os.path.abspath(repo)
    sys.path.insert(0, os.path.join(repo, "tools"))
    os.chdir(repo)
    import check, cc, units, unitobjects, unitprofiles, verify  # noqa: E401
    return check, cc, units, unitobjects, unitprofiles, verify


def compile_unit(mods, unit_va, cand, unit_objects):
    """Compile `cand` the way check.py --function <unit_va> does -> (obj, group, profile, source, tmp, env)."""
    check, cc, units, unitobjects, unitprofiles, verify = mods
    symbols = "config/SLUS-20836/symbols.txt"
    _by_name, by_va = verify.load_symbols(symbols)
    group = unitobjects.group_for(unit_va, unit_objects)
    owner = group.owner if group else unit_va
    nm = by_va[owner][0] if owner in by_va else None
    src, tmp = ((cand, None) if nm is None
                else units.standalone(cand, nm, symbols=symbols, unit_objects=unit_objects))
    flags, mwcc, wibo = check.FLAGS_DEFAULT, os.environ.get("DW4_MWCC", check.MWCC_DEFAULT), \
        os.environ.get("DW4_WIBO", check.WIBO_DEFAULT)
    resolution = unitprofiles.resolve(owner, flags, mwcc, symbols=symbols)
    profile = unitprofiles.for_source(resolution.profile, src, flags, mwcc)
    cmd_flags = unitprofiles.command_flags(profile)
    env = dict(os.environ, MWCIncludes=os.path.dirname(os.path.abspath(src)))
    obj = os.path.join(cc.scratch_dir(), "regions_cand.o")
    r = subprocess.run(cc.compile_argv(wibo, profile.compiler, cmd_flags, src, obj),
                       capture_output=True, text=True, env=env)
    if not os.path.exists(obj):
        if tmp:
            os.remove(tmp)
        sys.exit("compile failed: " + verify.compile_error(r.stdout + r.stderr))
    if tmp:
        os.remove(tmp)
    return obj, group, profile, src, env, wibo


# ---------------------------------------------------------------- verify mode

def verify_mode(mods, obj, group, profile, src, env, wibo, va, name, size, unit_objects):
    """-> list of differing word indices, or None when verify did not compare the body."""
    check, cc, units, unitobjects, unitprofiles, verify = mods
    import re
    symbols, elf = "config/SLUS-20836/symbols.txt", os.environ.get("DW4_ELF", check.ELF_DEFAULT)
    work = obj + ".verify.o"
    shutil.copy(obj, work)
    try:
        if group:
            def recompile(compiler, flags, out):
                subprocess.run(cc.compile_argv(wibo, compiler, flags, src, out),
                               capture_output=True, text=True, env=env)
                return os.path.exists(out)
            _ok, report, _ = verify.verify_emitted_unit(work, group, elf, symbols, profile, recompile,
                                                        requested=va)
            head = re.compile(r"^(MATCH|DIFFER) (?:emitted|duplicate) 0x%x \S+ (\d+)B" % va)
            word = re.compile(r"^   !!\[(\d+)\] retail")
        else:
            img = verify.read_elf(elf)
            by_name, _ = verify.load_symbols(symbols)
            tabs = sorted(verify.load_jumptables(verify.jumptables_path(symbols)).get(va, []))
            try:
                _ok, report = verify._verify_standalone(work, va, name, size, verify.va_bytes(img, va, size),
                                                        img, by_name, symbols, tabs, [], None, elf, False)
            except ValueError:
                return None, ""
            if "   size:" in report or "object defines no symbol" in report or "not defined in .text" in report:
                return None, report.splitlines()[0]
            return [int(m.group(1)) for m in map(re.compile(r"^   \[\s*(\d+)\] retail").match,
                                                 report.splitlines()) if m], report.splitlines()[0]
        lines = report.splitlines()
        if not any(head.match(ln) for ln in lines):
            return None, lines[0] if lines else ""
        return [int(m.group(1)) for m in map(word.match, lines) if m], lines[0]
    finally:
        if os.path.exists(work):
            os.remove(work)


# ---------------------------------------------------------------- aligned mode

BRANCH_OPS = {4, 5, 6, 7, 20, 21, 22, 23}
REGIMM_BRANCH = {0, 1, 2, 3, 16, 17, 18, 19}
R_TYPE_OPS = {0, 0x1c}          # SPECIAL, MMI: no immediate


def is_branch(w):
    op = w >> 26
    if op in BRANCH_OPS:
        return True
    if op == 1:
        return ((w >> 16) & 31) in REGIMM_BRANCH
    if op in (16, 17, 18) and ((w >> 21) & 31) == 8:     # BC0/BC1/BC2
        return True
    return False


def soff(w):
    o = w & 0xffff
    return o - 0x10000 if o & 0x8000 else o


def align_key(w):
    op = w >> 26
    if op in (2, 3):
        return w & 0xfc000000
    if op in R_TYPE_OPS or (op in (16, 17, 18) and ((w >> 21) & 31) >= 16):
        return w
    return w & 0xffff0000


FIELD = {4: 0x3ffffff}           # R_26; every other type patches the low half


def own_body(mods, obj, group, va, name):
    """The function's patched words and {word index: field mask} for relocations left unresolved."""
    check, cc, units, unitobjects, unitprofiles, verify = mods
    symbols, elf = "config/SLUS-20836/symbols.txt", os.environ.get("DW4_ELF", check.ELF_DEFAULT)
    by_name, by_va = verify.load_symbols(symbols)
    verify.trim_padded_names(obj)
    syms, _secs = verify.object_syms(obj)
    records, aliases, data = {}, {}, {}
    if group:
        members = ([(group.symbol or by_va[group.owner][0], group.owner)]
                   + list(group.emitted) + list(group.duplicates))
        records = {n: a for n, a in members}
        aliases, data = dict(group.externals), dict(group.data)
    cname = next((n for n, a in records.items() if a == va), name)
    if cname not in syms or not isinstance(syms[cname][0], int):
        # a C++ definition is mangled (`FUN_00159320__FPviUiUiPiPiPi`) while the map keeps the plain name
        mangled = [n for n, (s, _v, z) in syms.items()
                   if n.startswith(name + "__") and isinstance(s, int) and z]
        if len(mangled) != 1:
            sys.exit("object defines no symbol %r for 0x%x%s" % (cname, va, " (candidates: %s)" % mangled
                                                                 if mangled else ""))
        cname = mangled[0]
    section, value, size = syms[cname]
    headers = verify.elf_section_headers(obj)
    text = verify.object_section(obj, headers[section][0], section)[value:value + size]
    relocs = verify.function_relocs(verify.object_relocs(obj, target_section=section), value, size)

    def resolve(sym):
        if sym in records:
            return records[sym]
        if sym in aliases:
            return aliases[sym]
        if sym in data:
            return data[sym]
        if sym in syms and isinstance(syms[sym][0], int) and sym not in by_name:
            return None          # local label / anonymous datum / literal / table: masked
        try:
            return verify.sym_address(sym, by_name, symbols)
        except verify.SymbolError:
            return verify.spelled_address(sym, symbols)

    patched, _, unresolved = verify.apply_relocs(text, relocs, resolve, verify.reginfo_gp(elf))
    if patched is None:
        sys.exit("could not resolve gp")
    kinds = {off: kind for _s, off, kind, _n, _a in relocs}
    masks = {}
    for item in unresolved:
        masks[item[0] // 4] = FIELD.get(kinds.get(item[0]), 0xffff)
    for _s, off, kind, sym, _a in relocs:       # apply_relocs drops the HI16 of an unresolved pair
        if resolve(sym) is None:
            masks[off // 4] = FIELD.get(kind, 0xffff)
    words = [struct.unpack_from("<I", patched, 4 * i)[0] for i in range(len(patched) // 4)]
    return words, masks


def aligned_diff(ours, retail, masks):
    """-> (set of differing retail indices, {retail index: extra draft words inserted before it})."""
    def same(i, j, d2r):
        a, b = retail[i], ours[j]
        m = masks.get(j)
        if m is not None:
            return (a & ~m) == (b & ~m)
        if a == b:
            return True
        if d2r is not None and is_branch(a) and is_branch(b) and (a & 0xffff0000) == (b & 0xffff0000):
            return d2r.get(j + 1 + soff(b)) == i + 1 + soff(a)
        return False

    if len(ours) == len(retail):
        return {i for i in range(len(retail)) if not same(i, i, None)}, {}
    sm = difflib.SequenceMatcher(None, [align_key(w) for w in retail], [align_key(w) for w in ours],
                                 autojunk=False)
    ops = sm.get_opcodes()
    d2r = {}
    for tag, i1, i2, j1, j2 in ops:
        if tag in ("equal", "replace"):
            for k in range(min(i2 - i1, j2 - j1)):
                d2r[j1 + k] = i1 + k
    d2r[len(ours)] = len(retail)
    bad, extra = set(), {}
    for tag, i1, i2, j1, j2 in ops:
        if tag == "equal":
            bad |= {i1 + k for k in range(i2 - i1) if not same(i1 + k, j1 + k, d2r)}
        else:
            bad |= set(range(i1, i2))
            more = (j2 - j1) - (i2 - i1)
            if more > 0:
                at = min(i1 + (i2 - i1), len(retail) - 1)
                extra[at] = extra.get(at, 0) + more
    return bad, extra


# ---------------------------------------------------------------- report / board

def regions_of(size, bad, extra):
    out = []
    for k in range(-(-size // REGION)):
        lo, hi = k * REGION, min(size, (k + 1) * REGION)
        idx = range(lo // 4, hi // 4)
        n = sum(1 for i in idx if i in bad)
        e = sum(extra.get(i, 0) for i in idx)
        out.append({"region": "R%d" % k, "lo": lo, "hi": hi, "words": len(idx), "differ": n, "extra": e})
    return out


def fmt(r):
    span = "0x%03x-0x%03x" % (r["lo"], r["hi"] - 1)
    if r["differ"] == 0 and r["extra"] == 0:
        return "%-4s %s  EXACT" % (r["region"], span)
    s = "%-4s %s  %d/%d words differ" % (r["region"], span, r["differ"], r["words"])
    return s + (" (+%d extra)" % r["extra"] if r["extra"] else "")


@contextlib.contextmanager
def locked(folder):
    os.makedirs(folder, exist_ok=True)
    with open(os.path.join(folder, ".lock"), "w") as fh:
        fcntl.flock(fh, fcntl.LOCK_EX)
        yield


def board_path(board_dir, function):
    return os.path.join(board_dir, function)


def snapshot_files(repo, cand, draft_file):
    """[(name in the bundle, path)]: every worktree file differing from HEAD, every untracked file under
    src/ and include/, and the candidate and --draft-file when they live outside the worktree."""
    def git(*args):
        return subprocess.run(["git", "-C", repo, *args], capture_output=True, text=True).stdout.split("\n")
    names = {n for n in git("diff", "--name-only", "HEAD") if n}
    names |= {n for n in git("ls-files", "--others", "--exclude-standard", "--", "src", "include") if n}
    files = [(n, os.path.join(repo, n)) for n in sorted(names) if os.path.isfile(os.path.join(repo, n))]
    for extra in (cand, draft_file):
        if extra and os.path.relpath(extra, repo).startswith(".."):
            files.append(("external/" + os.path.basename(extra), extra))
    return files


def record(board_dir, function, va, size, rows, total, cand, label, repo, draft_file=None):
    folder = board_path(board_dir, function)
    primary = draft_file or cand
    files = snapshot_files(repo, cand, draft_file)
    sha = hashlib.sha1(open(primary, "rb").read())
    for arcname, path in files:
        sha.update(arcname.encode() + b"\0" + open(path, "rb").read())
    with locked(folder):
        path = os.path.join(folder, "board.json")
        board = json.load(open(path)) if os.path.exists(path) else {
            "function": function, "va": "0x%08x" % va, "size": size, "regions": {}, "total": None}
        now = datetime.datetime.now().isoformat(timespec="seconds")
        stamp = datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
        entry = os.path.join("drafts", "%s_%s_%s" % (stamp, label, sha.hexdigest()[:8]))
        draft = os.path.join(entry, os.path.basename(primary))
        bundle = os.path.join(entry, "bundle.tar.gz")
        improved, copied = [], False

        def keep():
            nonlocal copied
            if not copied:
                os.makedirs(os.path.join(folder, entry), exist_ok=True)
                shutil.copy(primary, os.path.join(folder, draft))
                with tarfile.open(os.path.join(folder, bundle), "w:gz") as tar:
                    for arcname, src in files:
                        tar.add(src, arcname=arcname)
                copied = True

        for r in rows:
            score = r["differ"] + r["extra"]
            old = board["regions"].get(r["region"])
            if old is None or score < old["best"]:
                keep()
                board["regions"][r["region"]] = {"best": score, "words": r["words"], "draft": draft,
                                                 "bundle": bundle, "agent": label, "timestamp": now}
                improved.append("%s %s -> %d" % (r["region"], "new" if old is None else old["best"], score))
        old = board.get("total")
        if old is None or total < old["best"]:
            keep()
            board["total"] = {"best": total, "draft": draft, "bundle": bundle, "agent": label, "timestamp": now}
            improved.append("total %s -> %d" % ("new" if old is None else old["best"], total))
        with open(path + ".tmp", "w") as fh:
            json.dump(board, fh, indent=1)
        os.replace(path + ".tmp", path)
    print("record: " + ("improved " + ", ".join(improved) if improved else "no region improved")
          + ("; kept %s (+ bundle.tar.gz of %d files)" % (os.path.join(folder, draft), len(files))
             if copied else ""))


def show(board_dir, function):
    path = os.path.join(board_path(board_dir, function), "board.json")
    if not os.path.exists(path):
        sys.exit("no board for %s (%s)" % (function, path))
    b = json.load(open(path))
    print("%s %s %dB  board %s" % (b["function"], b["va"], b["size"], path))
    for k in sorted(b["regions"], key=lambda r: int(r[1:])):
        r = b["regions"][k]
        lo = int(k[1:]) * REGION
        verdict = "EXACT" if r["best"] == 0 else "%d/%d best" % (r["best"], r["words"])
        print("%-4s 0x%03x  %-12s %-14s %s  %s" % (k, lo, verdict, r["agent"], r["timestamp"],
                                                    r.get("bundle", r["draft"])))
    t = b.get("total")
    if t:
        print("total best %d  %s %s  %s" % (t["best"], t["agent"], t["timestamp"], t.get("bundle", t["draft"])))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--repo", help="checkout to read (default: the one this script lives in)")
    ap.add_argument("--unit-va")
    ap.add_argument("--function")
    ap.add_argument("--cand")
    ap.add_argument("--unit-objects")
    ap.add_argument("--record", metavar="LABEL")
    ap.add_argument("--draft-file", help="with --record: the file holding the function body, kept as the primary "
                                         "draft (default --cand)")
    ap.add_argument("--words", action="store_true", help="also list the differing retail word indices")
    ap.add_argument("--show", metavar="FUNCTION")
    ap.add_argument("--board-dir", help="where boards are kept (default <repo>/build/regions)")
    a = ap.parse_args(argv)
    repo = os.path.abspath(a.repo or ROOT)
    board_dir = os.path.abspath(a.board_dir or os.path.join(repo, "build", "regions"))
    if a.show:
        return show(board_dir, a.show)
    if not (a.unit_va and a.function and a.cand):
        ap.error("--unit-va, --function and --cand are required (or --show)")
    t0 = time.time()
    cand = os.path.abspath(a.cand)
    draft_file = os.path.abspath(a.draft_file) if a.draft_file else None
    unit_objects = os.path.abspath(a.unit_objects) if a.unit_objects else None
    mods = load_repo(repo)
    verify = mods[5]
    by_name, by_va = verify.load_symbols("config/SLUS-20836/symbols.txt")
    if a.function in by_name:
        va, size = by_name[a.function]
        name = a.function
    else:
        va = int(a.function, 16)
        name, size = by_va[va]
    obj, group, profile, src, env, wibo = compile_unit(mods, int(a.unit_va, 16), cand, unit_objects)
    pristine = obj + ".pristine.o"
    shutil.copy(obj, pristine)
    bad, why = verify_mode(mods, obj, group, profile, src, env, wibo, va, name, size, unit_objects)
    extra, note = {}, ""
    if bad is not None:
        mode, ours_len = "verify", size // 4
        bad = set(bad)
    else:
        ours, masks = own_body(mods, pristine, group, va, name)
        img = verify.read_elf(os.environ.get("DW4_ELF", mods[0].ELF_DEFAULT))
        retail = [struct.unpack_from("<I", verify.va_bytes(img, va, size), 4 * i)[0] for i in range(size // 4)]
        bad, extra = aligned_diff(ours, retail, masks)
        mode, ours_len = "aligned", len(ours)
        note = "; verify: %s; %d reloc fields masked" % (why.strip()[:120] or "no body compared", len(masks))
    rows = regions_of(size, bad, extra)
    print("%s 0x%08x retail %dB, draft %dB, mode=%s%s" % (name, va, size, ours_len * 4, mode, note))
    for r in rows:
        print(fmt(r))
    total = len(bad) + sum(extra.values())
    exact = sum(1 for r in rows if r["differ"] == 0 and r["extra"] == 0)
    print("total: %d/%d words differ%s, %d/%d regions EXACT  (%.1fs)"
          % (len(bad), size // 4, " (+%d extra)" % sum(extra.values()) if extra else "", exact, len(rows),
             time.time() - t0))
    if a.words:
        print("differing retail words:", " ".join(str(i) for i in sorted(bad)))
    if a.record:
        record(board_dir, name, va, size, rows, total, cand, a.record, repo, draft_file)


if __name__ == "__main__":
    main()
