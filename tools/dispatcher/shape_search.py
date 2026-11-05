#!/usr/bin/env python3
"""shape_search.py MODE FUNCTION CANDIDATE [options]

Source-shape search for one unmatched function against the retail words, under the default compiler and the pinned alternate compiler
at several flag sets (it never reads or writes config/unit-*.tsv; the six profiles are fixed below).

Modes
  try    FUNCTION CAND            exact verify of one candidate under all profiles: MATCH / N differing words / size mismatch
  diff   FUNCTION CAND --profile "alt -O3,p"
                                  unified diff of the disassembly, retail against ours, branch targets masked
  alts   FUNCTION TEMPLATE        TEMPLATE holds groups  [[option A@@option B@@option C]]  (any number of groups). The product of the
                                  options (at most --max, random sample beyond that) is compiled under --profiles; results are ranked
                                  by (mnemonic edit distance of the whole function, number of differing operands). Edit distance 0 means
                                  the control flow and instruction mix are right; operands then show registers / relocation placeholders.
                                  An exact verify is run for the best entries and a MATCH is written to TEMPLATE.best
  perm   FUNCTION TEMPLATE        lines between //DECLS and //END (declarations) are permuted (random sample beyond --max); ranked by
                                  exact verify word count

Profiles: "def -O3", "def -O3,p", "def -O4", "def -O4,p", "alt -O3", "alt -O3,p", "alt -O4", "alt -O4,p" (def = tools/verify.py's
default compiler, alt = local/mwcps2/combat/mwccps2.exe). Several are separated by ';'.

Rules of thumb collected with it: the mnemonic score finds the control-flow spelling first
(loop form, early return, `(x != 0) ^ 1`, `(c ? 1 : 0)`, `0 < n`), the exact word count then finds registers and stack layout
(declaration order, volatile reads that fix a load order, padding structs).  Output files go to /tmp/shape_search_<pid>.
"""
import argparse, atexit, difflib, itertools, os, random, re, shutil, subprocess, sys
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import verify  # noqa: E402

ALT = os.path.join(ROOT, "local", "mwcps2", "combat", "mwccps2.exe")
PROFILES = {}
for _lab, _exe in (("def", verify.MWCC_DEFAULT), ("alt", ALT)):
    for _fl in ("-O3", "-O3,p", "-O4", "-O4,p"):
        PROFILES["%s %s" % (_lab, _fl)] = (_exe, _fl)
EMPTY = "/tmp/shape_search_empty.tsv"
WORK = "/tmp/shape_search_%d" % os.getpid()
BRANCH = ("b", "beq", "bne", "beqz", "bnez", "bgez", "bltz", "blez", "bgtz", "j", "jal", "bc1t", "bc1f")


