#!/usr/bin/env python3
"""bank.py DRAFT.cpp [--va 0x3fca10] [--keep] : bank a fully matching draft, or rehearse doing so.

Banking a function means: the C++ source in src/, its compiler pin (config/SLUS-20836/unit-compilers.tsv),
its flag row (config/SLUS-20836/unit-flags.tsv) and its ownership entry (config/SLUS-20836/unit-objects.json) -- the
last is taken from the draft's own overlay (tools/dispatcher/unit-objects.json), which is the
one that full_verify.py proved. Then `make check` (every function, zero mismatches) and
`make link` (byte-identical ELF) decide.

Default is a DRY RUN: the touched files are changed, both makes run, and every touched file is
restored byte for byte afterwards (also on error or Ctrl-C); the repository ends as it began.
--keep leaves the banked state in place when the report says BANKED OK (then review
`git diff` and commit). A pre-existing row for the address is replaced, never duplicated,
so the script can be rehearsed on an already banked function (give its own source as DRAFT).

Run from the repository root. Examples:
    python3 tools/dispatcher/full_verify.py tools/dispatcher/draft.cpp          # must say MATCH first
    python3 tools/dispatcher/bank.py tools/dispatcher/draft.cpp                 # rehearsal
    python3 tools/dispatcher/bank.py tools/dispatcher/draft.cpp --keep          # really bank
    python3 tools/dispatcher/bank.py src/unmatched/FUN_003fab90.cpp --va 0x3fab90 \\
        --overlay config/SLUS-20836/unit-objects.json --flags '-O3,p -Cpp_exceptions off -Iinclude'   # self-test

Exit status 0 only when check reports zero mismatches and link reports a byte-identical ELF."""
import argparse, hashlib, json, os, re, shutil, subprocess, sys, tempfile, time

SYMBOLS, COMPILERS, FLAGS_TSV, OBJECTS = ('config/SLUS-20836/symbols.txt', 'config/SLUS-20836/unit-compilers.tsv',
                                          'config/SLUS-20836/unit-flags.tsv', 'config/SLUS-20836/unit-objects.json')
TOUCHED = [COMPILERS, FLAGS_TSV, OBJECTS, 'config/SLUS-20836/layout.txt', 'config/SLUS-20836/symbols.txt']


def die(msg):
    print('bank: ' + msg, file=sys.stderr); sys.exit(2)


def symbol_name(va):
    for line in open(SYMBOLS):
        p = line.split()
        if len(p) >= 3 and not p[0].startswith('#') and int(p[0], 16) == va:
            return p[2]
    die('no symbol at 0x%x in %s' % (va, SYMBOLS))


def replace_rows(path, va, name, row, comment):
    """Drop every row keyed by va (and a directly preceding comment naming the function), append the new one."""
    key = '0x%08x' % va
    lines = open(path).read().split('\n')
    if lines and lines[-1] == '':
        lines.pop()
    out = []
    for ln in lines:
        if ln.split('\t')[0].strip().lower() == key:
            if out and out[-1].startswith('#') and name in out[-1]:  # its own comment, not a shared one
                out.pop()
            continue
        out.append(ln)
    out += ['', '# ' + comment, row]
    open(path, 'w').write('\n'.join(out) + '\n')


def make(target, jobs, log):
    t = time.time()
    r = subprocess.run(['make', '-j%d' % jobs, target], capture_output=True, text=True)
    open(log, 'w').write(r.stdout + r.stderr)
    return r.returncode, r.stdout + r.stderr, time.time() - t


def tail(text, n=8):
    return '\n'.join(text.rstrip().splitlines()[-n:])


