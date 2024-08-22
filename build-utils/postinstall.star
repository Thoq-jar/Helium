#!/bin/bash
### I AM AWARE THIS IS NOT STARLARK,
### I HAVE PLANS TO CONVERT THIS TO STARLARK IN THE FUTURE

sudo mv buildDir/purrooser /usr/local/bin/purrooser
cd ~
rm -rf .purroosertemp
purrooser