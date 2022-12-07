#!/bin/bash
docker rm -f rustystack
docker build --tag=rustystack . && \
docker run -p 9002:9002 --privileged=true --restart=on-failure --name=rustystack --detach rustystack