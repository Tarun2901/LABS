Midpoint ellipse algorithm is a method for drawing ellipses in computer graphics.
This method is modified from Bresenham’s algorithm. The advantage of this
modified method is that only addition operations are required in the program
loops. This leads to simple and fast implementation in all processors.
Let us consider one quarter of an ellipse. The curve is divided into two regions.
In region I, the slope on the curve is greater than –1 while in region II less
than –1

The algorithm described above shows how to obtain the pixel coordinates in the
first quarter only. The ellipse centre is assumed to be at the origin. In actual
implementation, the pixel coordinates in other quarters can be simply obtained
by use of the symmetric characteristics of an ellipse. For a pixel (x, y) in the first
quarter, the corresponding pixels in other three quarters are (x, –y), (–x, y) and
(–x, –y) respectively. If the centre is at (xC, yC), all calculated coordinate (x, y)
should be adjusted by adding the offset (xC, yC). 