Use Case "Create Curve"
=======================

Precondition
------------

A layer exists.

Postcondition
-------------

A new curve is created and editable.

Main Success Scenario
---------------------

1. The User enters the layer number
2. The System checks the validity of the layer number.
3. The User enters the curve type.
4. The System checks the validity of the curve type.
5. The User specifies at least two points.
6. The System checks that the points are not equal.
7. The System displays the curve.


Extension
---------

1. The System finds that the layer doesn't exist.

   a. The System prompts the User to re-enter a valid layer number.
   b. If the layer number is still wrong, the system asks the user whether he
      wants to use the default layer.
   c. The User chooses whether he wants to keep entering the layer number.

2. The System determines that the curve type is not supported.

   a. The System prompts the User to re-enter a valid curve type.
   b. If the curve type is still wrong, the User chooses whether he wants to
      keep entering the curve type or not.
