#include <iostream>
#include <opencv2/opencv.hpp>

void self_blur(cv::Mat& src, cv::Mat& dst, int row, int col, int channel);

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

    cv::Mat dst = src.clone();

    int rows = src.rows; // height
    int cols = src.cols; // width

    for (int row = 1; row < rows - 1; row++)
    {
        for (int col = 1; col < cols - 1; col++)
        {
            self_blur(src, dst, row, col, 0);
            self_blur(src, dst, row, col, 1);
            self_blur(src, dst, row, col, 2);
        }
    }

    cv::Mat dst2;
    // 锚定位置，cv::Point(-1, -1)：默认卷积的中心位置
    cv::blur(src, dst2, cv::Size(3, 3), cv::Point(-1, -1), cv::BORDER_DEFAULT);
    cv::imshow("blur", dst2);

    int border = 8;
    cv::Mat border_mat;
    // cv::copyMakeBorder(src, border_mat, border, border, border, border, cv::BORDER_DEFAULT);
    // cv::copyMakeBorder(src, border_mat, border, border, border, border, cv::BORDER_CONSTANT, cv::Scalar(0, 255, 0));
    cv::copyMakeBorder(src, border_mat, border, border, border, border, cv::BORDER_WRAP, cv::Scalar(0, 255, 0));
    cv::imshow("copyMakeBorder", border_mat);

    cv::namedWindow("Input", cv::WINDOW_NORMAL);
    cv::imshow("Input", src);
    cv::imshow("Onput", dst);
    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}

/**

 */
void self_blur(cv::Mat& src, cv::Mat& dst, int row, int col, int channel)
{
    int ret = src.at<cv::Vec3b>(row - 1, col - 1)[channel] + src.at<cv::Vec3b>(row - 1, col)[channel] + src.at<cv::Vec3b>(row - 1, col + 1)[channel] +
              src.at<cv::Vec3b>(row, col - 1)[channel] + src.at<cv::Vec3b>(row, col)[channel] + src.at<cv::Vec3b>(row, col + 1)[channel] +
              src.at<cv::Vec3b>(row + 1, col - 1)[channel] + src.at<cv::Vec3b>(row + 1, col)[channel] + src.at<cv::Vec3b>(row + 1, col + 1)[channel];

    dst.at<cv::Vec3b>(row, col)[channel] = ret / 9;
}