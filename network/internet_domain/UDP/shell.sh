#!/bin/bash
set -eu

for i in `seq 1 10000`
do
	./client 172.16.150.78 56000 James$i
done
