Line Clipping using Cohen-Sutherland Algorithm


The algorithm includes, excludes or partially includes the line based on whether:

   1. Both endpoints are in the viewport region (bitwise OR of endpoints = 00): trivial accept.
   2. Both endpoints share at least one non-visible region, which implies that the line does 		not cross the visible region. (bitwise AND of endpoints not equal to 0): trivial reject.
   3. Both endpoints are in different regions: in case of this nontrivial situation the 	   algorithm finds one of the two points that is outside the viewport region (there 		will be at least one point outside). The intersection of the outpoint and extended 		viewport border is then calculated (i.e. with the parametric equation for the line), 		and this new point replaces the outpoint. The algorithm repeats until a trivial accept 		or reject occurs.

The numbers in the figure below are called outcodes. An outcode is computed for each of the two points in the line. The outcode will have 4 bits for two-dimensional clipping, or 6 bits in the three-dimensional case. The first bit is set to 1 if the point is above the viewport. The bits in the 2D outcode represent: top, bottom, right, left. For example, the outcode 1010 represents a point that is top-right of the viewport.

