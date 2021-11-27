#!/bin/bash

grep --exclude=${3} -Rl '${1}' $2 &> /tmp/grep;mv /tmp/grep $3
