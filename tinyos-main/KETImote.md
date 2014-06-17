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
make tmote reinstall,<node num> /dev/ttyUSB0
```

`<node num>` should be unique for this mote and is just an arbitrary integer (2 or greater. 1 is reserved). Write this down and label the
mote with it so that you know which mote is which ID. The above command flashed the mote, and if all was
successful, you should see something like 

```
Mass Erase...
Transmit default password...
... more stuff here
Reset device...
etc...
```

## Talking to Motes

Get a Telos mote or attach one of the KETI boards to programmer and plug it in to your computer (if you are using Virtualbox, you will have
to do the trick where you halt the VM, add the USB device, and then restart the VM.

We are going to flash our mote with the ability to act as a router between the motes and our computer. Go to the `PppRouter` application:

```
cd $TOSROOT/apps/PppRouter
make tmote blip
```

Unplug any other programmers from your computer, and then to install, run

```
make tmote reinstall,1 /dev/ttyUSB0
```

Keep the mote plugged in, but in a separate window, run (as root)

```
pppd debug passive noauth nodetach 115200 /dev/ttyUSB0 nocrtscts nocdtrcts lcp-echo-interval 0 noccp noip ipv6 ::23,::24
```

This will not exit, but if it is successful, you should see some output like

```
[bunch of stuff here]
Script /etc/ppp/ipv6-up started (pid 3033)
Script /etc/ppp/ipv6-up finished (pid 3033), status = 0x0
```

Then in another window, run

```
sudo ifconfig ppp0 add fec0::100/64
```

which should exit cleanly. When you run `ifconfig`, you should see `ppp0` as an interface now.

Eventually, I plan on having some cleaner code to help read the output of these motes, but for now, go to `UDPEcho_TH_CO2/util` folder
and look at the `Listener.py` file. We will run the Listener script with an argument that tells it which USB device to read output from.
This USB device should be the `/dev/ttyUSB` where the Telos is.

```
cd $TOSROOT/apps/UDPEcho_TH_CO2/util
python Listener.py serial@/dev/ttyUSB0:tmote
```

You should see some output from this.
