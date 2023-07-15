#!/bin/bash
# 28 May, 2023
# Krzysztof Stawarski
#
# Here, we test that the maximum number of devices that we are required to handle, can in fact, be handled properly
# Unfortunately, due to the limits of our machines, we cannot test the scenario with all 1024 devices,
# but 300 with **much** higher frequency is our attempt at proving our system works as intended.

#### CONFIG ####
DST_PORT=8080
DST_ADDRESS=127.0.0.1
LOG_DIR="stress_log/"
################

echo "Creating separate dir for logs containment..."
mkdir $LOG_DIR

echo "Starting containers..."
echo "Starting 'brama'"
BRAMA_PID=`docker run -d --env PORT=$DST_PORT --rm --network host -v $(pwd)/$LOG_DIR:/log psi/brama`
echo "Starting 300 instances of 'sensor'"
for id in {100..399}; do
    SENSOR_PID="`docker run -d --env ADRES=$DST_ADDRESS --env PORT=$DST_PORT --env LOGIN=$id --env PASSWORD=qwerty --rm --network host -v $(pwd)/$LOG_DIR:/log psi/sensor` $SENSOR_PID"
done

echo "Starting 10 instances of 'rejestrator'"
for id in {1..10}; do
    REJESTRATOR_PID="`docker run -d --env ADRES=$DST_ADDRESS --env PORT=$DST_PORT --env LOGIN=$id --env PASSWORD=qwerty --rm --network host -v $(pwd)/$LOG_DIR:/log psi/rejestrator` $SENSOR_PID"
done

echo "All containers running..."

echo "Waiting for logs generation..."
sleep 5

echo "Killing containers..."
docker kill $BRAMA_PID $REJESTRATOR_PID $SENSOR_PID 2&> /dev/null

echo "Checking for data in logs..."
sensor_auth_count=`grep "INFO - Authenticated" $LOG_DIR/sensor.log -c`

echo "Cleaning up logs..."
rm -rf $LOG_DIR

if test $sensor_auth_count -eq 300; then
    echo "Test successful."
else
    echo "ERROR: Not all 'sensor' instances were authenticated!"
    exit 1
fi
