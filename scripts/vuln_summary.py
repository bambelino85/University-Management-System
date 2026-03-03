#!/usr/bin/env python3
import json, argparse, datetime

def generate(input_json, output_html):
    with open(input_json) as f:
        data = json.load(f)
    matches = data.get("matches", [])
    counts = {}
    for m in matches:
        sev = m.get("vulnerability", {}).get("severity", "Unknown")
        counts[sev] = counts.get(sev, 0) + 1

    rows = ""
    for m in matches:
        v = m.get("vulnerability", {})
        a = m.get("artifact", {})
        cve_id = v.get("id", "")
        nvd_url = f"https://nvd.nist.gov/vuln/detail/{cve_id}" if cve_id.startswith("CVE") else "#"
        rows += f"""<tr>
          <td><a href="{nvd_url}" target="_blank">{cve_id}</a></td>
          <td class="sev-{v.get('severity','unknown').lower()}">{v.get('severity','')}</td>
          <td>{a.get('name','')}</td>
          <td>{a.get('version','')}</td>
          <td>{str(v.get('description',''))[:100]}...</td>
        </tr>"""

    summary_rows = "".join(
        f"<tr><td>{sev}</td><td>{cnt}</td></tr>"
        for sev, cnt in sorted(counts.items())
    )

    html = f"""<!DOCTYPE html>
<html><head><meta charset="UTF-8">
<title>SBOM Vulnerability Report</title>
<style>
  body {{ font-family: Arial, sans-serif; margin: 40px; color: #222; }}
  h1 {{ color: #1F4E79; }} h2 {{ color: #2E75B6; }}
  table {{ border-collapse: collapse; width: 100%; margin-bottom: 30px; }}
  th {{ background: #1F4E79; color: white; padding: 8px 12px; text-align: left; }}
  td {{ border: 1px solid #ccc; padding: 7px 12px; }}
  tr:nth-child(even) {{ background: #f5f8fb; }}
  .sev-critical {{ background:#ff4d4d; color:white; font-weight:bold; }}
  .sev-high     {{ background:#ff9900; color:white; font-weight:bold; }}
  .sev-medium   {{ background:#ffd700; color:#333; }}
  .sev-low      {{ background:#90ee90; }}
  .sev-negligible {{ background:#e0e0e0; }}
</style></head><body>
<h1>SBOM Vulnerability Analysis Report</h1>
<p><strong>Generated:</strong> {datetime.datetime.utcnow().strftime("%Y-%m-%d %H:%M:%S")} UTC</p>
<p><strong>Total findings:</strong> {len(matches)}</p>
<h2>Severity Summary</h2>
<table><tr><th>Severity</th><th>Count</th></tr>{summary_rows}</table>
<h2>All Findings</h2>
<table><tr><th>CVE ID</th><th>Severity</th><th>Component</th><th>Version</th><th>Description</th></tr>
{rows}
</table></body></html>"""

    with open(output_html, "w") as f:
        f.write(html)
    print(f"[vuln_summary] Report written to {output_html} ({len(matches)} findings)")

if __name__ == "__main__":
    p = argparse.ArgumentParser()
    p.add_argument("--input",  required=True)
    p.add_argument("--output", required=True)
    args = p.parse_args()
    generate(args.input, args.output)