def setup(function):
    open(EMPTY, "a").close()
    os.makedirs(WORK, exist_ok=True)
    atexit.register(shutil.rmtree, WORK, True)
    by_name, _ = verify.load_symbols(os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt"))
    if function.startswith("0x"):
        va = int(function, 16)
        _, by_va = verify.load_symbols(os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt"))
        function = by_va[va][0]
    else:
        va = by_name[function][0]
    return function, va


def exact(va, path, profile):
    exe, fl = PROFILES[profile]
    try:
        ok, rep = verify.verify_one(va, path, flags=fl + " -Iinclude", mwcc=exe,
                                    unit_flags=EMPTY, unit_compilers=EMPTY)
    except Exception as error:  # noqa: BLE001
        return 999, "error %s" % error
    if ok:
        return 0, "MATCH"
    if "compile failed" in rep:
        return 998, "compile failed"
    n = len(re.findall(r"retail [0-9a-f]{8}  ours", rep))
    m = re.search(r"size: retail (\d+), ours (\d+)", rep)
    return n, "%d words%s" % (n, " size %s/%s" % m.groups() if m else "")


def retail_text(function):
    asm = open(os.path.join(ROOT, "asm", function + ".s")).read()
    return [re.sub(r"\s+", " ", m.group(1)).strip() for m in re.finditer(r"/\* [0-9a-f]+: (.*?) \*/", asm)]


def disassemble(path, profile):
    exe, fl = PROFILES[profile]
    obj = path + ".o"
    r = subprocess.run([os.path.join(ROOT, "local", "wibo"), exe, "-c", *fl.split(), "-Iinclude", path, "-o", obj],
                       capture_output=True, text=True, cwd=ROOT)
    if r.returncode or not os.path.exists(obj):
        return None
    out = subprocess.run(["mipsel-linux-gnu-objdump", "-d", obj], capture_output=True, text=True).stdout
    os.remove(obj)
    ours = []
    for line in out.splitlines():
        m = re.match(r"\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(.*)", line)
        if m:
            ours.append(re.sub(r"\s+", " ", m.group(1).split("<")[0]).strip())
    return ours


def mask(ins):
    op = ins.split(" ")[0]
    if op in BRANCH or op == "lui":
        return re.sub(r"(0x[0-9a-f]+|-?\d+)$", "N", ins)
    return ins


def structural(retail, ours):
    rm = [x.split(" ")[0] for x in retail]
    om = [x.split(" ")[0] for x in ours]
    sm = difflib.SequenceMatcher(None, rm, om, autojunk=False)
    edits = operands = 0
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != "equal":
            edits += max(i2 - i1, j2 - j1)
        else:
            operands += sum(1 for k in range(i2 - i1) if mask(retail[i1 + k]) != mask(ours[j1 + k]))
    return edits, operands


def expand(src):
    groups = [g.split("@@") for g in re.findall(r"\[\[(.*?)\]\]", src, re.S)]

    def render(choice):
        counter = [0]

        def rep(_m):
            k = counter[0]
            counter[0] += 1
            return groups[k][choice[k]]
        return re.sub(r"\[\[(.*?)\]\]", rep, src, flags=re.S)
    return groups, render


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("mode", choices=["try", "diff", "alts", "perm"])
    ap.add_argument("function")
    ap.add_argument("candidate")
    ap.add_argument("--profiles", default="alt -O3,p;alt -O3;def -O3;def -O3,p")
    ap.add_argument("--profile", default="alt -O3")
    ap.add_argument("--max", type=int, default=1500)
    ap.add_argument("--top", type=int, default=8)
    ap.add_argument("--verify", type=int, default=40, help="alts: exact-verify this many best-ranked entries")
    ap.add_argument("--jobs", type=int, default=8)
    a = ap.parse_args()
    function, va = setup(a.function)
    profiles = a.profiles.split(";")

    if a.mode == "try":
        with ThreadPoolExecutor(6) as ex:
            for prof, (_n, text) in zip(PROFILES, ex.map(lambda p: exact(va, a.candidate, p), PROFILES)):
                print("%-10s %s" % (prof, text))
        return

    if a.mode == "diff":
        ours = disassemble(os.path.abspath(a.candidate), a.profile)
        if ours is None:
            print("compile failed")
            return 1
        retail = retail_text(function)
        for line in difflib.unified_diff([mask(x) for x in retail], [mask(x) for x in ours], "retail", "ours", lineterm="", n=2):
            print(line)
        return

    src = open(a.candidate).read()
    ext = os.path.splitext(a.candidate)[1]
    random.seed(1)

    if a.mode == "alts":
        dm = re.search(r"//DECLS\n(.*?)//END\n", src, re.S)
        dperms = []
        if dm:       # a declaration block adds one more dimension: its permutations
            dlines = [l for l in dm.group(1).split("\n") if l.strip()]
            dperms = list(itertools.permutations(range(len(dlines))))
            if len(dperms) > 120:
                dperms = random.sample(dperms, 120)
            base = src
            src = base[:dm.start()] + "[[" + "@@".join("\n".join(dlines[k] for k in pm) + "\n" for pm in dperms) + "]]\n" + base[dm.end():]
        groups, render = expand(src)
        combos = list(itertools.product(*[range(len(g)) for g in groups]))
        if len(combos) > a.max:
            combos = random.sample(combos, a.max)
        retail = retail_text(function)

        def job(item):
            idx, (choice, prof) = item
            path = os.path.join(WORK, "a%d%s" % (idx, ext))
            open(path, "w").write(render(choice))
            ours = disassemble(path, prof)
            os.remove(path)
            return (structural(retail, ours) if ours else (9999, 9999)), choice, prof
        jobs = list(enumerate((c, p) for c in combos for p in profiles))
        with ThreadPoolExecutor(a.jobs) as ex:
            res = sorted(ex.map(job, jobs), key=lambda r: r[0])
        for score, choice, prof in res[:a.top]:
            print(score, prof, choice)
        def check(item):
            k, (score, choice, prof) = item
            path = os.path.join(WORK, "best%d%s" % (k, ext))
            open(path, "w").write(render(choice))
            n, _ = exact(va, path, prof)
            os.remove(path)
            return n, k, choice, prof
        with ThreadPoolExecutor(a.jobs) as ex:
            checked = list(ex.map(check, enumerate(res[:a.verify])))
        hits = sorted(c for c in checked if c[0] == 0)
        if hits:
            _, _, choice, prof = hits[0]
            open(a.candidate + ".best", "w").write(render(choice))
            print("MATCH under %s with %s -> %s.best" % (prof, choice, a.candidate))
        else:
            n, _, choice, prof = min(checked)
            open(a.candidate + ".near", "w").write(render(choice))
            print("best exact word count among the verified entries: %d under %s with %s -> %s.near" % (n, prof, choice, a.candidate))
        return

    # perm
    m = re.search(r"//DECLS\n(.*?)//END\n", src, re.S)
    lines = [l for l in m.group(1).split("\n") if l.strip()]
    perms = list(itertools.permutations(range(len(lines))))
    if len(perms) > a.max:
        perms = random.sample(perms, a.max)

    def job(item):
        idx, (perm, prof) = item
        path = os.path.join(WORK, "p%d%s" % (idx, ext))
        open(path, "w").write(src[:m.start()] + "\n".join(lines[k] for k in perm) + "\n" + src[m.end():])
        n, _ = exact(va, path, prof)
        os.remove(path)
        return n, perm, prof
    jobs = list(enumerate((p, prof) for p in perms for prof in profiles))
    with ThreadPoolExecutor(a.jobs) as ex:
        res = sorted(ex.map(job, jobs), key=lambda r: r[0])
    for n, perm, prof in res[:a.top]:
        print(n, prof, [lines[k].strip() for k in perm])


if __name__ == "__main__":
    sys.exit(main() or 0)
