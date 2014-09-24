// -*- mode: c++ -*-
/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2014, JSK Lab
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/o2r other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/


#ifndef JSK_PCL_ROS_PARALLEL_EDGE_FINDER_H_
#define JSK_PCL_ROS_PARALLEL_EDGE_FINDER_H_

#include <pcl_ros/pcl_nodelet.h>
#include <jsk_pcl_ros/ParallelEdgeArray.h>
#include <jsk_pcl_ros/ModelCoefficientsArray.h>
#include <jsk_pcl_ros/ClusterPointIndices.h>
#include <jsk_pcl_ros/ParallelEdgeFinderConfig.h>
#include "jsk_pcl_ros/pcl_conversion_util.h"
#include <dynamic_reconfigure/server.h>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/synchronizer.h>
#include "jsk_pcl_ros/geo_util.h"



namespace jsk_pcl_ros
{
  class ParallelEdgeFinder: public pcl_ros::PCLNodelet
  {
  public:
    typedef message_filters::sync_policies::ExactTime<
    ClusterPointIndices,
    ModelCoefficientsArray > SyncPolicy;
    typedef jsk_pcl_ros::ParallelEdgeFinderConfig Config;
  protected:
    ////////////////////////////////////////////////////////
    // methods
    ////////////////////////////////////////////////////////
    virtual void onInit();

    virtual void estimate(
      const ClusterPointIndices::ConstPtr& input_indices,
      const ModelCoefficientsArray::ConstPtr& input_coefficients);

    virtual void publishResult(
      const std::vector<std::set<int> >& parallel_groups_list,
      const ClusterPointIndices::ConstPtr& input_indices,
      const ModelCoefficientsArray::ConstPtr& input_coefficients);

    // for visualization
    virtual void publishResultAsCluser(
      const std::vector<std::set<int> >& parallel_groups_list,
      const ClusterPointIndices::ConstPtr& input_indices,
      const ModelCoefficientsArray::ConstPtr& input_coefficients);

    virtual void configCallback (Config &config, uint32_t level);
    
    ////////////////////////////////////////////////////////
    // ROS variables
    ////////////////////////////////////////////////////////
    message_filters::Subscriber<ClusterPointIndices> sub_indices_;
    message_filters::Subscriber<ModelCoefficientsArray> sub_coefficients_;
    boost::shared_ptr<message_filters::Synchronizer<SyncPolicy> >sync_;
    ros::Publisher pub_, pub_clusters_;
    boost::shared_ptr <dynamic_reconfigure::Server<Config> > srv_;
    boost::mutex mutex_;
    ////////////////////////////////////////////////////////
    // parallel estimation parameters
    ////////////////////////////////////////////////////////
    double angle_threshold_;
  private:
    
  };
}

#endif
