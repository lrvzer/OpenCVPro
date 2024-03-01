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

    // robot
    cv::Mat robot_x = (cv::Mat_<int>(2, 2) << 1, 0, 0, -1);
    cv::Mat robot_y = (cv::Mat_<int>(2, 2) << 0, 1, -1, 0);

    cv::Mat grad_x, grad_y, robot_ret;
    cv::filter2D(src, grad_x, -1, robot_x, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::filter2D(src, grad_y, -1, robot_y, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(grad_x, grad_x);
    cv::convertScaleAbs(grad_y, grad_y);

    cv::add(grad_x, grad_y, robot_ret);
    cv::imshow("robot gradient", robot_ret);

    // Sobel and Scharr
    cv::Mat s_ret;
    // cv::Sobel(src, grad_x, CV_32F, 1, 0);
    // cv::Sobel(src, grad_y, CV_32F, 0, 1);
    cv::Scharr(src, grad_x, CV_32F, 1, 0);
    cv::Scharr(src, grad_y, CV_32F, 0, 1);
    cv::convertScaleAbs(grad_x, grad_x);
    cv::convertScaleAbs(grad_y, grad_y);
    // cv::add(grad_x, grad_y, s_ret);
    cv::addWeighted(grad_x, 0.5, grad_y, 0.5, 0, s_ret);
    cv::imshow("s gradient", s_ret);

    // Laplacian
    cv::Mat dst;
    cv::Laplacian(src, dst, -1, 3, 1.0, 0, cv::BORDER_DEFAULT); // 噪声影响
    cv::imshow("Laplacian gradient", dst);

    cv::Mat sharpenKernel = (cv::Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cv::Mat sharpen_ret;
    cv::filter2D(src, sharpen_ret, CV_32F, sharpenKernel, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(sharpen_ret, sharpen_ret);
    cv::imshow("sharpen filter", sharpen_ret);

    cv::namedWindow("Input", cv::WINDOW_NORMAL);
    cv::imshow("Input", src);
    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
