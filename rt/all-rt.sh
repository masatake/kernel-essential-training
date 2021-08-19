#!/bin/bash
bash ./spin.sh & sleep 1; bash run.sh rt-spin-X-1;bash ./spin.sh & sleep 1; bash run.sh rt-spin-X-2;bash ./spin.sh & sleep 1; bash run.sh rt-spin-X-3
killall spin

bash ./pollx.sh & sleep 1; bash run.sh rt-pollx-X-1;bash ./pollx.sh & sleep 1; bash run.sh rt-pollx-X-2;bash ./pollx.sh & sleep 1; bash run.sh rt-pollx-X-3
killall pollx

bash run.sh rt-noload
