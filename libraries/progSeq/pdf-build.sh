#!/bin/sh
doxygen
docker run --rm -it -v $(pwd)/documentation/latex:/sources pdflatex-make make
mv ./documentation/latex/refman.pdf ./ProgSeq_reference.pdf
cp ./ProgSeq_reference.pdf ../../ProgSeq_reference.pdf