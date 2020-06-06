Iphito
======

*A small curve editor for educational purposes.*


.. image:: screenshot.png
    :width: 500pt
    :alt: iphito screenshot
    :align: center


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

The built executable will then be in :code:`bin/main/`.

Usage
-----

.. code:: bash

    $ iphito < "bezier [ (-0.5, 0), (-0.7, 0.6), (0.0, 0.9), (0.7, 0.6), (0.5, 0) ]"
    $ # or with the curve definitions inside a file
    $ iphito example.iphito

use

* :code:`bezier` for Bézier curves
* :code:`hermite3` for cubic Hermite curves
* :code:`hermite5` for quintic Hermite curves

Todo
----

The following list is sorted by order of priority:

#. [] Fix scrolling
#. [] Export to pdf format
#. [] Implement an infinite grid background
#. [] Command line interface
#. [] Option to add text of values of points and vectors
#. [] Option to make width of curves fixed with zoom
#. [] Find a better way to make curves look smooth (heuristic parallel curve)
#. [] Transition from OpenGL to Vulkan
