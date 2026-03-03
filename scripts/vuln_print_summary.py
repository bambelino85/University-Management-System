#!/usr/bin/env python3
import json, sys
data = json.load(open('reports/vuln-report.json'))
matches = data.get('matches', [])
counts = {}
for m in matches:
    sev = m.get('vulnerability', {}).get('severity', 'Unknown')
    counts[sev] = counts.get(sev, 0) + 1
print(f'Total findings: {len(matches)}')
for s, n in sorted(counts.items()):
    print(f'  {s}: {n}')
