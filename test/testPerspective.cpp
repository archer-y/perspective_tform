#include "PerspectiveTransform.hpp"
#include "EigenCoordConverter.h"

using namespace std;

int main()
{
	
	cv::Mat src = cv::imread("/media/titan/media/Data/Dropbox/Data/VANS/Missions/2018-04-19/VANS1_2018-04-18-1500/payload/monoimages/thermal/00001244.png", cv::IMREAD_GRAYSCALE);
	cv::Mat jet, alpha;
	cv::applyColorMap(src, jet, cv::COLORMAP_JET);
	cv::cvtColor(jet, alpha, cv::COLOR_BGR2BGRA);

	// Transform image
	PerspectiveTransform ptransform;
	ptransform.LoadImage(alpha);
	ptransform.LoadCamera(9e-3, 1.7e-5, 640, 512);		// focal length, pixel size, width, height
	ptransform.LoadLLA(33.844405660151, -118.28032562365, 50);
	ptransform.LoadAttitude(166.04942321777 + 90, -16.717555999756, 8.8087778091431 + 15);			// yaw, pitch roll
	ptransform.ImageTransform();

	// Retrieve 4 channel image
	cv::Mat tform = ptransform.GetTransformedImage();
	cv::imshow("img", tform);
	cv::imwrite("/home/ben/writing.png", tform);
	cv::waitKey(500);


	return 0;
}