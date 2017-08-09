/**
* This file is part of ORB-SLAM.
*
* Copyright (C) 2014 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <http://webdiis.unizar.es/~raulmur/orbslam/>
*
* ORB-SLAM is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FRAMEPUBLISHER_H
#define FRAMEPUBLISHER_H

#include "Tracking.h"
#include "MapPoint.h"
#include "Map.h"

#include "ros/ros.h"
#include <fstream>

//JSON stuff
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <cstdio>
// not sure if this stuff is needed/ok
#include <string>
#include <iostream>
#include <algorithm>

#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>

#include<boost/thread.hpp>

using namespace rapidjson;

namespace ORB_SLAM
{

class Tracking;

class FramePublisher
{
public:
    FramePublisher();    

    void Update(Tracking *pTracker);

    void Refresh();

    void SetMap(Map* pMap);

    int frameNum;

    Document boundingBoxes;

protected:

    cv::Mat DrawFrame();

    void PublishFrame();

    void DrawTextInfo(cv::Mat &im, int nState, cv::Mat &imText);

    cv::Mat mIm;
    vector<cv::KeyPoint> mvCurrentKeys;

    vector<bool> mvbOutliers;

    vector<MapPoint*> mvpMatchedMapPoints;
    int mnTracked;
    vector<cv::KeyPoint> mvIniKeys;
    vector<int> mvIniMatches;

    ros::NodeHandle mNH;
    ros::Publisher mImagePub;

    int mState;

    bool mbUpdated;

    Map* mpMap;

    boost::mutex mMutex;
};

} //namespace ORB_SLAM

#endif // FRAMEPUBLISHER_H
