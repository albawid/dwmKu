#!/bin/sh

# Created by albawid (only this module)

dwm_resources () {
    ROOT_DIR=$(df -h --output=pcent / | awk 'NR%2==0 {print $0}')
    MEM_TOT=$(free | awk 'NR%2==0 {print $2}')
    MEM_AVA=$(free | awk 'NR%2==0 {print $7}')
    MEM_USED=$(( $MEM_TOT - $MEM_AVA))
    MEM_USAGE=$(( $MEM_USED * 100 / $MEM_TOT ))
    VAR_TEMP=$(cat /sys/class/thermal/thermal_zone0/temp)
    TEMP=$(($VAR_TEMP/1000))
    CPU=$(top -b -n2 -p 1 | fgrep "Cpu(s)" | tail -1 | awk -F'id,' -v prefix="$prefix" '{ split($1, vs, ","); v=vs[length(vs)]; sub("%", "", v); printf "%s%.1f%%\n", prefix, 100 - v}' | cut -d "." -f1)

    echo "  "$TEMP°C "﬙ "$MEM_USAGE"%" " "$CPU"%" ""$ROOT_DIR
    }
dwm_resources
