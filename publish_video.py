#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright 2016 Massachusetts Institute of Technology

"""Publish a video as ROS messages.
"""

import argparse

import numpy as np

import cv2

import rospy

from sensor_msgs.msg import Image
from sensor_msgs.msg import CameraInfo

from cv_bridge import CvBridge, CvBridgeError

bridge = CvBridge()

def main():
    """Publish a video as ROS messages.
    """
    # Patse arguments.
    parser = argparse.ArgumentParser(description="Convert video into a rosbag.")
    parser.add_argument("video_file", help="Input video.")
    parser.add_argument("-c", "--camera", default="camera", help="Camera name.")
    parser.add_argument("-f", "--frame_id", default="camera",
                        help="tf frame_id.")
    parser.add_argument("--width", type=np.int32, default="640",
                        help="Image width.")
    parser.add_argument("--height", type=np.int32, default="480",
                        help="Image height.")
    parser.add_argument("--info_url", default="file:///camera.yml",
                        help="Camera calibration url.")

    args = parser.parse_args()
    publish(args)

def publish(args):
    print "Publishing %s." % (args.video_file)

    # Set up node.
    rospy.init_node("video_publisher", anonymous=True)
    img_pub = rospy.Publisher("/camera/image_raw", Image,
                              queue_size=10)

    # Open video.
    video = cv2.VideoCapture(args.video_file)

    # Get frame rate.
    fps = video.get(cv2.cv.CV_CAP_PROP_FPS)
    rate = rospy.Rate(fps)

    # Loop through video frames.
    while not rospy.is_shutdown() and video.grab():
        tmp, img = video.retrieve()

        if not tmp:
            print "Could not grab frame."
            break
        
        try:
            # Publish image.
            img_msg = bridge.cv2_to_imgmsg(img, "bgr8")
            img_msg.header.stamp = rospy.Time.now()
            img_msg.header.frame_id = args.frame_id
            img_pub.publish(img_msg)
        except CvBridgeError as err:
            print err

        rate.sleep()

    return

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass
