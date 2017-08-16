sma-bluetooth
#############

A C program to connect to sma inverters and export data, e.g.
to pvoutput.org.

The source code of the original sma-bluetooth tool was adapted, that
it can be now compiled with an up-to date C++ compiler.  Many errors
and issues were found during the port which were fixed.

Preconditions
-------------

Under Debian / Ubuntu you need to install the following packages:

.. code:: bash

   apt install bluez mysql-server make gcc g++ git libbluetooth-dev \
                 libcurl4-openssl-dev libmariadb-dev libxml2-dev

Compiling
---------

Get the source code (prefreeded with git clone) and

.. code:: bash

   make


