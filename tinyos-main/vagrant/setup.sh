echo "MAKE SURE YOU ARE ROOT. Waiting 5 seconds"
sleep 5
export HOME=/home/vagrant
sudo apt-get update
sudo apt-get install -y git vim emacs automake bison flex gperf build-essential libfuse2 python-dev python-pip
sudo apt-get install autoconf2.64 # sometimes this older version is needed
sudo pip install --upgrade twisted

# make a fuse install for java
cd /tmp
sudo apt-get download fuse
sudo dpkg-deb -x fuse_* .
sudo dpkg-deb -e fuse_*
sudo rm fuse_*.deb
sudo echo -en '#!/bin/bash\nexit 0\n' > DEBIAN/postinst
sudo dpkg-deb -b . /fuse.deb
sudo dpkg -i /fuse.deb

# install java
sudo apt-get install -y openjdk-6-jre openjdk-6-jdk

# install nesC

cd "$HOME"
git clone git://github.com/tinyos/nesc.git 
cd nesc
sudo ./Bootstrap
sudo ./configure
sudo make
sudo make install

# install TinyOS -- KMEG-blip branch
cd "$HOME"
git clone https://github.com/SoftwareDefinedBuildings/KMEG.git -b KMEG-blip
cd KMEG/tinyos-main/tools
sudo ./Bootstrap
sudo ./configure
sudo make
sudo make install

# install platform compilers
sudo apt-get install -y gcc-msp430


cd "$HOME/KMEG/tinyos-main"
export TOSROOT=`pwd`
export TOSDIR="$TOSROOT/tos"
export MAKERULES="$TOSROOT/support/make/Makerules"
export CLASSPATH="$TOSROOT/support/sdk/java/tinyos.jar:."
export PYTHONPATH="$TOSROOT/support/sdk/python:$PYTHONPATH"
export PATH="$TOSROOT/support/sdk/c:$PATH"
export PATH="$TOSROOT/tools/platforms/msp430/motelist:$PATH"
export PATH="$TOSROOT/tools/platforms/msp430/pybsl:$PATH"
sudo chmod +x "$TOSROOT/tools/platforms/msp430/motelist/motelist"
sudo chmod +x "$TOSROOT/tools/platforms/msp430/pybsl/tos-bsl"
