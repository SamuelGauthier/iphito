User Case: Edit Curve Equation
==============================

Precondition
------------

A curve exists.

Postcondition
-------------

A curve is edited.

Main Success Scenario
---------------------

1. The User enters the curve ID, the control point ID and the new control point.
2. The System checks the validity of the curve ID and the control point ID.
3. The System edits the curve.

Extension
---------

2.

   A. The System determines that the curve ID does not exist.

      a. The System prompts the User to re-enter a valid curve ID.
      b. If the curve ID is still wrong, the User chooses whether he wants to
         keep entering the curve ID or not.

   B. The System determines that the point ID does not exist.
      
      a. The System prompts the User to re-enter a valid point ID.
      b. If the point ID is still wrong, the User chooses whether he wants to
         keep entering the point ID or not.
