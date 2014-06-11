If you are looking to flash KETI motes, the simplest way to get started is to install [docker](http://www.docker.com/)
and to use the Dockerfile in this directory

```
sudo docker build -t keti .
sudo docker run -i -t keti # this will give you a bash prompt
```

Once inside the prompt, go to `/root/KMEG/tinyos-main/apps` and run `make epic blip`. The KETI-mote sensor program is in
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
