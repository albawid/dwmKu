#!/bin/sh

# A modular status bar for dwm
# Joe Standring <git@joestandring.com>
# GNU GPLv3

# Dependencies: xorg-xsetroot

LOC=$(readlink -f "$0")
DIR=$(dirname "$LOC")

export IDENTIFIER="unicode"
export SEP1=" "
export SEP2=" "

. "$DIR/bar-functions/dwm_traffic.sh"
. "$DIR/bar-functions/dwm_resources.sh"
. "$DIR/bar-functions/dwm_light.sh"
. "$DIR/bar-functions/dwm_volume.sh"
. "$DIR/bar-functions/dwm_date.sh"
. "$DIR/bar-functions/dwm_network.sh"
. "$DIR/bar-functions/dwm_session.sh"

while true
do
  xsetroot -name " $(dwm_network)$(dwm_traffic)$(dwm_resources)$(dwm_light)$(dwm_volume)$(dwm_date)$(dwm_session) "
    sleep 1
done
