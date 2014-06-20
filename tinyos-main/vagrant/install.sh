# install required apt packages
for package in git vim emacs automake bison flex gperf build-essential libfuse2 python-dev python-pip autoconf2.64 openjdk-6-jre openjdk-6-jdk gcc-msp430; do
    if ! dpkg -s $package ; then
        echo $package "is not installed. Attempting to install"
        sudo apt-get install -y $package  
    fi
done

# install python packages
pip list | grep -i twisted
if [ $? -eq 0 ] ; then
    sudo pip install --upgrade twisted
fi

echo "Setting $HOME to " `pwd`
export HOME=`pwd`
git clone git://github.com/tinyos/nesc.git
cd nesc
./Bootstrap
./configure
make
sudo make install

cd ..
git clone https://github.com/SoftwareDefinedBuildings/KMEG.git -b KMEG-blip
cd KMEG/tinyos-main/tools
./Bootstrap
./configure
make
sudo make install

cd ..

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
