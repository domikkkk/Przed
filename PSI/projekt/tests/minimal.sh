#!/bin/bash
# 28 May, 2023
# Krzysztof Stawarski
#
# Here, we test that a minimal example of 1 device of each type can be connected and pass messages as expected

#### CONFIG ####
DST_PORT=8080
DST_ADDRESS=127.0.0.1
LOG_DIR="minimal_log"
################

echo "Creating separate dir for logs containment..."
mkdir $LOG_DIR

echo "Starting containers..."
BRAMA_PID=`docker run -d --env PORT=$DST_PORT --rm --network host -v $(pwd)/$LOG_DIR:/log psi/brama`
REJESTRATOR_PID=`docker run -d --env ADRES=$DST_ADDRESS --env PORT=$DST_PORT --env LOGIN=1 --env PASSWORD=qwerty --rm --network host -v $(pwd)/$LOG_DIR:/log psi/rejestrator`
SENSOR_PID=`docker run -d --env ADRES=$DST_ADDRESS --env PORT=$DST_PORT --env LOGIN=10 --env PASSWORD=qwerty --rm --network host -v $(pwd)/$LOG_DIR:/log psi/sensor`
echo "All containers running..."

echo "Waiting for logs generation..."
sleep 5

echo "Killing containers..."
docker kill $BRAMA_PID $REJESTRATOR_PID $SENSOR_PID > /dev/null

echo "Checking for data in logs..."
data_count=`grep "Received sensor data" $LOG_DIR/brama.log -c`

echo "Cleaning up logs..."
rm -rf $LOG_DIR

if test $data_count -gt 0; then
    echo "Test successful."
else
    echo "ERROR: No data was transmitted! Test failed."
    exit 1
fi
