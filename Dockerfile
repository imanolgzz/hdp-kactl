FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    vim \
    git \
    build-essential \
    python3 \
    texlive-latex-base \
    texlive-latex-extra \
    texlive-fonts-recommended \
    texlive-fonts-extra \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
CMD ["/bin/bash"]
