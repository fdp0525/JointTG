/**
  * @author fyp
  */

#ifndef JOINTTGCONFIG_H
#define JOINTTGCONFIG_H

#include <iostream>
#include <opencv2/opencv.hpp>

class JointTGConfig
{
public:
    static const JointTGConfig & get()
    {
        static const JointTGConfig instance;
        return instance;
    }

public:
    float IMAGE_FX;
    float IMAGE_FY;
    float IMAGE_CX;
    float IMAGE_CY;
    float DEPTH_FX;
    float DEPTH_FY;
    float DEPTH_CX;
    float DEPTH_CY;
    int    DEPTH_WIDTH;
    int    DEPTH_HEIGHT;
    int    IMAGE_WIDTH;
    int    IMAGE_HEIGHT;

    int  EXTERNAL_ITER_NUM;//the iteration number of the external loop;
    int  TEX_ITER_NUM;//the iteration number of texture optimizaiton
    int  GEO_ITER_NUM;//the iteration number of geometry optimizaiton
    int  ILLUM_ITER_NUM;//the iteration number of illumination consistency optimizaiton

    float  lambda_c;
    float  lambda_d;
    float  lambda_H;
    float  lambda_L;
    float  lambda_R;
    float  lambda_hb;

 private:
    JointTGConfig()
        : EXTERNAL_ITER_NUM(3),
          TEX_ITER_NUM(50),
          ILLUM_ITER_NUM(10),
          GEO_ITER_NUM(20),
          lambda_c(1.0f),
          lambda_d(100.0f),
          lambda_H(10000.0f),
          lambda_L(1000.0f),
          lambda_R(1000.0f),
          lambda_hb(0.2f)
    {
        cv::FileStorage  fs2("../Config/config.yml", cv::FileStorage::READ);

        if(!fs2.isOpened())
        {
            std::cout << "Failed to open settings file at: "  << std::endl;
        }

    //depth
        fs2["depth_fx"]>>DEPTH_FX;
        fs2["depth_fy"]>>DEPTH_FY;
        fs2["depth_cx"]>>DEPTH_CX;
        fs2["depth_cy"]>>DEPTH_CY;
        fs2["depth_width"]>>DEPTH_WIDTH;
        fs2["depth_height"]>>DEPTH_HEIGHT;
        std::cout<<"depth fx:"<<DEPTH_FX<<" fy:"<<DEPTH_FY<<" cx:"<<DEPTH_CX<<" cy:"<<DEPTH_CY<<" width:"<<DEPTH_WIDTH<<" height:"<<DEPTH_HEIGHT<<std::endl;

       //rgb
        fs2["RGB_fx"]>>IMAGE_FX;
        fs2["RGB_fy"]>>IMAGE_FY;
        fs2["RGB_cx"]>>IMAGE_CX;
        fs2["RGB_cy"]>>IMAGE_CY;
        fs2["RGB_width"]>>IMAGE_WIDTH;
        fs2["RGB_height"]>>IMAGE_HEIGHT;
        std::cout<<"RGB fx:"<<IMAGE_FX<<" fy:"<<IMAGE_FY<<" cx:"<<IMAGE_CX<<" cy:"<<IMAGE_CY<<" width:"<<IMAGE_WIDTH<<" height:"<<IMAGE_HEIGHT<<std::endl;

        fs2["external_Iterations"]>>EXTERNAL_ITER_NUM;
        fs2["texture_Iterations"]>>TEX_ITER_NUM;
        fs2["illum_Iterations"]>>ILLUM_ITER_NUM;
        fs2["geometry_Iterations"]>>GEO_ITER_NUM;

        fs2["lambda_c"]>>lambda_c;
        fs2["lambda_d"]>>lambda_d;
        fs2["lambda_H"]>>lambda_H;
        fs2["lambda_L"]>>lambda_L;
        fs2["lambda_R"]>>lambda_R;
        fs2["lambda_hb"]>>lambda_hb;

    }


};
#endif // JOINTTGCONFIG_H
