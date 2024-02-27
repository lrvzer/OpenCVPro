#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

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
    cv::Mat src = cv::imread(filename, cv::IMREAD_UNCHANGED); // 读取一张图像
    if (src.empty())
    {
        std::cout << "picture could not find." << std::endl;
        return -1;
    }

    cv::Mat dst;
    int rows = src.rows;
    int cols = src.cols;
    int ch = src.channels();

    printf("width: %d, height: %d, channels: %d\n", cols, rows, ch);

    // 最大值最小值
    cv::Mat image_re = src.reshape(1);
    double minValue, maxValue;
    cv::Point minLocPoint, maxLocPoint;
    /**
     * Finds the global minimum and maximum in an array.
     * The function cv::minMaxLoc finds the minimum and maximum element values and their positions.
     * The extremums are searched across the whole array or, if mask is not an empty array, in the specified array region.
     * The function do not work with multi-channel arrays.
     *
     * Notes:
     * If you need to find minimum or maximum elements across all the channels, use Mat::reshape first to reinterpret the array as single-channel.
     * Or you may extract the particular channel using either extractImageCOI, or mixChannels, or split.
     */
    cv::minMaxLoc(image_re, &minValue, &maxValue, &minLocPoint, &maxLocPoint); // 不支持多通道数组
    printf("Min: %.2f, Max: %.2f\n", minValue, maxValue);

    // 均值方差
    cv::Scalar s = cv::mean(src);
    printf("mean b: %.2f, g: %.2f, r: %.2f\n", s[0], s[1], s[2]);

    cv::Mat mm, mstd;
    // 均值和方差
    cv::meanStdDev(src, mm, mstd);
    printf("rows: %d, cols: %d\n", mstd.rows, mstd.cols);
    printf("mean  : %.2f, %.2f, %.2f\n", mm.at<double>(0, 0), mm.at<double>(1, 0), mm.at<double>(2, 0));
    printf("stddev: %.2f, %.2f, %.2f\n", mstd.at<double>(0, 0), mstd.at<double>(1, 0), mstd.at<double>(2, 0));

    // 像素值统计
    std::vector<int> histB(256);
    std::vector<int> histG(256);
    std::vector<int> histR(256);
    std::vector<int> hist(256);
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            if (ch == 3)
            {
                cv::Vec3b pv = src.at<cv::Vec3b>(row, col);
                histB[pv[0]]++;
                histG[pv[1]]++;
                histR[pv[2]]++;
            }

            if (ch == 1)
            {
                int pv = src.at<uchar>(row, col);
                hist[pv]++;
            }
        }
    }

    cv::namedWindow("Input", cv::WINDOW_NORMAL);
    cv::imshow("Input", src);
    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
