#include <iostream>
#include <opencv2/opencv.hpp>

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

    // 高斯模糊
    cv::Mat g_dst;
    // cv::GaussianBlur(src, g_dst, cv::Size(5, 5), 0);
    cv::GaussianBlur(src, g_dst, cv::Size(0, 0), 15);
    cv::imshow("g_dst", g_dst);

    // 盒子模糊
    cv::Mat b_dst;
    // cv::boxFilter(src, b_dst, -1, cv::Size(5, 5), cv::Point(-1, -1), true, cv::BORDER_DEFAULT);
    // cv::boxFilter(src, b_dst, -1, cv::Size(15, 1), cv::Point(-1, -1), true, cv::BORDER_DEFAULT);
    cv::boxFilter(src, b_dst, -1, cv::Size(1, 15), cv::Point(-1, -1), true, cv::BORDER_DEFAULT);
    cv::imshow("b_dst", b_dst);

    cv::namedWindow("Input", cv::WINDOW_NORMAL);
    cv::imshow("Input", src);
    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
