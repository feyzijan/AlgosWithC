Here the goal is to find the intersection points of two ellipses given by the following functions: 
𝑓(𝑥, 𝑦) = 𝑥² + 𝑦² - 1 = 0, and 𝑔(𝑥, 𝑦) = 5𝑥² + 21𝑦² - 9 = 0. These equations represent a circle and an intersecting ellipse.

Two methods are used to find the intersection points: Newton's method and fixed-point iteration.

## Method 1: Newton's Method
- Uses Newton's method to iteratively find solutions.
- Requires the calculation of derivatives and the inverse of a Jacobian matrix.
- Checks for singularity of the Jacobian matrix.
- Provides a fast convergence when applicable.

## Method 2: Fixed-Point Iteration
- Utilizes a fixed-point iteration scheme to find solutions.
- Involves iterative calculations based on given equations.
- Suitable for finding one set of intersection points (with positive values).


## Implementation Notes
- Both methods are implemented using a while loop with a maximum number of iterations.
- Checks for singular Jacobian and negative square roots to handle erroneous cases.
- Translates mathematical equations directly into code.
- Provides the correct solutions based on initial values.