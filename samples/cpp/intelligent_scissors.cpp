#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgproc/segmentation.hpp"

using namespace cv;
using namespace cv::segmentation;

Mat img;

// static void onMouse(int event, int x, int y, int , void* userdata)
// {
//     segmentation::IntelligentScissorsMB* param = reinterpret_cast<segmentation::IntelligentScissorsMB*>(userdata);
//     Point targrt_point = Point(x, y);
//     if (event == EVENT_LBUTTONDOWN)
//     {

//         param->buildMap(targrt_point);
//     }
//     else if (event == EVENT_MOUSEMOVE)
//     {
//         std::vector<Point> result;
//         param->getContour(targrt_point,result);
//         drawContours(img, result, static_cast<int>(result.size()) - 1, Scalar(0,255,0), FILLED);
//         imshow("lasso", img);
//     }
// }

const char* keys =
{
    "{help h | |}"
    "{@image | fruits.jpg| Path to image to process}"
};


int main( int argc, const char** argv )
{
    CommandLineParser parser(argc, argv, keys);
    parser.about("\nThis program demonstrates implementation of 'Intelligent Scissors' algorithm designed\n"
                 "by Eric N. Mortensen and William A. Barrett, and described in article\n"
                 "'Intelligent Scissors for Image Composition':\n"
                 "http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.138.3811&rep=rep1&type=pdf\n"
                 "To start drawing a new contour select a pixel, click LEFT mouse button.\n"
                 "To fix a path click LEFT mouse button again.\n"
                 "To finish drawing a contour click RIGHT mouse button.\n");
    if (parser.has("help"))
    {
        parser.printMessage();
        return 1;
    }

    std::vector<std::vector<Point> > c;
    std::string filename = parser.get<std::string>(0);

    img = imread(samples::findFile(filename));


    segmentation::IntelligentScissorsMB tool;
    tool.setEdgeFeatureCannyParameters(16, 100).setGradientMagnitudeMaxLimit(200);
    tool.applyImage(img);
    Point source_point(30, 40);
    tool.buildMap(source_point);

    Point target_point(120, 300);
    std::vector<Point> pts;
    tool.getContour(target_point, pts);
    c.push_back(pts);

    drawContours(img, c, -1, Scalar(255,255,0), 2, 1);
    // setMouseCallback("lasso", onMouse, &tool);
    imshow("lasso", img);

    std::cout<< pts;
    waitKey(0);
}
