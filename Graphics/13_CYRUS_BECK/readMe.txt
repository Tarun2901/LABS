The Cyrus–Beck algorithm is a generalized line clipping algorithm. It was designed to be more efficient than the Cohen–Sutherland algorithm, which uses repetitive clipping. Cyrus–Beck is a general algorithm and can be used with a convex polygon clipping window.

Here the parametric equation of a line in the view plane is

p(t) = p0 + t*(p1-p0)

where 0 ≤ t ≤ 1 

Now to find intersection point with the clipping window we calculate value of dot product. Let pE be a point on the clipping plane E.

Calculate n⋅(p(t)−pE) 

    if > 0, vector pointed towards interior;
    if = 0, vector pointed parallel to plane containing p;
    if < 0, vector pointed away from interior.

Here n stands for normal of the current clipping plane (pointed away from interior).

By this we select the point of intersection of line and clipping window where (dot product is 0) and hence clip the line.
