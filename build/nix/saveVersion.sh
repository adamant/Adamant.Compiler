#!/bin/bash

# This script saves off the current translated code so that we can have a stable version while we are working
rm -rf ../../translated/previous
cp -r ../../translated/current ../../translated/previous
echo 'New version saved.'
