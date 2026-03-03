#!/usr/bin/env python3
import json, sys
f = sys.argv[1]
d = json.load(open(f))
d['specVersion'] = '1.4'
d.pop('annotations', None)
json.dump(d, open(f, 'w'), indent=2)
print(f'[patch] {f} specVersion set to 1.4')