def git_status():
    return subprocess.run(['git', 'status', '--porcelain'], capture_output=True, text=True).stdout


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument('draft')
    ap.add_argument('--va', default='0x3fca10')
    ap.add_argument('--name', help='symbol/file stem (default: from config/SLUS-20836/symbols.txt)')
    ap.add_argument('--flags', default='-O3,p -Iinclude')
    ap.add_argument('--compiler', default='local/mwcps2/combat/mwccps2.exe')
    ap.add_argument('--overlay', default='tools/dispatcher/unit-objects.json')
    ap.add_argument('--dest-dir', default='src/unmatched')
    ap.add_argument('--jobs', type=int, default=4)
    ap.add_argument('--keep', action='store_true', help='leave the banked state in place on success')
    ap.add_argument('--skip-link', action='store_true')
    a = ap.parse_args()
    va = int(a.va, 16)
    if not os.path.isfile('tools/verify.py'): die('run from the repository root')
    if not os.path.isfile(a.draft): die('no draft ' + a.draft)
    if not os.path.isfile(a.compiler): die('no compiler ' + a.compiler)
    name = a.name or symbol_name(va)
    dest = os.path.join(a.dest_dir, name + '.cpp')
    for ext in ('.c', '.inc'):  # one source per function (tools/srctree.py resolves by stem)
        if os.path.exists(os.path.join(a.dest_dir, name + ext)): die('conflicting source ' + name + ext)
    entry = json.load(open(a.overlay)).get('0x%08x' % va)
    if entry is None: die('overlay %s has no entry for 0x%08x' % (a.overlay, va))
    draft_text = open(a.draft).read()

    scratch = tempfile.mkdtemp(prefix='ownership-bank-')
    saved = {f: (open(f, 'rb').read() if os.path.exists(f) else None) for f in TOUCHED + [dest]}
    status0 = git_status()
    ok = False
    try:
        os.makedirs(a.dest_dir, exist_ok=True)
        open(dest, 'w').write(draft_text)
        digest = hashlib.sha256(open(a.compiler, 'rb').read()).hexdigest()
        replace_rows(COMPILERS, va, name, '0x%08x\t%s\t%s' % (va, a.compiler, digest),
                     '%s: banked by tools/dispatcher/bank.py.' % name)
        replace_rows(FLAGS_TSV, va, name, '0x%08x\t%s' % (va, a.flags), '%s: banked flags.' % name)
        objs = json.load(open(OBJECTS)); objs['0x%08x' % va] = entry
        open(OBJECTS, 'w').write(json.dumps(objs, indent=2) + '\n')
        print('bank: %s -> %s, flags %r, compiler pin %s..., %d emitted, %d duplicates, exceptions %s' % (
            a.draft, dest, a.flags, digest[:12], len(entry.get('emitted', {})),
            len(entry.get('duplicates', {})), 'yes' if entry.get('exceptions') else 'no'))

        rc, out, secs = make('check', a.jobs, os.path.join(scratch, 'check.log'))
        print('bank: make check rc=%d in %.0fs\n%s' % (rc, secs, tail(out, 6)))
        for l in [l for l in out.splitlines() if name in l or '%08x' % va in l.lower()][:12]:
            print('   check> ' + l.rstrip()[:200])
        mism = [int(m) for m in re.findall(r'(\d+)\s+mismatch', out, re.I)]
        check_ok = rc == 0 and not any(mism)
        link_ok = None
        if check_ok and not a.skip_link:
            rc2, out2, secs2 = make('link', a.jobs, os.path.join(scratch, 'link.log'))
            print('bank: make link rc=%d in %.0fs\n%s' % (rc2, secs2, tail(out2, 6)))
            link_ok = rc2 == 0
        elif not check_ok:
            print('bank: link skipped (check failed)')
        ok = check_ok and link_ok is not False
        print('bank: ' + ('BANKED OK (check clean%s)' % ('' if link_ok is None else ', ELF byte-identical')
                          if ok else 'NOT BANKABLE (logs in %s)' % scratch))
        return 0 if ok else 1
    finally:
        if a.keep and ok:
            print('bank: --keep: files left in place; review git diff and commit')
            shutil.rmtree(scratch, ignore_errors=True)
        else:
            for f, data in saved.items():
                if data is None:
                    if os.path.exists(f): os.remove(f)
                else:
                    open(f, 'wb').write(data)
            print('bank: restored; repository %s' % (
                'unchanged' if status0 == git_status() else 'DIFFERS from its pre-run state:\n' + git_status()))
            if ok: shutil.rmtree(scratch, ignore_errors=True)


sys.exit(main())
