#!/bin/bash

echo "This is a useless service."

function handleTerm() {
	echo "I refuse to stop being useless!"
}

trap handleTerm TERM

while :
do
	sleep 8
	echo "Still useless..."
done

