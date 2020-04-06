#ifndef OV_CORE_SUPERPOINT_H
#define OV_CORE_SUPERPOINT_H

#include <opencv2/opencv.hpp>
#include "tensorflow/core/public/session.h"
#include "tensorflow/cc/saved_model/loader.h"
#include "tensorflow/cc/saved_model/tag_constants.h"
#include "tensorflow/core/protobuf/meta_graph.pb.h"

#include <ros/ros.h>
#include <ros/package.h>
#include<iostream>
#include<vector>
#include <cmath>

class SuperPointNetwork{
  public: 
    SuperPointNetwork(){
      // Initialize a tensorflow session
      options.config.mutable_gpu_options()->set_allow_growth(true);
      status = NewSession(options, &session);    
      // prepare session
      TF_CHECK_OK(tensorflow::LoadSavedModel(sess_options, run_options, \
        graph_fn, {tensorflow::kSavedModelTagServe}, &bundle));
      graph_def = bundle.meta_graph_def;
    }
    ~SuperPointNetwork(){
      session-> Close();
    }
    std::unique_ptr<tensorflow::Session>&sess = bundle.session;
  
  private:
    tensorflow::Session* session;
    tensorflow::SessionOptions options = tensorflow::SessionOptions();
    tensorflow::Status status;
    const std::string& graph_fn = "/home/robin/work/src/tensorflow_ros_test/models/sp_v6";
    tensorflow::SessionOptions sess_options;
    tensorflow::RunOptions run_options;
    tensorflow::MetaGraphDef graph_def;
    tensorflow::SavedModelBundle bundle;
};

class SuperPoint{
  
  public:
    SuperPoint(){
      keyPtNum = 2000; 
    }
    SuperPoint(int keyPtNum){
      this->keyPtNum = keyPtNum;
    }
    void compute(const cv::Mat& im, std::vector<cv::KeyPoint>&keyPoints,cv::Mat & desc,std::unique_ptr<tensorflow::Session>& sess);
  private:
    int keyPtNum; 
    //void imageProcessing(cv::Mat& img);
    void cvmatToTensor(cv::Mat img,tensorflow::Tensor* output_tensor,int input_rows,int input_cols);
    void extract(int rows,int cols,int keyPtNum,float*keyData,Eigen::TensorMap<Eigen::Tensor<float, 4, 1, long>, 16>&descriptorTensor2,std::vector<cv::KeyPoint>&keyPoints,cv::Mat&desc);
    std::vector<int> sortIndexes(float* v,int size);
};
#endif /* OV_SUPERPOINT_H */