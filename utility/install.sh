#!/bin/bash

chmod +x utility/build.sh
./utility/build.sh

sudo mv build/Purr /usr/local/bin/purrooser-experimental
exit 0
