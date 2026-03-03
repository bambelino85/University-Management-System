FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive

# Base build tools
RUN apt-get update && apt-get install -y \
    build-essential cmake git wget curl \
    python3 python3-pip pipx \
    apt-transport-https gnupg lsb-release \
    openssl ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Install Trivy
RUN wget -qO - https://aquasecurity.github.io/trivy-repo/deb/public.key | apt-key add - \
    && echo "deb https://aquasecurity.github.io/trivy-repo/deb jammy main" \
       > /etc/apt/sources.list.d/trivy.list \
    && apt-get update && apt-get install -y trivy \
    && rm -rf /var/lib/apt/lists/*

# Install Syft
RUN curl -sSfL https://raw.githubusercontent.com/anchore/syft/main/install.sh \
    | sh -s -- -b /usr/local/bin

# Install Grype
RUN curl -sSfL https://raw.githubusercontent.com/anchore/grype/main/install.sh \
    | sh -s -- -b /usr/local/bin

# Install CycloneDX-CLI
RUN wget -q https://github.com/CycloneDX/cyclonedx-cli/releases/download/v0.30.0/cyclonedx-linux-x64 \
    -O /usr/local/bin/cyclonedx && chmod +x /usr/local/bin/cyclonedx

# Install Hoppr and symlink as hoppr
RUN pipx install hoppr \
    && ln -s /root/.local/share/pipx/venvs/hoppr/bin/hopctl /usr/local/bin/hoppr \
    && ln -s /root/.local/share/pipx/venvs/hoppr/bin/hopctl /usr/local/bin/hopctl

# Install Flask for SBOM UI backend
RUN pip3 install flask flask-cors

# Verify all tools are present
RUN echo "=== Tool Verification ===" \
    && syft version \
    && grype version \
    && cyclonedx --version \
    && trivy --version \
    && hoppr -h 2>&1 | head -3 \
    && openssl version \
    && echo "=== All tools OK ==="

WORKDIR /workspace
COPY . .

# Build the C++ application
RUN mkdir -p build && cd build \
    && cmake .. -DCMAKE_BUILD_TYPE=Release \
    && make -j$(nproc)

CMD ["/bin/bash"]
