set terminal  png 
set output 'graph_f.png'
plot 'f_vals.txt' using 1:2 with lines lt rgb 'red'
