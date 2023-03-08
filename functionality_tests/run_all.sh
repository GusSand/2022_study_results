#!/bin/bash

mkdir -p repos
if [ $(ls repos | wc -l) -ne 0 ]; then
    if [ "$1" != "-f" ]; then
        echo "WARNING: repos directory is not empty, aborting so we don't overwrite old data"
        echo "If you want to remove it and recreate it, use: $0 -f"
        exit
    else
        echo "Existing data in repos, but removing as you requested"
        ./recreate_dirs.sh
    fi
else
    ./recreate_dirs.sh
fi

echo "Running tests..."
ls -d repos/* | parallel bash grade.sh

echo 'Results are in repos/*/*.json'
