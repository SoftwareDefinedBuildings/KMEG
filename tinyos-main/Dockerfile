# A tinyOS 2.0 build environment
FROM stackbrew/ubuntu:saucy

MAINTAINER Michael Andersen <m.andersen@cs.berkeley.edu>

RUN apt-get update && apt-get dist-upgrade -y
RUN apt-get install -y git vim emacs automake bison flex gperf build-essential

# Fake a fuse install for java
RUN apt-get install libfuse2
RUN cd /tmp ; apt-get download fuse
RUN cd /tmp ; dpkg-deb -x fuse_* .
RUN cd /tmp ; dpkg-deb -e fuse_*
RUN cd /tmp ; rm fuse_*.deb
RUN cd /tmp ; echo -en '#!/bin/bash\nexit 0\n' > DEBIAN/postinst
RUN cd /tmp ; dpkg-deb -b . /fuse.deb
RUN cd /tmp ; dpkg -i /fuse.deb

# Install java
RUN apt-get install -y openjdk-7-jdk

# Install nesC
RUN git clone git://github.com/tinyos/nesc.git /root/nesc
RUN cd /root/nesc/ && ./Bootstrap
RUN cd /root/nesc/ && ./configure
RUN cd /root/nesc/ && make && make install

# Install TinyOS
#RUN git clone https://github.com/SoftwareDefinedBuildings/KETI.git /root/tinyos-main
RUN git clone https://github.com/SoftwareDefinedBuildings/KMEG.git -b KMEG-blip /root/KMEG
RUN cd /root/KMEG/tinyos-main/tools/ && ./Bootstrap
RUN cd /root/KMEG/tinyos-main/tools/ && ./configure
RUN cd /root/KMEG/tinyos-main/tools && make && make install

# Install platform compilers
RUN apt-get install -y gcc-msp430

# Setup environment variables
ENV TOSROOT     /root/KMEG/tinyos-main
ENV TOSDIR      /root/KMEG/tinyos-main/tos
ENV MAKERULES   /root/KMEG/tinyos-main/support/make/Makerules
ENV CLASSPATH   /root/KMEG/tinyos-main/support/sdk/java/tinyos.jar:.
ENV PYTHONPATH  /root/KMEG/tinyos-main/support/sdk/python:$PYTHONPATH
ENV PATH        /root/KMEG/tinyos-main/support/sdk/c:$PATH

# Setup working directory
WORKDIR         /root/KMEG/tinyos-main/

# We want to just bash in here
ENTRYPOINT      /bin/bash

