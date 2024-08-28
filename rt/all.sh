#!/bin/bash
name=$1

if [[ -z "$name" ]]; then
    echo "ERROR: no name given" 1>&2
    exit 1
fi

bash ./spin.sh & sleep 1; bash run.sh "${name}"-spin-X-1;bash ./spin.sh & sleep 1; bash run.sh "${name}"-spin-X-2;bash ./spin.sh & sleep 1; bash run.sh "${name}"-spin-X-3
killall spin

bash ./pollx.sh & sleep 1; bash run.sh "${name}"-pollx-X-1;bash ./pollx.sh & sleep 1; bash run.sh "${name}"-pollx-X-2;bash ./pollx.sh & sleep 1; bash run.sh "${name}"-pollx-X-3
killall pollx

bash ./intr.sh & sleep 1; bash run.sh "${name}"-intr-X-1;bash ./intr.sh & sleep 1; bash run.sh "${name}"-intr-X-2;bash ./intr.sh & sleep 1; bash run.sh "${name}"-intr-X-3
killall intr

bash run.sh "${name}"-noload
