set terminal  png 
set output 'graph.png'
plot 'measuring_data.txt' using 1:2 with lines
