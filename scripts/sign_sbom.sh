#!/bin/bash
set -e
KEY_FILE=${SBOM_SIGNING_KEY:-keys/signing/sbom-rsa-signing.key}
PUB_KEY=${SBOM_PUBLIC_KEY:-keys/public/sbom-rsa-public.pem}

echo "[1/3] Converting SBOM to XML..."
cyclonedx convert \
  --input-file sbom/holistic-sbom.json \
  --input-format json \
  --output-file sbom/holistic-sbom.xml \
  --output-format xml

echo "[2/3] Signing SBOM (XML)..."
cp sbom/holistic-sbom.xml sbom/holistic-sbom-signed.xml
cyclonedx sign bom sbom/holistic-sbom-signed.xml \
  --key-file $KEY_FILE

echo "[3/3] Verifying signature..."
cyclonedx verify all sbom/holistic-sbom-signed.xml \
  --key-file $PUB_KEY

echo "[DONE] Signed SBOM: sbom/holistic-sbom-signed.xml"
