Polygon Clipping using Weiler Atherton Algorithm.


The Weiler–Atherton is a polygon-clipping algorithm. It is used in areas like computer graphics and games development where clipping of polygons is needed. It allows clipping of a subject or candidate polygon by an arbitrarily shaped clipping polygon/area/region.

Given polygon A as the clipping region and polygon B as the subject polygon to be clipped, the algorithm consists of the following steps:

   1. List the vertices of the clipping-region polygon A and those of the subject polygon B.
   2. Label the listed vertices of subject polygon B as either inside or outside of clipping region A.
   3. Find all the polygon intersections and insert them into both lists, linking the lists at the intersections.
   4. Generate a list of "inbound" intersections – the intersections where the vector from the intersection to the subsequent vertex of subject polygon B begins inside the clipping region.
   5. Follow each intersection clockwise around the linked lists until the start position is found.

If there are no intersections then one of three conditions must be true:

    1.A is inside B – return A for clipping, B for merging.
    2.B is inside A – return B for clipping, A for merging.
    3.A and B do not overlap – return None for clipping or A & B for merging.
