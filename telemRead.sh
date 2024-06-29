#!/bin/bash

# Define variables
TELEMETRY_HOST="localhost"  # The host where telemetry data is streamed from
TELEMETRY_PORT=50000        # The port where telemetry data is streamed from
OUTPUT_FILE="telemetry_data.txt"  # The file to store telemetry data

# Function to capture telemetry data
capture_telemetry() {
  echo "Capturing telemetry data from ${TELEMETRY_HOST}:${TELEMETRY_PORT}..."
  nc ${TELEMETRY_HOST} ${TELEMETRY_PORT} > ${OUTPUT_FILE}
}

# Run the function to start capturing telemetry
capture_telemetry

# Optional: If you want to append a timestamp to each line of telemetry data
# Uncomment the following lines to add timestamps to the telemetry data
# while IFS= read -r line; do
#   echo "$(date +"%Y-%m-%d %H:%M:%S") $line" >> ${OUTPUT_FILE}
# done < <(nc ${TELEMETRY_HOST} ${TELEMETRY_PORT})

echo "Telemetry capture started. Data is being stored in ${OUTPUT_FILE}."