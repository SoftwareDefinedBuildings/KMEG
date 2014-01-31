#/bin/sh

mkdir /share/build_bin/
mkdir /share/build_bin/telosb
pushd build/telosb/
cp ident_flags.txt main.exe main.ihex tos_image.xml /share/build_bin/telosb

pushd /share
tar cvf build_bin.tar build_bin
gzip build_bin.tar

popd
popd

