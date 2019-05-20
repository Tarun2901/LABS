CIRCLE PATTERN
The given circle pattern is drawn by using mid point circle algorithm.
For the arcs of various circles, visible arcs are drawn using WHITE and invisible using BLACK.
As in 2D transformation, the matrix is
[
cos(theta)   -sin(theta)   0
sin(theta)   cos(theta)    0
0             0            1
],
so we rotate each point by multiplying it through the matrix where theta varies through small angles.

In this program, I have used the 
midpoint circle algorithm to draw
the pattern. The code simply calls 
the function that has implemented 
midpoint circle algorithm, and
instead of drawing a complete circle 
I have used this function to draw
some specific arcs only as required by the 
pattern. The entire pattern is then
set to rotate.