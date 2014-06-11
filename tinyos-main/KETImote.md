If you are looking to flash KETI motes, the simplest way to get started is to install [docker](http://www.docker.com/)
and to use the Dockerfile in this directory

```
sudo docker build -t keti .
sudo docker run -i -t keti # this will give you a bash prompt
```

Once inside the prompt, go to `/root/KMEG/tinyos-main/apps/UDPEcho_TH_CO2` and run `make tmote blip`. The KETI-mote sensor program is in
`/root/KMEG/tinyos-main/apps/UDPEcho_TH_CO2` and within that directory, you want `build/epic/main.ihex`.

To get the build file from the Docker file, run

```
sudo docker ps | grep keti
```

to get the ID of the running docker container. It should be some hex, something like 'e0a2b2c1f3bd'.
Run

```
sudo docker cp <docker id>:/root/KMEG/tinyos-main/apps/UDPEcho_TH_CO2/build/epic/main.ihex .
```

to get the file on your local computer.

Remember you need the correct environment 

go to the tinyos-main directory

```
export TOSROOT=`pwd`
export TOSDIR=$TOSROOT/tos
export MAKERULES=$TOSROOT/support/make/Makerules
export CLASSPATH=$TOSROOT/support/sdk/java/tinyos.jar:.
export PYTHONPATH=$TOSROOT/support/sdk/python:$PYTHONPATH
export PATH=$TOSROOT/support/sdk/c:$PATH
export PATH=$TOSROO
```

make epic blip reinstall,<node num> bsl,/dev/<usb device> # try w/o "bsl," ?

make sure to add the path var to include tinyos-main/tools/platforms/msp430/motelist/motelist
as well as tinyos-main/tools/platforms/msp430/pybsl/tos-bsl

make those binaries executable! chmod +x

make sure that /dev/ttyUSB0 is world-writeable (chmod 777 or whatever)

in vagrant, enable the serial ports as well as the usb port
