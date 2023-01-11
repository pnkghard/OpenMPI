#!/bin/bash

for f in *.txt; do
	mv -- "$f" "${f//e/a}"
	#echo "$f"
done
