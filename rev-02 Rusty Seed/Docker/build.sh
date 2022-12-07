#!/bin/bash
docker rm -f rustyseed
docker build --tag=rustyseed . && \
docker run -p 9004:9004 --privileged=true --restart=on-failure --name=rustyseed --detach rustyseed