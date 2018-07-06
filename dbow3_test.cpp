#include <iostream>
#include <iomanip>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "DBoW3.h"

using namespace DBoW3;
using namespace std;

// Given a list of image files, will compute the ORB descriptors for each of the images.
vector< cv::Mat  >  loadFeatures( std::vector<string> path_to_images,string descriptor="") throw (std::exception){
    //select detector
    cv::Ptr<cv::Feature2D> fdetector;
    if (descriptor=="orb")        fdetector=cv::ORB::create();
    else if (descriptor=="brisk") fdetector=cv::BRISK::create();
    else throw std::runtime_error("Invalid descriptor");
    assert(!descriptor.empty());
    vector<cv::Mat>    features;


    cout << "Extracting   features..." << endl;
    for(size_t i = 0; i < path_to_images.size(); ++i)
    {
        vector<cv::KeyPoint> keypoints;
        cv::Mat descriptors;
        cout<<"reading image: "<<path_to_images[i]<<endl;
        cv::Mat image = cv::imread(path_to_images[i], 0);
        if(image.empty())throw std::runtime_error("Could not open image"+path_to_images[i]);
        cout<<"extracting features"<<endl;
        fdetector->detectAndCompute(image, cv::Mat(), keypoints, descriptors);
        features.push_back(descriptors);
        cout << "# of keypoints : "<< keypoints.size() << endl;
        cout << "descriptors shape : "<< descriptors.rows << "x" << descriptors.cols << endl;
        cout<<"done detecting features"<<endl;
    }
    return features;
}

int main()
{

  std::vector<string> images_path;
  string BASE_PATH = "/home/mpkuse/catkin_ws/src/nap/slam_data/dbow3_vocab/Images/lip6kennedy_bigdoubleloop_";
  // images_path.push_back("/home/mpkuse/catkin_ws/src/nap/slam_data/dbow3_vocab/Images/lip6kennedy_bigdoubleloop_000000.ppm");
  // images_path.push_back("/home/mpkuse/catkin_ws/src/nap/slam_data/dbow3_vocab/Images/lip6kennedy_bigdoubleloop_000001.ppm");
  // images_path.push_back("/home/mpkuse/catkin_ws/src/nap/slam_data/dbow3_vocab/Images/lip6kennedy_bigdoubleloop_000002.ppm");
  // images_path.push_back("/home/mpkuse/catkin_ws/src/nap/slam_data/dbow3_vocab/Images/lip6kennedy_bigdoubleloop_000003.ppm");

  for( size_t i=0; i<10 ; i++ )
  {
    ostringstream ss;
    ss << BASE_PATH << std::setw(6) << std::setfill('0') << i << ".ppm";
    // cout << ss.str() << endl;
    images_path.push_back(ss.str());
  }




  vector< cv::Mat   >   features= loadFeatures(images_path,"orb");

  BowVector bow_vec;


  // Loads a pretrained Vocabulary
  Vocabulary voc("../orbvoc.dbow3");

  // Init a database
  Database db(voc, false, 0);

  // add images to the database
 for(size_t i = 0; i < features.size(); i++)
 {
     db.add(features[i], &bow_vec );
     cout << "bow_vec.size() : "<< bow_vec.size() << endl;
 }

  cout << "Database information: " << endl << db << endl;
  return 0;


  // Query newer images from the database.
  QueryResults ret;
  // for(size_t i = 0; i < features.size(); i++)
  // {
  //     db.query(features[i], ret, 4);
  //
  //     // ret[0] is always the same image in this case, because we added it to the
  //     // database. ret[1] is the second best match.
  //
  //     cout << "Searching for Image " << i << ". " << ret << endl;
  // }

  db.query(features[71], ret, 20);
  cout << "Searching for Image " << 71 << ". " << ret << endl;

}
