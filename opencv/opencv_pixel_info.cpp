#include <iostream>
#include <opencv2/opencv.hpp>

/***
 * 图像最大与最小值
 * 图像均值与方差
 * 图像像素分布信息
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

    cv::Mat dst;
    int rows = src.rows;
    int cols = src.cols;
    int dims = src.channels();

    printf("width: %d, height: %d, dims: %d\n", cols, rows, dims);

    double minValue, maxValue;
    cv::Point minLocPoint, maxLocPoint;
    cv::minMaxLoc(src, &minValue, &maxValue, &minLocPoint, &maxLocPoint);
    printf("Min: %.2f, Max: %.2f\n", minValue, maxValue);

    cv::namedWindow("Input", cv::WINDOW_NORMAL);
    cv::imshow("Input", src);
    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
