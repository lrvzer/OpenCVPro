#include <iostream>
#include <opencv2/opencv.hpp>
cv::Mat src;
int t1 = 50;

void canny_demo(int pos, void* userdata)
{
    cv::Mat edges, dst;
    cv::Canny(src, edges, t1, t1 * 3, 3, false);
    cv::bitwise_and(src, src, dst, edges);
    cv::imshow("edges", edges);
    cv::imshow("dst", dst);
}

int main(int argc, char const* argv[])
{
    std::string filename;
    if (argc < 2)
    {
        std::cout << "please input image path!" << std::endl;
        return -1;
    }
    filename = argv[1];

    src = cv::imread(filename, cv::IMREAD_ANYCOLOR); // 读取一张图像
    if (src.empty())
    {
        std::cout << "picture could not find." << std::endl;
        return -1;
    }
    cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
    cv::imshow("Input", src);
    // canny demo

    cv::createTrackbar("threshold value: ", "Input", &t1, 100, canny_demo);
    canny_demo(0, 0);

    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
