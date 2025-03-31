#!/bin/bash

#pio run --target clean
pio run --target buildfs
pio run --target uploadfs
pio run --target upload
#pio run --target monitor