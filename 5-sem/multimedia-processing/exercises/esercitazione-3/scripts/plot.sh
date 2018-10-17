#!/bin/bash

if [ -z $1 ]; then
  echo "Usage: $0 fft-file"
  exit
fi

FFT_FILE=$1
lines=$(head -n 1 /tmp/fft.csv | grep -o , | wc -l)

for i in $(seq 2 $((lines+1))); do
  echo $i
  gnuplot -e "set output '/tmp/fft-$i.png'" plot.gnu -e "plot '$FFT_FILE' using 1:$i with lines"
done
