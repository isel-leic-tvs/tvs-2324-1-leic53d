#!/bin/bash

CURDIR=`dirname $0`

trap do_nothing INT ALRM

function do_nothing() {
	return
}

$CURDIR/sig02

EXIT_CODE=$?

echo
echo "Exit code:" $EXIT_CODE
