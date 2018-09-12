Use Case: Delete Curve
======================

Precondition
------------

A curve exists.

Postcondition
-------------

A curve is deleted.

Main Success Scenario
---------------------

1. The User enters the layer number and the curve ID.
2. The System checks the validity of the layer number and curve ID.
3. The System deletes the curve with the corresponding ID.

Extension
---------

2.
   A. The System finds that the layer doesn't exist.

      a. The System prompts the User to re-enter a valid layer number.
      b. If the layer number is still wrong, the system asks the user whether he
         wants to use the default layer.
      c. The User chooses whether he wants to keep entering the layer number.

   B. The System determines that the curve ID does not exist.

      a. The System prompts the User to re-enter a valid curve ID.
      b. If the curve ID is still wrong, the User chooses whether he wants to
         keep entering the curve ID or not.

