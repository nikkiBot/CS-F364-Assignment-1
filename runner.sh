#!/bin/sh
PATH = usr/bin
g++ InputGraph.cpp -o input && ./input
echo "ran input successfully"
python3 plotGraph.py 
sleep 10 & kill $!
g++ final_algo_code.cpp -g -o final && ./final 
echo "merge and decompose done"
python3 plotGraph_Dec.py 
sleep 10 & kill $!
python3 Merged_Plot.py 
sleep 10 & kill $!
