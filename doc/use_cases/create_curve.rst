Use Case: Create Curve
======================

Precondition
------------

A layer exists.

Postcondition
-------------

A new curve is created and editable.

Main Success Scenario
---------------------

1. The User enters the layer number, the curve type and at least two control
   points.
2. The System checks the validity of the layer number, the curve type and that
   the points are not equal.
3. The System creates the curve.


Extension
---------

2.
   A. The System finds that the layer doesn't exist.

      a. The System prompts the User to re-enter a valid layer number.
      b. If the layer number is still wrong, the system asks the user whether he
         wants to use the default layer.
      c. The User chooses whether he wants to keep entering the layer number.

   B. The System determines that the curve type is not supported.

      a. The System prompts the User to re-enter a valid curve type.
      b. If the curve type is still wrong, the User chooses whether he wants to
         keep entering the curve type or not.

   C. The System determines that the points are equal
      
      a. The System prompts the User to re-enter different points.
      b. If the points are still equal, the User chooses whether he wants to
         keep entering the points or not.
