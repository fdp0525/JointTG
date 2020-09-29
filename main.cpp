
//#include <Core/Camera/PinholeCameraIntrinsic.h>
//#include <Core/Camera/PinholeCameraTrajectory.h>
//#include <IO/ClassIO/IJsonConvertibleIO.h>
//#include <IO/ClassIO/PinholeCameraTrajectoryIO.h>
//#include <IO/ClassIO/ImageIO.h>
//#include <IO/ClassIO/TriangleMeshIO.h>
//#include <Core/Geometry/Image.h>
//#include <Core/Geometry/RGBDImage.h>
//#include <Core/Geometry/TriangleMesh.h>
//#include <Core/ColorMap/ColorMapOptimization.h>

//#include <Visualization/Utility/DrawGeometry.h>
#include <Open3D.h>
#include <ceres/ceres.h>
//#include "glog/logging.h"
//#include <mypointcloudgenetool.h>
#include <boost/filesystem.hpp>
#include "jointtgconfig.h"

using namespace open3d;

/**
 * @brief checkNumOfFileInPath automatically calculate the number of key-frames
 * @param filepath             file path
 * @param fileExtension        file extension(such as ".png" ".jgp")
 * @return
 */
int checkNumOfFileInPath(const std::string filepath, const std::string fileExtension)
{
    boost::filesystem::directory_iterator   end_iter;
    int  num = 0;
    for(boost::filesystem::directory_iterator  iter(filepath); iter!= end_iter;iter++)
    {
        if(strcmp(boost::filesystem::extension(*iter).c_str(), fileExtension.c_str()) == 0)
        {
            num++;
        }
    }
    return num;
}

int main(int argc, char** argv)
{
    if(argc != 4)
    {
        std::cerr<<"Too few arguments:"<<std::endl;
        std::cout<<"Usage: " + std::string(argv[0]) + " IN_IMAGES IN_MESH IN_TRAJECTORY"<<std::endl;
        return 0;
    }

//    std::string filedir = "keyboard";
//    std::string imagedir = "/images";
    int num = checkNumOfFileInPath(argv[1],".png");

    std::vector<std::shared_ptr<open3d::geometry::RGBDImage> > rgbdimages;
    for(int i =0;i<num;i++)
    {
        char rgbbuf[512];
        sprintf(rgbbuf,"%s/%05d.jpg",argv[1], i);
        char depthbuf[512];
        sprintf(depthbuf,"%s/%05d.png",argv[1], i);
        std::cout<<"rgbiamge:"<<rgbbuf<<"2----depthimage:"<<depthbuf<<std::endl;
        open3d::geometry::Image rgbimage,depthimage;
        std::cout<<rgbbuf<<std::endl;
        open3d::io::ReadImageFromJPG(rgbbuf, rgbimage);
        std::cout<<depthbuf<<std::endl;
        open3d::io::ReadImageFromPNG(depthbuf,depthimage);

        std::shared_ptr<open3d::geometry::RGBDImage> image = open3d::geometry::CreateRGBDImageFromColorAndDepth(rgbimage, depthimage, 1000.0, 4.5,false);
        rgbdimages.push_back(image);
    }
    open3d::camera::PinholeCameraTrajectory trajectory;
    open3d::camera::PinholeCameraParameters  intrinsics;


    intrinsics.intrinsic_.SetIntrinsics(JointTGConfig::get().IMAGE_WIDTH,JointTGConfig::get().IMAGE_HEIGHT, JointTGConfig::get().IMAGE_FX, JointTGConfig::get().IMAGE_FY, JointTGConfig::get().IMAGE_CX, JointTGConfig::get().IMAGE_CY);
    //color
    intrinsics.colorintrinsic_.SetIntrinsics(JointTGConfig::get().IMAGE_WIDTH,JointTGConfig::get().IMAGE_HEIGHT, JointTGConfig::get().IMAGE_FX, JointTGConfig::get().IMAGE_FY, JointTGConfig::get().IMAGE_CX, JointTGConfig::get().IMAGE_CY);
    //depth
    intrinsics.depthintrinsic_.SetIntrinsics(JointTGConfig::get().DEPTH_WIDTH,JointTGConfig::get().DEPTH_HEIGHT, JointTGConfig::get().DEPTH_FX, JointTGConfig::get().DEPTH_FY, JointTGConfig::get().DEPTH_CX, JointTGConfig::get().DEPTH_CY);

    trajectory.parameters_.push_back(intrinsics);
    open3d::io::ReadPinholeCameraTrajectory(argv[3], trajectory);//the camera trajectory (world-->camera)


    open3d::geometry::TriangleMesh mesh;

    open3d::io::ReadTriangleMesh(argv[2], mesh);//read the 3D recosntructed model
    mesh.Purge();
    mesh.ComputeTriangleNormals();
    mesh.ComputeVertexNormals();
    mesh.ComputeAdjacencyList();



    open3d::color_map::ColorMapOptimizationOption option;
    option.maximum_iteration_ = 0;
    option.non_rigid_camera_coordinate_ = false;
    open3d::color_map::ColorMapOptimization(mesh, rgbdimages, trajectory, option);

    open3d::io::WriteTriangleMesh("withoutoption.ply",mesh);//without any optimization


    open3d::color_map::ColorAndMeshOptimization(mesh, rgbdimages, trajectory);//joint opetimizaiton


    open3d::io::WriteTriangleMesh("JointTG.ply", mesh);

}
