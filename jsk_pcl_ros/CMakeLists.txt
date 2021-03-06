if($ENV{ROS_DISTRO} STREQUAL "groovy")
  file(GLOB _msg_files ${CMAKE_CURRENT_SOURCE_DIR}/msg/*.msg)
  foreach(_msg_file ${_msg_files})
    message("convert pcl_msgs -> pcl for groovy ${_msg_file}")
    execute_process(COMMAND grep pcl_msgs ${_msg_file} OUTPUT_VARIABLE _grep_pcl_msgs)
    if (NOT ${_grep_pcl_msgs})
      execute_process(COMMAND sed -i s@^pcl_msgs/@pcl/@g ${_msg_file})
    endif()
  endforeach()
endif()
if(NOT USE_ROSBUILD)
  include(catkin.cmake)
  return()
endif()
cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# rosbuild_add_library (jsk_pcl_ros  src/ConvexHullToPlane.cpp)

rosbuild_find_ros_package (dynamic_reconfigure)
include (${dynamic_reconfigure_PACKAGE_PATH}/cmake/cfgbuild.cmake)
gencfg ()

rosbuild_find_ros_package (pcl_ros)

macro(jsk_pcl_nodelet _nodelet_cpp _nodelet_class _single_nodelet_exec_name)
  list(APPEND jsk_pcl_nodelet_sources ${_nodelet_cpp})
  set(NODELET ${_nodelet_class})
  set(DEFAULT_NODE_NAME ${_single_nodelet_exec_name})
  configure_file(${PROJECT_SOURCE_DIR}/src/single_nodelet_exec.cpp.in
    ${_single_nodelet_exec_name}.cpp) #${CMAKE_CURRENT_BINARY_DIR}/
  rosbuild_add_executable(${_single_nodelet_exec_name} build/${_single_nodelet_exec_name}.cpp)
endmacro(jsk_pcl_nodelet _nodelet_cpp _nodelet_class _single_nodelet_exec_name)

jsk_pcl_nodelet(src/pointcloud_screenpoint_nodelet.cpp "jsk_pcl/PointcloudScreenpoint" "pointcloud_screenpoint")
jsk_pcl_nodelet(src/particle_filter_tracking_nodelet.cpp "jsk_pcl/ParticleFilterTracking" "particle_filter_tracking")
jsk_pcl_nodelet(src/voxel_grid_downsample_manager_nodelet.cpp "jsk_pcl/VoxelGridDownsampleManager" "voxel_grid_downsample_manager")
jsk_pcl_nodelet(src/voxel_grid_downsample_decoder_nodelet.cpp "jsk_pcl/VoxelGridDownsampleDecoder" "voxel_grid_downsample_decoder")
jsk_pcl_nodelet(src/snapit_nodelet.cpp "jsk_pcl/Snapit" "snapit")
jsk_pcl_nodelet(src/keypoints_publisher_nodelet.cpp "jsk_pcl/KeypointsPublisher" "keypoints_publisher")
jsk_pcl_nodelet(src/hinted_plane_detector_nodelet.cpp "jsk_pcl/HintedPlaneDetector" "hinted_plane_detector")
#jsk_pcl_nodelet(src/color_filter_nodelet.cpp "jsk_pcl/RGBColorFilter" "rgb_color_filter")
jsk_pcl_nodelet(src/resize_points_publisher_nodelet.cpp "jsk_pcl/ResizePointsPublisher" "resize_points_publisher")
jsk_pcl_nodelet(src/depth_image_creator_nodelet.cpp "jsk_pcl/DepthImageCreator" "depth_image_creator")
jsk_pcl_nodelet(src/euclidean_cluster_extraction_nodelet.cpp "jsk_pcl/EuclideanClustering" "euclidean_clustering")
jsk_pcl_nodelet(src/cluster_point_indices_decomposer_nodelet.cpp "jsk_pcl/ClusterPointIndicesDecomposer" "cluster_point_indices_decomposer")
jsk_pcl_nodelet(src/cluster_point_indices_decomposer_z_axis_nodelet.cpp "jsk_pcl/ClusterPointIndicesDecomposerZAxis" "cluster_point_indices_decomposer_z_axis")
jsk_pcl_nodelet(src/centroid_publisher_nodelet.cpp "jsk_pcl/CentroidPublisher" "centroid_publisher")
jsk_pcl_nodelet(src/pointcloud_throttle_nodelet.cpp
  "jsk_pcl/NodeletPointCloudThrottle" "point_cloud_throttle")
jsk_pcl_nodelet(src/image_throttle_nodelet.cpp
  "jsk_pcl/NodeletImageThrottle" "image_throttle")
jsk_pcl_nodelet(src/image_mux_nodelet.cpp
  "jsk_pcl/NodeletImageMUX" "image_mux")
jsk_pcl_nodelet(src/image_demux_nodelet.cpp
  "jsk_pcl/NodeletImageDEMUX" "image_demux")

rosbuild_add_library (jsk_pcl_ros
  ${jsk_pcl_nodelet_sources}
#  ${pcl_ros_PACKAGE_PATH}/src/pcl_ros/features/feature.cpp
  src/filter.cpp # copy from pcl_ros https://github.com/ros-perception/perception_pcl/issues/9
  src/color_filter_nodelet.cpp
)

rosbuild_add_compile_flags (jsk_pcl_ros ${SSE_FLAGS})
rosbuild_link_boost (jsk_pcl_ros system)
#target_link_libraries (jsk_pcl_ros tbb pcl_ros_io pcl_ros_features pcl_ros_filters pcl_ros_segmentation pcl_ros_surface)
target_link_libraries (jsk_pcl_ros tbb pcl_ros_io pcl_ros_filters pcl_ros_tf)

#uncomment if you have defined services
rosbuild_gensrv()

#uncomment if you have defined messages
rosbuild_genmsg()

# roslaunch documentation
rosbuild_find_ros_package("jsk_tools")
execute_process(COMMAND cmake -E chdir ${PROJECT_SOURCE_DIR} python ${jsk_tools_PACKAGE_PATH}/bin/launchdoc-generator.py ${PROJECT_NAME} --output_dir=./build --nomakefile RESULT_VARIABLE _make_failed)
