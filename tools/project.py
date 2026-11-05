"""project.py — the build generator behind configure.py (the dtk-template layout for a PS2 ELF).

The template (github.com/encounter/dtk-template) keeps one folder per game version:
config/<GAMEID>/config.yml with symbols.txt, splits.txt and build.sha1, the private retail
executable in orig/<GAMEID>/, a configure.py that writes build.ninja, objdiff.json for the
diff tool and a progress report for decomp.dev. Its generator drives decomp-toolkit, which
only splits PowerPC DOL/REL files; here the same layout drives the repository's own MIPS
tools instead:

  check    tools/check.py (every unit verified byte-for-byte against retail)
  link     tools/layout.py + tools/linkgen.py + GNU ld + tools/linkcheck.py, then the merged
           load image is written to build/<GAMEID>/main.bin and compared with build.sha1
  objdiff  one objdiff unit per function: the base object is its definition compiled under its
           unit profile (config/<GAMEID>/units.tsv) exactly as tools/check.py extracts it, the
           target object its retail instructions with the relocations restored (tools/target_asm.py)
  report   objdiff-cli report generate -> build/<GAMEID>/report.json (the decomp.dev format)

config.yml is a flat `key: value` file with one nested `image:` block; the reader below
accepts exactly that subset, so no YAML package is needed.
"""
import hashlib
import json
import os
import shutil
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)

VERSIONS = ["SLUS-20836"]
DEFAULT_VERSION = "SLUS-20836"
DEFAULT_COMPILER = "local/mwcps2/3.0-011126/mwccps2.exe"
DEFAULT_FLAGS = "-O3 -Iinclude"
WIBO = "local/wibo"


def read_config(version):
    """config/<GAMEID>/config.yml -> dict (flat keys; `image` is a nested dict)."""
    path = os.path.join(ROOT, "config", version, "config.yml")
    out, block = {}, None
    for raw in open(path):
        line = raw.split(" #", 1)[0].rstrip() if not raw.lstrip().startswith("#") else ""
        if not line.strip():
            continue
        key, _, value = line.strip().partition(":")
        value = value.strip()
        if raw.startswith("  ") and block is not None:
            out[block][key] = value
        elif not value:
            block = key
            out[block] = {}
        else:
            block = None
            out[key] = value
    return out


def sha1_file(path):
    with open(path, "rb") as fh:
        return hashlib.sha1(fh.read()).hexdigest()


def write_image(version, linked):
    """Write the merged load image of `linked` (the relink) to build/<GAMEID>/main.bin and
    compare it with config/<GAMEID>/build.sha1, the way the template checks its DOL."""
    import linkcheck
    cfg = read_config(version)
    start, size = int(cfg["image"]["start"], 0), int(cfg["image"]["size"], 0)
    vma, data = linkcheck.section_bytes(linked)
    if vma != start or len(data) < size:
        raise SystemExit(f"{linked}: .text at 0x{vma:x}, {len(data)} bytes; expected 0x{start:x}, {size}")
    out = os.path.join(ROOT, "build", version, "main.bin")
    os.makedirs(os.path.dirname(out), exist_ok=True)
    with open(out, "wb") as fh:
        fh.write(data[:size])
    want, path = open(os.path.join(ROOT, "config", version, "build.sha1")).read().split()[:2]
    got = sha1_file(out)
    print(f"{path}: {'OK' if got == want else 'FAILED'}")
    return 0 if got == want else 1


def _units(cfg):
    """[(source path, [(name, va)])] for the version's source tree, in address order."""
    import units
    import verify
    symbols = os.path.join(ROOT, cfg["symbols"])
    by_name, _ = verify.load_symbols(symbols)
    by_file = {}
    for name, path in units.scan(os.path.join(ROOT, cfg["source"]), symbols,
                                 os.path.join(ROOT, cfg["unit_objects"])).items():
        if name in by_name:
            by_file.setdefault(os.path.relpath(path, ROOT), []).append((name, by_name[name][0]))
    return sorted(((path, sorted(fns, key=lambda f: f[1])) for path, fns in by_file.items()),
                  key=lambda item: item[1][0][1])


