#!/bin/bash
# This script will install Cocos2d-x with EziSocial template in your cocos2d-x folder.
# To install the project, use following command from your terminal.
#
# The script is tested on Mac platform only.
#
# sudo ./install_ezisocial.sh
#
# It will ask your password and then later for the Cocos2d-x root folder.
# Specify the root folder and then script will take care of further installation.
# In case of any issue, write to support@ezibyte.com
#
# Created By: Paras Mendiratta
# Date: 12 Sep 2013
# EziByte Technologies (TM)
#
# All rights reserved.
#

echo ""
echo "Welcome to EziSocial Plugin Installer"
echo "The script is for Cocos2d-x 2.1.5 version."
echo ""
echo "Please specify your Cocos2d-x Root folder:"
read cocos2dx_root_folder
echo "You have selected cocos2dx root folder as: $cocos2dx_root_folder"
echo ""
echo ""
echo "................................................................."
echo ".         Begining Installation of EziSocial Plugin             ."
echo "................................................................."
echo ""
echo ""
echo ""

# Configure the variables...
SRC_EZIBYTE_FOLDER="ezibyte"
SRC_TEMPLATE_FOLDER="multi-platform-cpp-ezisocial"
SRC_PROJECT_CREATOR_SCRIPT="project-creator/create_project_with_ezisocial.py"

DST_EZIBYTE_FOLDER="$cocos2dx_root_folder"
DST_TEMPLATE_FOLDER="$cocos2dx_root_folder/template"
DST_PROJECT_CREATOR_SCRIPT="$cocos2dx_root_folder/tools/project-creator"

# Step 1
# Copy EziByte Folder in Cocos2d-x Root Directory
cp -R -f $SRC_EZIBYTE_FOLDER $DST_EZIBYTE_FOLDER
echo "copied ezibyte folder to cocos2d-x root folder"

# Step 2 
# Copy multi-platform-cpp-ezisocial template folder in Cocos2d-x Root/template Directory
cp -R -f $SRC_TEMPLATE_FOLDER $DST_TEMPLATE_FOLDER
echo "copied multi-platform template folder to cocos2d-x template folder"

# Step 3
# Copy create_project_with_ezisocial.py script file to Cocos2d-x Root/tools/project-creator Directory
cp -f $SRC_PROJECT_CREATOR_SCRIPT $DST_PROJECT_CREATOR_SCRIPT
echo "copied project creator script to cocos2d-x root project-folder"

# Installation Finished. Say GoogBye note :)
echo ""
echo ""
echo ""
echo "Installation finished..."
echo "Please goto $cocos2dx_root_folder/tools/project-creator directory and run script create_project_with_ezisocial.py to create your first project with EziSocial Plugin "
echo ""
echo "To run script:"
echo "python create_project_with_ezisocial.py -project YOUR_PROJECT_NAME -package PACKAGE_NAME -language cpp"
echo ""
echo "Thank you!"
echo "Team EziByte"
