#!/usr/bin/env bash

# fail on error
set -e
set -o pipefail

rm -rf /i/af/ports/build*/flex*

rm -f ${ASV_PLAT_PORTS}/bin/bison++ \
${ASV_PLAT_PORTS}/lib/bison.cc \
${ASV_PLAT_PORTS}/lib/bison.h \
${ASV_PLAT_PORTS}/man/bison++.1 \
${ASV_PLAT_PORTS}/man/bison++.1.dman
