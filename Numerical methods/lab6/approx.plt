set terminal  png 
set output 'graph_approx.png'
plot 'spline_approx_vals.txt' using 1:2 with lines lt rgb 'green'
