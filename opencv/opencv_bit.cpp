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

    cv::Mat dstNot;
    cv::Mat mask = cv::Mat::zeros(src.size(), CV_8UC1);
    int rows = src.rows / 2;
    int cols = src.cols / 2;
    for (int row = 120; row < rows + 120; row++)
    {
        for (int col = 100; col < cols + 100; col++)
        {
            mask.at<uchar>(row, col) = 255;
        }
    }

    // 图像取反
    cv::bitwise_not(src, dstNot, mask); // 对指定mask的ROI区域进行取反操作（255-v）
    cv::imshow("bitwise_not", dstNot);

    // 与操作
    cv::Mat dstAnd;
    cv::bitwise_and(src, src, dstAnd, mask);
    cv::imshow("bitwise_and", dstAnd);

    // 或操作
    cv::Mat dstOr;
    cv::bitwise_or(src, src, dstOr, mask);
    cv::imshow("bitwise_or", dstOr);

    cv::namedWindow("Input", cv::WINDOW_NORMAL);
    cv::imshow("Input", src);
    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
