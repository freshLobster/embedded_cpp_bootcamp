#!/usr/bin/env python3
import os
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

link_re = re.compile(r"\[[^\]]+\]\(([^)]+)\)")


def is_local(link: str) -> bool:
    return not (link.startswith("http://") or link.startswith("https://") or link.startswith("mailto:"))


def normalize(link: str) -> str:
    # strip anchors
    return link.split("#")[0]


def main() -> int:
    failures = []
    md_files = list(ROOT.rglob("*.md"))
    for md in md_files:
        text = md.read_text(encoding="utf-8", errors="ignore")
        for match in link_re.findall(text):
            link = match.strip()
            if not is_local(link):
                continue
            link = normalize(link)
            if not link:
                continue
            target = (md.parent / link).resolve()
            if not target.exists():
                # also allow root-relative without leading ./ by checking from repo root
                alt = (ROOT / link).resolve()
                if not alt.exists():
                    failures.append(f"{md.relative_to(ROOT)} -> {link}")

    if failures:
        print("Broken links:")
        for f in failures:
            print("  -", f)
        return 1

    print("OK: no broken local markdown links")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
