#!/bin/sh

# A dwm_bar module to display the current backlight brighness with xbacklight
# Joe Standring <git@joestandring.com>
# GNU GPLv3

# Dependencies: xbacklight

dwm_light () {
    # printf "%s %.0f%s%%\n" "$SEP1" "$(light)" "$SEP2"
    light=$(light | cut -d "." -f1)
    echo "  "$light"% "
}
dwm_light
