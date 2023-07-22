#!/bin/bash
find dir -name "*.c" | awk '{ system("wc -l " $0) }' | awk '{if ($1 > 500 ) print $2}' | head -2
