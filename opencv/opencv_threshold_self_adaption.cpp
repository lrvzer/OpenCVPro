#include <iostream>
#include <opencv2/opencv.hpp>
cv::Mat src;
int t1 = 50;

int main(int argc, char const* argv[])
{
    std::string filename;
    if (argc < 2)
    {
        std::cout << "please input image path!" << std::endl;
        return -1;
    }
    filename = argv[1];

    src = cv::imread(filename, cv::IMREAD_ANYCOLOR); // 读取一张图像
    if (src.empty())
    {
        std::cout << "picture could not find." << std::endl;
        return -1;
    }
    cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
    cv::imshow("Input", src);

    cv::Mat gray, binary;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // 均值法
    cv::Scalar m = cv::mean(gray);
    printf("means: %.2f\n", m[0]);
    cv::threshold(gray, binary, m[0], 255, cv::THRESH_BINARY);
    cv::imshow("mean", binary);

    double d1 = cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::imshow("THRESH_OTSU", binary);

    double d2 = cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_TRIANGLE);
    cv::imshow("THRESH_TRIANGLE", binary);

    printf("otsu threshold: %.2f, triangle threshold: %.2f\n", d1, d2);

    cv::adaptiveThreshold(gray, binary, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 25, 10);
    cv::imshow("ADAPTIVE_THRESH_GAUSSIAN_C", binary);

    cv::adaptiveThreshold(gray, binary, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 25, 10);
    cv::imshow("ADAPTIVE_THRESH_MEAN_C", binary);

    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
