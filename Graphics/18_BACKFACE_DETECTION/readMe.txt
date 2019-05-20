Hidden Surface detection using Backface algorithm

When we project 3-D objects on a 2-D screen, we need to detect the faces that are hidden on 2D.
Back-Face detection, also known as Plane Equation method, is an object space method in which objects and parts of objects are compared to find out the visible surfaces. Let us consider a triangular surface that whose visibility needs to decided. The idea is to check if the triangle will be facing away from the viewer or not. If it does so, discard it for the current frame and move onto the next one. Each surface has a normal vector. If this normal vector is pointing in the direction of the center of projection, then it is a front face and can be seen by the viewer. If this normal vector is pointing away from the center of projection, then it is a back face and can not be seen by the viewer.

1) Compute N for every face of object.
2) If (C.(Z component) < 0)
        then a back face and don't draw
   else
        front face and draw


Limitations :
1) This method works fine for convex polyhedra, but not necessarily for concave polyhedra.
2) This method can only be used on solid objects modeled as a polygon mesh.
