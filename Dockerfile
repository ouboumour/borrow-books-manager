FROM ubuntu:20.04

RUN apt update
RUN apt install -y gcc libjson-c-dev make
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp