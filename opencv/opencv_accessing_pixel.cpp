#include <iostream>
#include <opencv2/opencv.hpp>

// #define ACCESS_ARR
#define ACCESS_PTR

/**
 * 遍历和访问像素值
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

    cv::Mat src = cv::imread(filename, cv::IMREAD_COLOR); // 读取一张图像
    if (src.empty())
    {
        std::cout << "picture could not find." << std::endl;
        return -1;
    }

    int width = src.cols;
    int height = src.rows;
    int dim = src.channels();

#ifdef ACCESS_ARR
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            if (dim == 3)
            {
                cv::Vec3b pixel = src.at<cv::Vec3b>(row, col);
                int blue = pixel[0];
                int green = pixel[1];
                int red = pixel[2];
                src.at<cv::Vec3b>(row, col)[0] = 255 - blue;
                src.at<cv::Vec3b>(row, col)[1] = 255 - green;
                src.at<cv::Vec3b>(row, col)[2] = 255 - red;
            }

            if (dim == 1)
            {
                int pv = src.at<uchar>(row, col);
                src.at<uchar>(row, col) = 255 - pv;
            }
        }
    }

#elif defined(ACCESS_PTR)
    for (int row = 0; row < height; row++)
    {
        uchar* curr_row = src.ptr<uchar>(row);
        for (int col = 0; col < width; col++)
        {
            if (dim == 3)
            {
                int blue = *curr_row;
                *curr_row++ = 255 - blue;
                int green = *curr_row;
                *curr_row++ = 255 - green;
                int red = *curr_row;
                *curr_row++ = 255 - red;
            }

            if (dim == 1)
            {
                int pv = *curr_row;
                *curr_row++ = 255 - pv;
            }
        }
    }
#endif

    cv::namedWindow("Input", cv::WINDOW_NORMAL);
    cv::imshow("Input", src);
    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
