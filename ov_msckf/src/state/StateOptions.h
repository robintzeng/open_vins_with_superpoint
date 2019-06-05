#ifndef OV_MSCKF_STATE_OPTIONS_H
#define OV_MSCKF_STATE_OPTIONS_H


/**
 * @namespace ov_msckf
 * @brief The Open VINS MSCKF
 */
namespace ov_msckf {


    /**
     * @brief Struct which stores all our filter options
     */
    struct StateOptions {

        /// Bool to determine whether or not to do first estimate Jacobians
        bool do_fej = false;

        /// Bool to determine whether or not use imu message averaging
        bool imu_avg = false;

        /// Bool to determine whether or not to calibrate imu-to-camera pose
        bool do_calib_camera_pose = false;

        /// Bool to determine whether or not to calibrate camera intrinsics
        bool do_calib_camera_intrinsics = false;

        /// Bool to determine whether or not to calibrate camera to IMU time offset
        bool do_calib_camera_timeoffset = false;

        /// Max clone size of sliding window
        size_t max_clone_size = 8;

        /// Max number of estimated SLAM features
        size_t max_slam_features = 0;

        /// Number of cameras
        size_t num_cameras = 1;

    };


}

#endif //OV_MSCKF_STATE_OPTIONS_H
