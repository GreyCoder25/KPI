set terminal  png 
set output 'graph_P.png'
plot 'approx_data.txt' using 1:2 with lines
