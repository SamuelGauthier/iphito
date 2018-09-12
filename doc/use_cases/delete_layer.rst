Use Case: Delete Layer
======================

Precondition
------------

A layer exists.

Postcondition
-------------

A layer is deleted.

Main Success Scenario
---------------------

1. The User enters a layer number.
2. The System checks the validity of the layer number.
3. The System deletes the layer.

Extension
---------

2.
   A. The System finds that the layer doesn't exist.

      a. The System prompts the User to re-enter a valid layer number.
      b. If the layer number is still wrong, the User chooses whether he wants
         to keep entering the layer number.

