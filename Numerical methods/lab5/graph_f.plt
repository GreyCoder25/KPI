set terminal  png 
set output 'graph_f.png'
plot 'f_data.txt' using 1:2 with lines
