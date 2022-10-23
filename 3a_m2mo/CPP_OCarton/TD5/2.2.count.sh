#!/bin/bash
awk 'NF > 0 {s += NF-1 } END {print s}' FS=const 2.2.h
