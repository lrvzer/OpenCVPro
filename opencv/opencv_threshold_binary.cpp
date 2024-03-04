#include <iostream>
#include <opencv2/opencv.hpp>
cv::Mat src;
int t1 = 50;

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

    cv::Mat gray, binary;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY);
    cv::imshow("THRESH_BINARY", binary);

    cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY_INV);
    cv::imshow("THRESH_BINARY_INV", binary);

    cv::threshold(gray, binary, 127, 255, cv::THRESH_TRUNC);
    cv::imshow("THRESH_TRUNC", binary);

    cv::threshold(gray, binary, 127, 255, cv::THRESH_TOZERO);
    cv::imshow("THRESH_TOZERO", binary);

    cv::threshold(gray, binary, 127, 255, cv::THRESH_TOZERO_INV);
    cv::imshow("THRESH_TOZERO_INV", binary);

    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
