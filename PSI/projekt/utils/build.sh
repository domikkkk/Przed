#!/bin/bash
# 28 May, 2023
# Krzysztof Stawarski


for program in brama sensor rejestrator
do
    docker build -f ./docker/$program/Dockerfile -t psi/$program --network host --build-arg PROGRAM_NAME="$program" .
done
