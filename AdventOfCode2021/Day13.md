# General Pattern
* If fold at y, column stays constant and if fold at x row stays constant
* Calculate distance from fold point
* Fold point minus the distance
* Need to only look for bottom half is split on y, and right half if split on x

# Walk Through 

. # . . . . .
. . . . . . .
. . . . . . .
- - - - - - -
a . . . . . .
b . . . . . .
. . . . . . .

a - row 4, 1 away from 3, need to be 1 away from 3 on the other side: 2
b - row 5, 2 away from 3, need to be 2 away from 3 on the other side: 1