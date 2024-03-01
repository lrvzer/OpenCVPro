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

    // Laplacian
    cv::Mat blurM, dst;
    cv::GaussianBlur(src, blurM, cv::Size(3, 3), 0);
    cv::Laplacian(src, dst, -1, 1, 1.0, 0, cv::BORDER_DEFAULT); // 噪声影响
    cv::imshow("Laplacian gradient", dst);

    cv::Mat ret;
    cv::addWeighted(blurM, 1.0, dst, -0.7, 0, ret);
    cv::imshow("usm filter", ret);

    cv::namedWindow("Input", cv::WINDOW_NORMAL);
    cv::imshow("Input", src);
    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
