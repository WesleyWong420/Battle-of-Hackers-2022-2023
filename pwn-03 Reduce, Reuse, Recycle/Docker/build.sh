#!/bin/bash
docker rm -f 3r
docker build --tag=3r . && \
docker run -p 9003:9003 --privileged=true --restart=on-failure --name=3r --detach 3r