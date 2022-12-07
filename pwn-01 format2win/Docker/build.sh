#!/bin/bash
docker rm -f format2win
docker build --tag=format2win . && \
docker run -p 9001:9001 --privileged=true --restart=on-failure --name=format2win --detach format2win