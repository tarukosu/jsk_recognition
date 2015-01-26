^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package resized_image_transport
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

0.1.33 (2015-01-24)
-------------------
* add parameter to select interpolation method
* Contributors: Yusuke Furuta

0.1.32 (2015-01-12)
-------------------

0.1.31 (2015-01-08)
-------------------
* not include image prosessing config
* add log polar sample
* add include directory
* implement resize image processing
* implement log-polar processing
* add base class for processing image
* add sample launch file
* add LogPolar.cfg
* add first sample

0.1.30 (2014-12-24)
-------------------

0.1.29 (2014-12-24)
-------------------

0.1.28 (2014-12-17)
-------------------

0.1.27 (2014-12-09)
-------------------

0.1.26 (2014-11-23)
-------------------

0.1.25 (2014-11-21)
-------------------

0.1.24 (2014-11-15)
-------------------

0.1.23 (2014-10-09)
-------------------
* Install nodelet executables
* Contributors: Ryohei Ueda

0.1.22 (2014-09-24)
-------------------

0.1.21 (2014-09-20)
-------------------

0.1.20 (2014-09-17)
-------------------

0.1.19 (2014-09-15)
-------------------

0.1.18 (2014-09-13)
-------------------
* Creating publisher before subscribe topics in resized_image_transport
* Supress messages from resized_image_transport
* Contributors: Ryohei Ueda

0.1.17 (2014-09-07)
-------------------

0.1.16 (2014-09-04)
-------------------
* remove static variables from ImageResizer because now it is used as
  nodelet
* add client for resize image
* Contributors: Ryohei Ueda, Yusuke Furuta

0.1.14 (2014-08-01)
-------------------

0.1.13 (2014-07-29)
-------------------

0.1.12 (2014-07-24)
-------------------

0.1.11 (2014-07-08)
-------------------

0.1.10 (2014-07-07)
-------------------

0.1.9 (2014-07-01)
------------------

0.1.8 (2014-06-29)
------------------

0.1.7 (2014-05-31)
------------------

0.1.6 (2014-05-30)
------------------
* src/image_resizer.cpp: fix to compile on rosbuild

0.1.5 (2014-05-29)
------------------

0.1.4 (2014-04-25)
------------------

0.1.3 (2014-04-12)
------------------

0.1.2 (2014-04-11)
------------------
* use find_module to check catkin/rosbuild to pass git-buildpackage
* Contributors: Kei Okada

0.1.1 (2014-04-10)
------------------
* `#11 <https://github.com/jsk-ros-pkg/jsk_recognition/issues/11>`_: add depend tags
* add depend to driver_base
* add update with message
* simplify example and rename to example.launch
* fix bugs whcn resize paramater is 0, see issue `#252 <https://github.com/jsk-ros-pkg/jsk_recognition/issues/252>`_
* use Kbps not kB, issue `#253 <https://github.com/jsk-ros-pkg/jsk_recognition/issues/253>`_
* updating for catkin
* add option to change fps, rename image_type->image, see Issue 248
* mv resized_imagetransport resized_image_transport
* Contributors: Ryohei Ueda, Kei Okada, Youhei Kakiuchi
