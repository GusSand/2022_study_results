#!/bin/bash

rm -rf repos/*
for f in ../data/submitted_assignments/*-* ; do
    d=repos/$(basename ${f})
    cp -r skeleton $d
    cp "$f"/list.c "$d"/list.c
done
cp -r skeleton repos/gold_standard
cp -r skeleton repos/unmodified
cp student_version/list.c repos/unmodified/list.c
