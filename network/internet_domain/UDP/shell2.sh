#!/bin/bash
set -eu
for i in `seq 1 100`
do
	bash ./shell.sh &
done
