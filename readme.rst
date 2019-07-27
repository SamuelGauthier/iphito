Iphito
======

*A small curve editor for educational purposes.*

.. contents::
   :backlinks: top

.. sectnum::

This small cross-platform curve editor and visualizer supports displaying cubic,
quintic Hermite and Bézier curves.

Build
-----

.. code:: bash

   $ md build bin
   $ cd build
   $ cmake -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
   $ ../bin; ninja -C ../build

Todo
----

The following list is sorted by order of priority:

[] Make window resizable
[] Display axes
[] Command line interface
[] File loading and saving
[] Export to pdf format
[] Add text of points and vectors
