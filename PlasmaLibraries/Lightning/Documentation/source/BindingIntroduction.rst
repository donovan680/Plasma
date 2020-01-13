Binding Introduction
====================

To get started, download the latest `Lightning library <../downloads#http://>`_. For convenience, all of the Lightning C++ code
is compacted into one header and one cpp.

.. warning::
  Lightning uses its own containers, including Array, HashMap, String, etc. For compatibility with STL, the containers support ``.begin()`` and ``.end()`` iterators, as well as ``.size()``. The String class supports ``.c_str()``.

Compiling C++
-------------

Include the Lightning.cpp into your compilation process, and start by having your main include the Lightning.hpp

.. literalinclude:: ../../Project/Documentation/CompilingCpp.inl
  :language: cpp

So long as Lightning.cpp is built and linked in, this program should fully compile.

Compiling a Lightning script
------------------------

.. literalinclude:: ../../Project/Documentation/CompilingLightningScript.inl
  :language: cpp

Running a Lightning script
----------------------

As a language meant to be called and run from C++, Lightning has no 'main entrypoint' of its own.
Instead it is up to the user to instantiate types defined within Lightning scripts and call
functions on them (or invoke static methods).

Create a Lightning script with code that we want to test out.

``Player.lightning``

.. literalinclude:: ../../Project/Documentation/Player.lightning
  :language: as

From the C++ side change ``AddCodeFromString`` to ``AddCodeFromFile``.

.. code-block:: cpp

  project.AddCodeFromFile("Player.lightning");

.. warning::
  Make sure to put the ``Player.lightning`` file side by side with the executable, or make
  sure that the working directory is setup correctly so that the executable can find the script file.

We now need to compile the code into a ``Library``, and finally link that library into an ``ExecutableState``.
A ``Library`` stores all the compiled types and functions. The ``ExecutableState``
has its own stack and virtual machine, and is responsible for executing Lightning code.

.. literalinclude:: ../../Project/Documentation/RunningLightningScript.inl
  :language: cpp

