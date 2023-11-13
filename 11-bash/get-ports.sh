#!/bin/bash

if [ "$(id -u)" -ne 0 ]; then
   echo "Only an admin can do that."
   exit 1
fi

TVSAPP_BIN=$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")
NGINX_CONF=/etc/nginx/sites-available/tvsapp

# INCOMPLETE: insert other commands between grep and
#             sort to extract only the port number
PORTS=$(cat "$NGINX_CONF" | grep  ":[0-9]\+;" | sort -n | uniq)

if [ "$1" == "--last" ]; then
   echo "$PORTS" | tail -n 1
   exit 0
fi

echo "$PORTS"
