// BSD 3-Clause License

// Copyright (c) 2018, Neel Parikh
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.

// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.

// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <list>
#include <map>
#include <string>

#include <geometry_msgs/PoseArray.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <osrf_gear/LogicalCameraImage.h>
#include <osrf_gear/Order.h>
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>


#include "agile_robotics_industrial_automation/sensor.hpp"
#include "agile_robotics_industrial_automation/ur10_controller.hpp"
#include <osrf_gear/LogicalCameraImage.h>
#include <osrf_gear/VacuumGripperControl.h>
#include <osrf_gear/GetMaterialLocations.h>



class OrderManager {
 public:
  OrderManager();
  ~OrderManager();
  void orderCallback(const osrf_gear::Order::ConstPtr& order_msg);
  void executeOrder();
  std::string getPartType(std::string object);
  // std::map<std::string, std::list<std::string>> getOrder();
  bool pickAndPlace(std::pair<std::string,geometry_msgs::Pose> object_prop,int agvnum);
  void submitAGV(int num);
  void conveyor_camera_Callback(
  const osrf_gear::LogicalCameraImage::ConstPtr& image_msg);
  // std::map<std::string, std::list<std::string>> getConveyorParts();
  void scanConveyorParts();
  
 private:
  ros::NodeHandle manager_nh_;
  ros::Subscriber order_subscriber_,conveyor_camera_subscriber_;
  Sensor camera_;
  UR10Controller robot_;
  
  tf::TransformListener part_tf_listener_;
  std::pair<std::string,geometry_msgs::Pose> object_prop;
  std::string object;
  std::map<std::string, std::list<std::string>> scanned_objects_,conveyor_parts_list_;
  osrf_gear::Order order_;
  int counter_;
  osrf_gear::LogicalCameraImage conveyor_parts_;

};