#!/bin/sh

# A dwm_bar function that shows the current date and time
# Joe Standring <git@joestandring.com>
# GNU GPLv3📆

# Date is formatted like like this: "[Mon 01-01-00 00:00:00]"
dwm_date () {
    printf " %s"
    if [ "$IDENTIFIER" = "unicode" ]; then
        printf "   %s"$(date "+0%u%d%m%Y%H%M")
    else
        printf "DAT %s" "$(date "+%a %d-%m-%y %T")"
    fi
    printf "%s\n"
}

dwm_date
