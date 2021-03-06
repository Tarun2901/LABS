Write your name using Hermite Curve.


In numerical analysis, a cubic Hermite spline or cubic Hermite interpolator is a spline where each piece is a third-degree polynomial specified in Hermite form:[1] that is, by its values and first derivatives at the end points of the corresponding domain interval.

Cubic Hermite splines are typically used for interpolation of numeric data specified at given argument values x 1 , x 2 , … , x n,, to obtain a smooth continuous function. The data should consist of the desired function value and derivative at each x k {\displaystyle x_{k}} x_{k}. (If only the values are provided, the derivatives must be estimated from them.) The Hermite formula is applied to each interval ( x(k) , x(k + 1) ) separately. The resulting spline will be continuous and will have continuous first derivative.

On the unit interval ( 0 , 1 ) , given a starting point p(0) at t=0 and an ending point p(1) at  t = 1 with starting tangent m0  at t = 0 {and ending tangent m1 at t = 1, the polynomial can be defined by

    p(t) = ( 2t^3 − 3t^2 + 1 )*p0 + ( t^3 − 2t^2 + t )m0 + ( −2t^3 + 3t^2)p1 + ( t^3 − t^2 )m1 a

The four Hermite basis functions. The interpolant in each subinterval is a linear combination of these four functions.

where t ∈ [0, 1].s
