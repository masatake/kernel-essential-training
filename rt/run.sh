#!/bin/sh
#
# This script is base on
# https://www.osadl.org/Create-a-latency-plot-from-cyclictest-hi.bash-script-for-latency-plot.0.html
# The MIT License doesn't cover this script.
#
if [ -z "$1" ]; then
    echo "no output file given" 1>&2
    exit 1
fi

count=100000
target_cpu=2
pri=90

base=$1
output=${base}.data
histogram=${base}.hist
plotout=${base}.png
plotcmd=${base}.cmd
cores=1

rm -f "${output}" "${histogram}" "${plotout}" "${plotcmd}"

cyclictest -l${count} -a "${target_cpu}" -t 1 --policy=fifo -p"${pri}" -m -i200 -h400 -q > "${output}"
max=`grep "Max Latencies" ${output} | tr " " "\n" | sort -n | tail -1 | sed s/^0*//`
grep -v -e "^#" -e "^$" ${output} | tr " " "\t" > ${histogram}

for i in `seq 1 $cores`
do
  column=`expr $i + 1`
  cut -f1,$column "${histogram}" > ${histogram}.$i
done

echo -n -e "set title \"Latency plot\"\n\
set terminal png\n\
set xlabel \"Latency (us), max $max us\"\n\
set logscale y\n\
set xrange [0:400]\n\
set yrange [0.8:*]\n\
set ylabel \"Number of latency samples\"\n\
set output \"${plotout}\"\n\
plot " > "${plotcmd}"

for i in `seq 1 $cores`
do
  if test $i != 1
  then
    echo -n ", " >> "${plotcmd}"
  fi
  cpuno=`expr $i - 1`
  if test $cpuno -lt 10
  then
    title=" CPU$cpuno"
   else
    title="CPU$cpuno"
  fi
  echo -n "\"${histogram}.$i\" using 1:2 title \"$title($base)\" with histeps" >> "${plotcmd}"
done

gnuplot -persist < "${plotcmd}"
echo do "\"eog ${plotout}\"" or "\"firefox ${plotout}\""
sync
