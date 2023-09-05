/*
 * Copyright (c) 2008, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "save_goal_tool.h"
#include <geometry_msgs/PoseStamped.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <rviz/display_context.h>
#include <rviz/ogre_helpers/arrow.h>
#include <rviz/properties/string_property.h>
#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <fstream>

namespace rviz
{
SaveGoalTool::SaveGoalTool()
{
  shortcut_key_ = 's';

  // topic_property_ =
  //     new StringProperty("Topic", "goal", "The topic on which to publish navigation goals.",
  //                        getPropertyContainer(), &GoalTool::updateTopic, this);
}

void SaveGoalTool::onInitialize()
{
  PoseTool::onInitialize();
  arrow_->setColor(1.0f, 0.0f, 1.0f, 1.0f);
  setName("2D Save Goal");
  // updateTopic();
}

void SaveGoalTool::activate()
{
  // Activate your tool (e.g., subscribe to topics, set up listeners).
}

void SaveGoalTool::deactivate()
{
  // Deactivate your tool (e.g., unsubscribe from topics, clean up resources).
}

int SaveGoalTool::processMouseEvent(ViewportMouseEvent& event)
{
  // Handle mouse events (if necessary).
  return Render;
}

void SaveGoalTool::saveGoal()
{
  // Get the pose of the arrow.
  Ogre::Vector3 position;
  Ogre::Quaternion orientation;
  getPose(position, orientation);

  // Code to save the goal point and orientation to a YAML file.
  std::string yaml_filename = QFileDialog::getSaveFileName(nullptr, "Save Goal Point", "", "YAML Files (*.yaml)").toStdString();
  
  if (!yaml_filename.empty())
  {
    // Create a YAML file and write the goal point data.
    std::ofstream yaml_file(yaml_filename);
    
    if (yaml_file.is_open())
    {
      // Write the position and orientation to the YAML file.
      yaml_file << "goal_x: " << position.x << std::endl;
      yaml_file << "goal_y: " << position.y << std::endl;
      yaml_file << "goal_z: " << position.z << std::endl;
      yaml_file << "goal_orientation_x: " << orientation.x << std::endl;
      yaml_file << "goal_orientation_y: " << orientation.y << std::endl;
      yaml_file << "goal_orientation_z: " << orientation.z << std::endl;
      yaml_file << "goal_orientation_w: " << orientation.w << std::endl;
      
      yaml_file.close();
    }
  }
}

} // end namespace rviz

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(rviz::SaveGoalTool, rviz::Tool)
