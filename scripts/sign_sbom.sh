#!/bin/bash
set -e
KEY_FILE=${SBOM_SIGNING_KEY:-keys/signing/sbom-signing.key}
CERT_FILE=${SBOM_SIGNING_CERT:-keys/signing/sbom-signing.crt}

echo "[1/2] Signing SBOM with CycloneDX-CLI..."
cyclonedx sign bom \
  --key-file $KEY_FILE \
  --certificate-file $CERT_FILE \
  sbom/holistic-sbom.json \
  --output sbom/holistic-sbom-signed.json

echo "[2/2] Verifying signature..."
cyclonedx verify bom \
  --key-file keys/public/sbom-public.pem \
  sbom/holistic-sbom-signed.json

echo "[DONE] SBOM signed: sbom/holistic-sbom-signed.json"
