#!/usr/bin/env python3
"""download_tools.py — fetch the build's compilers and loader into local/ and verify them.

The compilers are not redistributed here. Every one the build pins (the `@compiler` rows of
config/SLUS-20836/units.tsv, by SHA-256) is published in the decomp.me compiler distribution,
and the Win32 loader in the wibo releases; this downloads each archive, unpacks it to the path
the build expects and refuses any executable whose SHA-256 differs from the pinned one.

    python3 tools/download_tools.py            # everything missing
    python3 tools/download_tools.py --force    # re-download and re-check everything

local/ is gitignored. An existing file with the right digest is left alone.
"""
import argparse
import hashlib
import io
import os
import stat
import sys
import tarfile
import urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
COMPILERS = "https://github.com/decompme/compilers/releases/download/compilers/"
WIBO = ("https://github.com/decompals/wibo/releases/download/1.2.0/wibo-x86_64", "local/wibo",
        "13f86a2d618f0dbe67179d349625345eabf9b46450295cb4c904e49f6aff85af")
# units.tsv compiler id -> the decomp.me archive that holds it
ARCHIVES = {
    "default": "mwcps2-3.0-011126.tar.gz",
    "combat": "mwcps2-3.0b38-030307.tar.gz",
    "3.0.3": "mwcps2-3.0.3-020716.tar.gz",
    "b52": "mwcps2-3.0b52-030722.tar.gz",
    "2.4": "mwcps2-2.4-001213.tar.gz",
    "ee-gcc": "ee-gcc2.96.tar.xz",
    "ee-gcc-2.9": "ee-gcc2.9-991111-01.tar.xz",
    "ee-gcc-2.9-as210": "ee-gcc2.9-991111-01.tar.xz",
}
# an install that pairs one archive's compiler with another install's assembler: id -> the ee-as it uses
ASSEMBLERS = {
    "ee-gcc-2.9-as210": "local/ee-gcc2.96/bin/ee-as",
}


def pinned():
    """{id: (repository-relative executable, sha256)} from config/SLUS-20836/units.tsv."""
    out = {}
    for line in open(os.path.join(ROOT, "config", "SLUS-20836", "units.tsv")):
        if line.startswith("@compiler\t"):
            _tag, ident, path, digest = line.rstrip("\n").split("\t")[:4]
            out[ident] = (path, digest)
    return out


def sha256(path):
    with open(path, "rb") as fh:
        return hashlib.sha256(fh.read()).hexdigest()


def fetch(url):
    print(f"  downloading {url}")
    with urllib.request.urlopen(url) as response:
        return response.read()


def install(ident, path, digest, force):
    dest = os.path.join(ROOT, path)
    if not force and os.path.exists(dest) and sha256(dest) == digest and (
            ident not in ASSEMBLERS or os.path.exists(os.path.join(os.path.dirname(dest), "ee-as"))):
        print(f"{ident}: {path} present")
        return True
    archive = ARCHIVES[ident]
    data = fetch(COMPILERS + archive)
    # an ee-gcc install is the whole toolchain tree (bin/, lib/, ee/); an MWCC build is one folder
    root = os.path.join(ROOT, os.path.dirname(os.path.dirname(path))) if ident.startswith("ee-gcc") \
        else os.path.join(ROOT, os.path.dirname(path))
    os.makedirs(root, exist_ok=True)
    with tarfile.open(fileobj=io.BytesIO(data)) as tar:
        tar.extractall(root, filter="data")
    if not os.path.exists(dest) or sha256(dest) != digest:
        print(f"{ident}: {archive} did not produce {path} with SHA-256 {digest}", file=sys.stderr)
        return False
    os.chmod(dest, os.stat(dest).st_mode | stat.S_IXUSR)
    if ident in ASSEMBLERS:
        link = os.path.join(os.path.dirname(dest), "ee-as")
        if os.path.lexists(link):
            os.remove(link)
        os.symlink(os.path.relpath(os.path.join(ROOT, ASSEMBLERS[ident]), os.path.dirname(dest)), link)
    print(f"{ident}: {path} installed and verified")
    return True


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--force", action="store_true", help="download again even when present")
    args = ap.parse_args(argv)
    ok = True
    url, path, digest = WIBO
    dest = os.path.join(ROOT, path)
    if args.force or not os.path.exists(dest) or sha256(dest) != digest:
        data = fetch(url)
        if hashlib.sha256(data).hexdigest() != digest:
            print(f"wibo: {url} has an unexpected SHA-256", file=sys.stderr)
            ok = False
        else:
            os.makedirs(os.path.dirname(dest), exist_ok=True)
            with open(dest, "wb") as fh:
                fh.write(data)
            os.chmod(dest, 0o755)
            print(f"wibo: {path} installed and verified")
    else:
        print(f"wibo: {path} present")
    for ident, (path, digest) in pinned().items():
        if ident not in ARCHIVES:
            print(f"{ident}: no known download for {path}; supply it by hand", file=sys.stderr)
            ok = False
            continue
        ok = install(ident, path, digest, args.force) and ok
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
