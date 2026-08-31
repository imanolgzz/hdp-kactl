#!/usr/bin/env bash
set -e

docker build -t reference-env .
docker run --rm -v "$(pwd)":/workspace reference-env make kactl
