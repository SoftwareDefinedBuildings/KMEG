To facilitate creating a build/flash environment for KETImotes and tiny-os, I have put together
a provisioned VM for you to use. If you do not want to use a VM, like if you are already on Linux,
then you can just follow the instructions in the `vagrant/Vagrantfile` -- look at the top for the script.

If you do want to use a VM, install [vagrant](http://www.vagrantup.com/) and a backend for vagrant, like
[virtualbox](https://www.virtualbox.org/). You want a provider that allows you to enable/forward the USB
and serial ports on your computer to the virtual machine.

To build the virtual machine, go into the `vagrant/` directory and run

```
vagrant up
```

Depending on your internet connection, this should probably take around 15 minutes. You can watch the output.
When it has finished, run

```
vagrant halt
```

To shutdown the virtual machine. Open up your virtual machine provider and enable the serial ports and USB ports
for the virtual machine that Vagrant just created. If you are using VirtualBox, plug the programmer into
your computer (it is a small green piece of board with USB port on one end, and should say "KETI" on it somewhere).
Open VirtualBox, and find the virtual machine you just created. It will be in a 'shutdown' or 'powered off' state.
Select the VM and open the settings. Under the Ports menu, there should be two tabs for Serial Ports and USB. Under
Serial Ports, click "Enable Serial Port" for any and all Serial Ports listed. Under USB, click "Enable USB controller".
I have had problems with USB 2.0 support, so just ignore it for now (you do not need it). There should be a little icon
on the right-hand side that looks like a USB plug with a little green plus symbol. Click it and add the programmer. Click "OK"
and save any changes if it asks you.

Go back to the terminal in the `vagrant/` folder. Re-run `vagrant up`, which should go much faster this time. Then, login to
the machine by running

```
vagrant ssh
```

which should drop you into a shell prompt inside the VM. You should be at `/home/vagrant` and should see `KMEG` and
`nesc` folders. Run the following:

```
sudo su root # should be passwordless
cd /home/vagrant/KMEG/tinyos-main
export TOSROOT=`pwd`
export TOSDIR=$TOSROOT/tos
export MAKERULES=$TOSROOT/support/make/Makerules
export CLASSPATH=$TOSROOT/support/sdk/java/tinyos.jar:.
export PYTHONPATH=$TOSROOT/support/sdk/python:$PYTHONPATH
export PATH=$TOSROOT/support/sdk/c:$PATH
export PATH=$TOSROOT/tools/platforms/msp430/motelist:$PATH
export PATH=$TOSROOT/tools/platforms/msp430/pybsl:$PATH
chmod +x $TOSROOT/tools/platforms/msp430/motelist/motelist
chmod +x $TOSROOT/tools/platforms/msp430/pybsl/tos-bsl
```

Now, go to the apps folder for the KETI-motes. For the temperature/humidity/co2 sensors, this is `UDPEcho_TH_CO2`.

```
cd $TOSROOT/apps/UDPEcho_TH_CO2
make tmote blip
```

This should compile the application for the tmote/telosb architecture, and you can find the resulting app
in the `build/telosb` folder relative to your current path.

To install the app on a mote (e.g. 'flash the mote'), first do

```
ls /dev/ttyUSB*
```

which should PROBABLY give you `/dev/ttyUSB0`, which should be your programmer unit. Make this world writeable:

```
sudo chmod 777 /dev/ttyUSB0
```

Now, unplug the board from the KETImote and plug it into the programmer. Inside the `UDPEcho_TH_CO2` folder,
run 

```
make epic tmote reinstall,<node num> /dev/ttyUSB0
```

`<node num>` should be unique for this mote and is just an arbitrary integer. Write this down and label the
mote with it so that you know which mote is which ID. The above command flashed the mote, and if all was
successful, you should see something like 

```
Mass Erase...
Transmit default password...
... more stuff here
Reset device...
rm -rf bunch of stuff
```
