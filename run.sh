#!/bin/bash

g++ -std=c++14 prog1.cpp -O3 -o prog1
g++ -std=c++14 brute.cpp -O3 -o brute

for file in $(cat ${1}); do
	if [ -r ${file}.args ]; then
		if [ -r ${file}.in ]; then
			${2} $(cat ${file}.args) < ${file}.in > ${file}.out
		else
			${2} $(cat ${file}.args) > ${file}.out
		fi
	else
		if [ -r ${file}.in ]; then
                        ./prog1 < ${file}.in > ${file}.out
                        ./brute < ${file}.in > ${file}.expect
                        diff ${file}.out ${file}.expect
                else
                        ${2} > ${file}.out
		fi
	fi
done
