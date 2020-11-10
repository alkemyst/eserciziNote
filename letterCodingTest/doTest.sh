#!/bin/bash

for i in `cat allcodes`; do
	echo -n "$i = "
	./testProgram $i 2> /dev/null
done

