#!/usr/bin/env python3
"""full_verify.py DRAFT.cpp [--diagnose] : the complete oracle for the dispatcher draft.

Runs tools/verify.py with the draft's ownership overlay (tools/dispatcher/unit-objects.json;
its entry moves to config/SLUS-20836/unit-objects.json when the function is banked). A pass
requires, all at once: the owner's 41,864 code bytes, nine compiler-emitted duplicate
bodies (each against the retail unit it was kept from, under that unit's own compiler
profile), both switch tables (0x519310, 0x519370), the exception index record
(0x553b80) and the exception table (0x544fd4, 416 bytes).

--diagnose also appends the per-entry table report of table_diff.py (case labels that moved, exception
ranges/actions that differ) and ends with a VERDICT line.

--diagnose also reports the non-code regions while the code is still the wrong length:
the owner's retail extent is replaced by the draft's own size in a scratch symbol map.
Everything else is judged as usual, and the index record carries the code size, so a
diagnosed run can never report MATCH while the length differs. Run from the repo root."""
import argparse, os, re, subprocess, sys, tempfile

COMPILER, FLAGS = 'local/mwcps2/combat/mwccps2.exe', '-O3,p -Iinclude'


def run(draft, symbols=None):
    cmd = [sys.executable, 'tools/verify.py', '0x3fca10', draft, '--flags', FLAGS, '--mwcc', COMPILER,
           '--unit-objects', 'tools/dispatcher/unit-objects.json']
    if symbols:
        cmd += ['--symbols', symbols]
    r = subprocess.run(cmd, capture_output=True, text=True)
    return r.returncode, r.stdout + r.stderr


def main():
    ap = argparse.ArgumentParser(); ap.add_argument('draft'); ap.add_argument('--diagnose', action='store_true')
    ap.add_argument('--no-detail', action='store_true', help='with --diagnose, skip the per-entry table report')
    a = ap.parse_args()
    code, out = run(a.draft)
    m = re.search(r'emitted extent differs for Gap__Bec__beNDMWGameRam__vfunc_34: object symbol (\d+) bytes', out)
    if a.diagnose and m:
        print('diagnostic run: draft body is %s bytes, retail is 41864' % m.group(1))
        text = open('config/SLUS-20836/symbols.txt').read().replace('003fca10 00a388', '003fca10 %06x' % int(m.group(1)), 1)
        with tempfile.TemporaryDirectory(prefix='ownership-') as d:
            open(os.path.join(d, 'symbols.txt'), 'w').write(text)
            open(os.path.join(d, 'jumptables.txt'), 'w').write(open('config/SLUS-20836/jumptables.txt').read())
            code, out = run(a.draft, os.path.join(d, 'symbols.txt'))
        code = code or 1
    lines = [l for l in out.splitlines() if not re.match(r'^\s*(!!)?\s*\[\s*\d+\]|^\s+body 0x|^\s+(jump table|exception \w+) \[', l)]
    print('\n'.join(lines))
    text = '\n'.join(lines)
    if re.search(r'missing emitted function|additional \.text bytes|unresolved relocation', text):
        print('HINT: the object emitted a different set of bodies than tools/dispatcher/unit-objects.json declares. '
              'The cleanup helpers (RecoveryTarget::release, RecoveryString::release and the RecoveryRef/RecoveryString '
              'destructors) must stay real static members, and #pragma inline_depth(1) must stay at the top so they are '
              'not inlined into the callback; a new class or helper that calls them (or an unused inline member) adds '
              'bodies or removes the expected ones.')
    if a.diagnose and not a.no_detail:
        print('\n-- per-entry report of the switch tables and exception data (tools/dispatcher/table_diff.py) --')
        try:
            sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
            import table_diff
            tables_exact = table_diff.analyse(a.draft)
            print('tables: ' + ('all three non-code regions exact' if tables_exact else 'NOT exact (see above)'))
        except (SystemExit, Exception) as error:  # the code verdict above stays authoritative
            print('table_diff unavailable: %s' % error)
    print('VERDICT: ' + ('MATCH (bankable: run bank.py)' if code == 0 else 'NOT YET'))
    return code


if __name__ == '__main__':
    sys.exit(main())
