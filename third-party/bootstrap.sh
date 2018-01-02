#!/bin/sh

if [[ -d  "SPMediaKeyTap" ]]; then
    cd SPMediaKeyTap
    git pull --rebase
    cd -
else
    git clone git@github.com:dubo-dubon-duponey/SPMediaKeyTap.git
fi

if [[ -d  "apple_remote_control" ]]; then
    cd apple_remote_control
    git pull --rebase
    cd -
else
    git clone git@github.com:dubo-dubon-duponey/apple_remote_control.git
fi
