#!/bin/bash

CURDIR=`dirname $0`

trap do_nothing INT

function do_nothing() {
	return
}

$CURDIR/sig01

EXIT_CODE=$?

echo
echo "Exit code:" $EXIT_CODE
