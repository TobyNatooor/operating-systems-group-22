#!/bin/bash

# Simple test of the command interpreter

in="abbabaq"
out="0,3,5;"

[[ $(./cmd_int <<< "$in") == "$out"* ]] && echo "PASSED_1" || echo "FAILED_1"

in="acccaa"
out="4,5"

[[ $(./cmd_int <<< "$in") == "$out"* ]] && echo "PASSED_2" || echo "FAILED_2"

in="bbbbaa"
out="4,5"

[[ $(./cmd_int <<< "$in") == "$out"* ]] && echo "PASSED_3" || echo "FAILED_3"

in="aaaaacca"
out="0,1,2,7"

[[ $(./cmd_int <<< "$in") == "$out"* ]] && echo "PASSED_4" || echo "FAILED_4"

in="aaaqaaa"
out="0,1,2"

[[ $(./cmd_int <<< "$in") == "$out"* ]] && echo "PASSED_5" || echo "FAILED_5"