def compile_unit(version, name, source, out):
    """Compile one function the way tools/check.py does: its definition extracted from `source`
    (units.standalone; an emitted member builds its owner) under its unit profile."""
    import subprocess
    import cc
    import unitobjects
    import units
    import unitprofiles
    import verify
    cfg = read_config(version)
    symbols = os.path.join(ROOT, cfg["symbols"])
    # an emitted member builds its owner, under the owner's profile
    owner = unitobjects.source_owner(name, symbols, os.path.join(ROOT, cfg["unit_objects"]))
    va = verify.load_symbols(symbols)[0][owner][0]
    res = unitprofiles.resolve(va, DEFAULT_FLAGS, DEFAULT_COMPILER,
                               units=os.path.join(ROOT, cfg["splits"]) if "splits" in cfg else None,
                               unit_flags=os.path.join(ROOT, cfg["unit_flags"]),
                               unit_compilers=os.path.join(ROOT, cfg["unit_compilers"]), symbols=symbols)
    path, tmp = units.standalone(os.path.join(ROOT, source), name, symbols,
                                 os.path.join(ROOT, cfg["unit_objects"]))
    try:
        profile = unitprofiles.for_source(res.override or res.profile, path, DEFAULT_FLAGS, DEFAULT_COMPILER)
        os.makedirs(os.path.dirname(os.path.abspath(out)), exist_ok=True)
        env = dict(os.environ, MWCIncludes=os.path.join(ROOT, "src"))
        # Compile into a private directory, then move: wibo resolves paths case-insensitively,
        # so beModelCtrlAIMAP_X.o and beModelCtrlAIMap_X.o in one folder would overwrite each other.
        with tempfile.TemporaryDirectory(prefix="dw4_cc_") as tmpdir:
            stage = os.path.join(tmpdir, "unit.o")
            argv = cc.compile_argv(os.path.join(ROOT, WIBO), profile.compiler,
                                   unitprofiles.command_flags(profile), path, stage)
            code = subprocess.run(argv, env=env, cwd=ROOT).returncode
            if code == 0 and not os.path.exists(stage):
                print(f"cc: {name}: the compiler wrote no object", file=sys.stderr)
                code = 1
            if code == 0:
                shutil.move(stage, out)
        return code
    finally:
        if tmp:
            os.remove(tmp)


