#!/bin/bash
bash ./spin.sh & sleep 1; bash run.sh normal-spin-X-1;bash ./spin.sh & sleep 1; bash run.sh normal-spin-X-2;bash ./spin.sh & sleep 1; bash run.sh normal-spin-X-3
killall spin

bash ./pollx.sh & sleep 1; bash run.sh normal-pollx-X-1;bash ./pollx.sh & sleep 1; bash run.sh normal-pollx-X-2;bash ./pollx.sh & sleep 1; bash run.sh normal-pollx-X-3
killall pollx

bash ./intr.sh & sleep 1; bash run.sh normal-intr-X-1;bash ./intr.sh & sleep 1; bash run.sh normal-intr-X-2;bash ./intr.sh & sleep 1; bash run.sh normal-intr-X-3
killall intr

bash run.sh normal-noload
