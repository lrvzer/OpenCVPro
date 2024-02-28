#include <iostream>
#include <opencv2/opencv.hpp>

/**
 * 图像的加载和保存
 */
int main(int argc, char const* argv[])
{
    std::string filename;
    if (argc < 2)
    {
        std::cout << "please input image path!" << std::endl;
        return -1;
    }
    filename = argv[1];

    cv::Mat src = cv::imread(filename, cv::IMREAD_ANYCOLOR); // 读取一张图像
    if (src.empty())
    {
        std::cout << "picture could not find." << std::endl;
        return -1;
    }

    cv::Mat lut = cv::Mat(256, 1, CV_8UC3);

    for (int i = 0; i < 256; i++)
    {
        lut.at<cv::Vec3b>(i, 0) = src.at<cv::Vec3b>(10, i);
    }

    cv::imshow("color", src);

    cv::Mat dst;
    cv::LUT(src, lut, dst);
    cv::imshow("dst", dst);

    cv::applyColorMap(src, dst, cv::COLORMAP_AUTUMN);
    cv::imshow("autumn", dst);

    cv::namedWindow("Input", cv::WINDOW_NORMAL);
    cv::imshow("Input", src);
    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
