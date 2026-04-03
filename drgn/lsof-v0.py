#!/usr/bin/env drgn

import sys
import argparse
from drgn.helpers.linux import (find_task, fget)
from drgn import (FaultError)

parser = argparse.ArgumentParser()

parser.add_argument("pid", type=int)
parser.add_argument("--fd", type=int, required=False, default=False)

args = parser.parse_args()

t = find_task(args.pid)
if not t:
    sys.exit(f"no task for {args.pid}")

for i in range(1024):
    if args.fd == False or args.fd == i:
        f = fget(t, i)
        if f:
            try:
                name = f.f_path.dentry.d_name.name
                print(f'{i:5}, {name.string_().decode()}')
            except:
                print(f'{i:5}, ???')
