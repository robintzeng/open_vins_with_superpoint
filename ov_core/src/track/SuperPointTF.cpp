#include"SuperPointTF.h"

void SuperPoint::cvmatToTensor(cv::Mat img,tensorflow::Tensor* output_tensor,int input_rows,int input_cols){
    img.convertTo(img,CV_32FC1);
    img= img/255;
    float *p = output_tensor->flat<float>().data();
    cv::Mat tempMat(input_rows, input_cols, CV_32FC1, p);
    img.convertTo(tempMat,CV_32FC1);
}

/////argsort
std::vector<int> SuperPoint::sortIndexes(float* v,int size){

  // initialize original index locations
  std::vector<int> idx(size);
  std::iota(idx.begin(), idx.end(),0);

  // sort indexes based on comparing values in v
  // using std::stable_sort instead of std::sort
  // to avoid unnecessary index re-orderings
  // when v contains elements of equal values 
  std::stable_sort(idx.begin(), idx.end(),
       [&v](size_t i1, size_t i2) {return v[i1] > v[i2];});
  return idx;
}

/*void SuperPoint::imageProcessing(cv::Mat&im){
  cvtColor(im, im, CV_RGB2GRAY);
  resize(im,im,cv::Size(cols,rows));
}*/

void SuperPoint::extract(int rows,int cols,int keyPtNum,float*keyData,Eigen::TensorMap<Eigen::Tensor<float, 4, 1, long>, 16>&descriptorTensor2,std::vector<cv::KeyPoint>&keyPoints,cv::Mat&desc){
  std::vector<int> index = sortIndexes(keyData,rows*cols);
  for(int i = 0 ; i < keyPtNum ; i ++){
    int ii = index[i];
    int row_ = std::floor(ii/cols);
    int col_ = ii%cols;
    keyPoints.push_back(cv::KeyPoint(col_, row_, 1));
    for(int j = 0 ; j < 256 ; j ++){
      desc.at<float>(i,j)= descriptorTensor2(0,row_,col_,j);
    }
  }
}
void SuperPoint::compute(const cv::Mat&im, std::vector<cv::KeyPoint>&keyPoints,cv::Mat &desc,std::unique_ptr<tensorflow::Session>&sess){
    
    // process image and turn into tensor
    //imageProcessing(im);
    int rows = im.rows;
    int cols = im.cols;

    tensorflow::Tensor x(tensorflow::DT_FLOAT, tensorflow::TensorShape({1,rows, cols,1}));
    cvmatToTensor(im,&x,rows,cols);

    // input the tensor into the neural network
    std::vector<std::pair<tensorflow::string, tensorflow::Tensor>> inputs;
    inputs.push_back(std::pair<std::string, tensorflow::Tensor>("superpoint/image", x));
    std::vector<tensorflow::Tensor> outputTensor;
    TF_CHECK_OK(sess -> Run(inputs, {"superpoint/prob_nms:0", "superpoint/descriptors:0"}, {}, &outputTensor));
    
    // extract the descriptor and keypoints from output tensor
    auto keyTensor = outputTensor[0].tensor<float, 3>();
    float* keyData = keyTensor.data();
    auto descriptorTensor = outputTensor[1].tensor<float, 4>();
    
    extract(rows,cols,keyPtNum,keyData,descriptorTensor,keyPoints,desc);
}
