Use Case: Create Layer
======================

Precondition
------------

A layer exists.

Postcondition
-------------

A new layer is created.

Main Success Scenario
---------------------

1. The User enters a layer number.
2. The System checks the validity of the layer number.
3. The System creates the new layer.

Extension
---------

2.
   A. The System finds that the layer doesn't exist.

      a. The System prompts the User to re-enter a valid layer number.
      b. If the layer number is still wrong, the system asks the user whether he
         wants to use the default layer.
      c. The User chooses whether he wants to keep entering the layer number.
