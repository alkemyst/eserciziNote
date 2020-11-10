#!/bin/bash

data=`date +%s%N`
echo $data

code=`../bin/timeToKey encode $data`
echo $code

../bin/timeToKey decode $code