def extract_executable(cfg, iso_path, path):
    """Copy SYSTEM.CNF and the boot executable out of a disc image into the executable's folder.
    Another dump of the same release can differ elsewhere on the disc, so the identity that
    matters is the executable's own SHA-1 in config.yml."""
    sys.path.insert(0, os.path.join(ROOT, "port/tools"))
    from extract_iso import Iso
    iso = Iso(iso_path)
    try:
        entries = dict(iso.walk())
        files = {}
        for name in ("SYSTEM.CNF", cfg["boot_file"]):
            if name not in entries:
                raise SystemExit(f"{iso_path}: disc is missing {name}")
            entry = entries[name]
            files[name] = iso.read(entry["lba"], (entry["size"] + 2047) // 2048)[:entry["size"]]
    finally:
        iso.f.close()
    if cfg["boot_file"].encode() not in files["SYSTEM.CNF"]:
        raise SystemExit(f"{iso_path}: boot configuration names another executable")
    if hashlib.sha1(files[cfg["boot_file"]]).hexdigest() != cfg["hash"]:
        raise SystemExit(f"{iso_path}: the executable's SHA-1 differs from config.yml; "
                         "this is not the retail executable of this version")
    cnf = os.path.join(os.path.dirname(path), "SYSTEM.CNF")
    if os.path.exists(cnf) and open(cnf, "rb").read() != files["SYSTEM.CNF"]:
        raise SystemExit(f"{cnf}: differs from the disc's boot configuration")
    os.makedirs(os.path.dirname(path), exist_ok=True)
    for out, data in ((cnf, files["SYSTEM.CNF"]), (path, files[cfg["boot_file"]])):
        with open(out, "wb") as fh:
            fh.write(data)


def ensure_executable(version):
    """Make sure orig/<GAMEID>/<boot file> exists: extract it from a disc image placed in
    orig/<GAMEID>/ (any *.iso), as the template does with its disc. The executable's SHA-1 is
    checked against config.yml; the disc image may be deleted afterwards."""
    cfg = read_config(version)
    path = os.path.join(ROOT, cfg["object"])
    if os.path.exists(path):
        if sha1_file(path) != cfg["hash"]:
            raise SystemExit(f"{cfg['object']}: SHA-1 differs from config/{version}/config.yml; "
                             "this is not the retail executable of this version")
        return
    folder = os.path.dirname(path)
    discs = sorted(f for f in os.listdir(folder) if f.lower().endswith(".iso")) if os.path.isdir(folder) else []
    if not discs:
        raise SystemExit(f"{cfg['object']} is missing: put your {cfg['name']} disc image (.iso) in "
                         f"orig/{version}/ and run configure.py again (see docs/build-system.md)")
    print(f"configure: extracting {cfg['boot_file']} from orig/{version}/{discs[0]}")
    extract_executable(cfg, os.path.join(folder, discs[0]), path)


def generate(version, verbose=False):
    """Write build.ninja and objdiff.json for `version`."""
    import ninja_syntax
    ensure_executable(version)
    cfg = read_config(version)
    # asm/ (the objdiff targets' input) is generated from the executable and never committed
    subprocess.check_call([sys.executable, os.path.join(HERE, "split.py"), "--ensure",
                           "--elf", os.path.join(ROOT, cfg["object"])])
    build = os.path.join("build", version)
    lines = []
    n = ninja_syntax.Writer(_Lines(lines), width=120)
    n.comment(f"GENERATED by configure.py --version {version}; do not edit.")
    n.variable("ninja_required_version", "1.3")
    n.variable("python", sys.executable if verbose else "python3")
    n.newline()
    n.rule("check", "$python tools/split.py --ensure --elf {0} && $python tools/check.py --elf {0}".format(cfg["object"]),
           description="CHECK every unit against retail", pool="console")
    n.rule("link", " && ".join([
        "$python tools/layout.py >/dev/null", "$python tools/linkgen.py --all",
        "mipsel-linux-gnu-ld -T build/link.ld -G0 --no-warn-mismatch -o build/game.elf",
        "$python tools/linkcheck.py build/game.elf",
        f"$python tools/project.py image --version {version} build/game.elf"]),
           description="LINK and compare the merged image", pool="console")
    n.rule("progress", "$python tools/progress.py",
           description="PROGRESS")
    n.rule("cc", f"$python tools/project.py cc --version {version} $name $in $out", description="CC $out")
    n.rule("as", "mipsel-linux-gnu-as -march=r5900 -EL -o $out $in", description="AS $out")
    n.rule("target_asm", "$python tools/target_asm.py $out $names $base",
           description="TARGET $out")
    n.rule("report", "objdiff-cli report generate -p . -o $out", description="REPORT $out",
           pool="console")
    n.newline()
    n.build("check", "phony", "build/.check")
    n.build("build/.check", "check")
    n.build("link", "phony", "build/.link")
    n.build("build/.link", "link")
    n.build("progress", "phony", "build/.progress")
    n.build("build/.progress", "progress")
    units, objects = [], []
    sources = _units(cfg)
    verified = _categories()
    for source, fns in sources:
        for name, va in fns:
            if verified.get(name) == "asm-body":
                continue
            base = f"{build}/obj/base/{name}.o"
            target_s, target = f"{build}/obj/target/{name}.s", f"{build}/obj/target/{name}.o"
            n.build(base, "cc", source, implicit=["tools/project.py"], variables={"name": name})
            n.build(target_s, "target_asm", f"asm/{name}.s", implicit=["tools/target_asm.py", cfg["symbols"], base],
                    variables={"names": name, "base": f"--base {base}"})
            n.build(target, "as", target_s)
            objects += [base, target]
            units.append({"name": f"{os.path.splitext(source)[0]}/{name}" if len(fns) > 1
                          else os.path.splitext(source)[0],
                          "target_path": target, "base_path": base,
                          "metadata": {"source_path": source, "complete": verified.get(name) == "match",
                                       "progress_categories": [_category(source)],
                                       "auto_generated": source.startswith("src/unmatched/")}})
    # functions with no source yet, and asm bodies, which compile to the target by construction and
    # would read as matched: target-only units, so the report's total is the whole image
    import verify
    by_name, _ = verify.load_symbols(os.path.join(ROOT, cfg["symbols"]))
    have = {name for _source, fns in sources for name, _va in fns if verified.get(name) != "asm-body"}
    for name, (va, _size) in sorted(by_name.items(), key=lambda kv: kv[1][0]):
        if name in have:
            continue
        target_s, target = f"{build}/obj/target/asm/{name}.s", f"{build}/obj/target/asm/{name}.o"
        n.build(target_s, "target_asm", f"asm/{name}.s", implicit=["tools/target_asm.py", cfg["symbols"]],
                variables={"names": name})
        n.build(target, "as", target_s)
        objects.append(target)
        units.append({"name": f"asm/{name}", "target_path": target,
                      "metadata": {"complete": False, "progress_categories": ["unmatched"]}})
    n.build("objdiff", "phony", objects)
    n.build(f"{build}/report.json", "report", objects + ["objdiff.json"])
    n.build("report", "phony", f"{build}/report.json")
    n.default("link")
    with open(os.path.join(ROOT, "build.ninja"), "w") as fh:
        fh.write("".join(lines))
    project = {"$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
               "custom_make": "ninja", "custom_args": ["objdiff"], "build_target": False,
               "build_base": True, "watch_patterns": ["*.c", "*.cpp", "*.h", "*.inc"],
               "progress_categories": [{"id": c, "name": c} for c in CATEGORIES],
               "units": units}
    with open(os.path.join(ROOT, "objdiff.json"), "w") as fh:
        json.dump(project, fh, indent=1)
        fh.write("\n")
    print(f"configure: {version} ({cfg['name']}): build.ninja, objdiff.json ({len(units)} units)")


CATEGORIES = ["game", "engine", "sdk", "unmatched"]


def _categories():
    """{name: category} from the last complete `make check` (data/check-categories.tsv)."""
    out = {}
    path = os.path.join(ROOT, "data", "check-categories.tsv")
    if os.path.exists(path):
        for line in open(path):
            if line.startswith("#"):
                continue
            parts = line.rstrip("\n").split("\t")
            if len(parts) >= 3:
                out[parts[1]] = parts[2]
    return out


def _category(source):
    parts = source.split("/")
    if len(parts) > 1 and parts[1] in ("game", "engine"):
        return parts[1]
    if len(parts) > 1 and parts[1] in ("sdk", "asmbody"):
        return "sdk"
    return "unmatched"


class _Lines:
    def __init__(self, lines):
        self.lines = lines

    def write(self, text):
        self.lines.append(text)


def main(argv):
    if argv[:1] == ["cc"]:
        version = argv[argv.index("--version") + 1]
        name, source, out = argv[3:6]
        return compile_unit(version, name, source, out)
    if argv[:1] == ["image"]:
        version = argv[argv.index("--version") + 1]
        return write_image(version, argv[-1])
    raise SystemExit("usage: project.py image --version GAMEID LINKED | cc --version GAMEID NAME SOURCE OUT")


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
