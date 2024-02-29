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

    // 自定义滤波，均值卷积
    int k = 15;
    cv::Mat kernel = cv::Mat::ones(k, k, CV_32F) / (float)(k * k); // k*k矩阵，并归一化
    std::cout << kernel.channels() << std::endl;
    for (int row = 0; row < kernel.rows; row++)
    {
        for (int col = 0; col < kernel.cols; col++)
        {
            std::cout << kernel.at<float>(row, col) << ' ';
        }
        std::cout << std::endl;
    }
    cv::Mat dst;
    cv::filter2D(src, dst, -1, kernel, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::imshow("dst", dst);

    // 非均值滤波器
    cv::Mat robot = (cv::Mat_<int>(2, 2) << 1, 0, 0, -1);

    cv::Mat result;
    // cv::filter2D(src, result, -1, robot, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::filter2D(src, result, -1, robot, cv::Point(-1, -1), 127, cv::BORDER_DEFAULT);
    cv::imshow("result", result);

    cv::convertScaleAbs(result, result);

    cv::namedWindow("Input", cv::WINDOW_NORMAL);
    cv::imshow("Input", src);
    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
