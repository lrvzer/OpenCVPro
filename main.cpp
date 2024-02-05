#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char const *argv[])
{
    /**
     * cv::IMREAD_COLOR
     * cv::IMREAD_GRAYSCALE  灰度图像
     * cv::IMREAD_ANYCOLOR
     */
    cv::Mat src = cv::imread("../images/lena.jpg", cv::IMREAD_ANYCOLOR); // 读取一张图像
    if (src.empty()) 
    {
        std::cout << "picture could not find." <<std::endl;
        return -1;
    }
    /**
     * cv::WINDOW_AUTOSIZE   适配图像大小，窗口不可改动
     * cv::WINDOW_FREERATIO  窗口可改动
     * cv::WINDOW_NORMAL     窗口可改动
     */
    cv::namedWindow("Input", cv::WINDOW_NORMAL);
    cv::imshow("Input", src);
    cv::waitKey(0); // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
