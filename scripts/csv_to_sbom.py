#!/usr/bin/env python3
import csv, json, argparse, hashlib, datetime, uuid

def csv_to_cyclonedx(input_csv, output_json, version):
    components = []
    deps = []
    with open(input_csv) as f:
        reader = csv.DictReader(f)
        for row in reader:
            bom_ref = f"{row['name']}-{version}"
            comp = {
                "type": row["type"],
                "bom-ref": bom_ref,
                "name": row["name"],
                "version": row["version"],
                "supplier": {"name": row["supplier"]},
                "licenses": [{"license": {"id": row["license"]}}],
                "description": row["description"]
            }
            components.append(comp)
            if row["depends_on"]:
                deps.append({
                    "ref": bom_ref,
                    "dependsOn": [f"{d}-{version}" for d in row["depends_on"].split("|")]
                })
            else:
                deps.append({"ref": bom_ref, "dependsOn": []})

    sbom = {
        "bomFormat": "CycloneDX",
        "specVersion": "1.4",
        "version": 1,
        "serialNumber": f"urn:uuid:{uuid.uuid4()}",
        "metadata": {
            "timestamp": datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%SZ"),
            "tools": [{"name": "csv_to_sbom", "version": "1.0.0"}],
            "component": {
                "type": "application",
                "name": "University-Management-System",
                "version": version,
                "supplier": {"name": "bambelino85"}
            }
        },
        "components": components,
        "dependencies": deps
    }
    with open(output_json, "w") as f:
        json.dump(sbom, f, indent=2)
    print(f"[csv_to_sbom] Wrote {len(components)} components to {output_json}")

if __name__ == "__main__":
    p = argparse.ArgumentParser()
    p.add_argument("--input",   required=True)
    p.add_argument("--output",  required=True)
    p.add_argument("--version", default="1.0.0")
    args = p.parse_args()
    csv_to_cyclonedx(args.input, args.output, args.version)
