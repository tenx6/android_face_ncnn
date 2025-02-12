//
// Created by ZL on 2019-06-14.
//

#ifndef NCNNDEMO_MTCNN_H
#define NCNNDEMO_MTCNN_H

#include "net.h"
#include <math.h>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include <map>
#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
struct Bbox {
    float score;
    int x1;
    int y1;
    int x2;
    int y2;
    float area;
    float ppoint[10];
    float regreCoord[4];
};

class MTCNN {

public:
    MTCNN(const string &model_path);

    MTCNN(std::vector<std::string> param_files, std::vector<std::string> bin_files);

    ~MTCNN();

    void SetMinFace(int minSize);

    void detect(cv::Mat &img_, std::vector<Bbox> &finalBbox);

private:
    void generateBbox(ncnn::Mat score, ncnn::Mat location, vector<Bbox> &boundingBox_, float scale);

    void nms(vector<Bbox> &boundingBox_, const float overlap_threshold, string modelname = "Union");

    void refine(vector<Bbox> &vecBbox, const int &height, const int &width, bool square);

    void PNet();

    void RNet();

    void ONet();

    ncnn::Net Pnet, Rnet, Onet;
    ncnn::Mat img;
    const float nms_threshold[3] = {0.5f, 0.7f, 0.7f};
    const float mean_vals[3] = {127.5, 127.5, 127.5};
    const float norm_vals[3] = {0.0078125, 0.0078125, 0.0078125};
    const int MIN_DET_SIZE = 12;
    std::vector<Bbox> firstBbox, secondBbox, thirdBbox;
    int img_w, img_h;

private:
    const float threshold[3] = {0.8f, 0.8f, 0.6f};
    int minsize = 40;
    const float pre_facetor = 0.709f;

};

#endif //NCNNDEMO_MTCNN_H
