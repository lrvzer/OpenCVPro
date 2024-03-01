#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char const* argv[])
{
    cv::Mat src = (cv::Mat_<int>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    // robot
    cv::Mat robot_x = (cv::Mat_<int>(2, 2) << 1, 0, 0, -1);
    cv::Mat robot_y = (cv::Mat_<int>(2, 2) << 0, 1, -1, 0);

    cv::Mat grad_x, grad_y, robot_ret;
    cv::filter2D(src, grad_x, -1, robot_x, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::filter2D(src, grad_y, -1, robot_y, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(grad_x, grad_x);
    cv::convertScaleAbs(grad_y, grad_y);
    cv::add(grad_x, grad_y, robot_ret);

    // Sobel and Scharr
    // cv::Mat s_ret;
    // // cv::Sobel(src, grad_x, CV_32F, 1, 0);
    // // cv::Sobel(src, grad_y, CV_32F, 0, 1);
    // cv::Scharr(src, grad_x, CV_32F, 1, 0);
    // cv::Scharr(src, grad_y, CV_32F, 0, 1);
    // cv::convertScaleAbs(grad_x, grad_x);
    // cv::convertScaleAbs(grad_y, grad_y);
    // // cv::add(grad_x, grad_y, s_ret);
    // cv::addWeighted(grad_x, 0.5, grad_y, 0.5, 0, s_ret);

    return 0;
}

void printMat(cv::Mat src)
{
    for (int row = 0; row < src.rows; row++)
    {
        for (int col = 0; col < src.cols; col++)
        {
            std::cout << src.at<float>(row, col) << ' ';
        }
        std::cout << std::endl;
    }
}