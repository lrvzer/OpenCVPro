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

    // 1.创建空白的Mat对象
    // cv::Mat dest = cv::Mat(256, 256, CV_8UC1); // 灰度图像
    // dest = cv::Scalar(0);
    // 1.1>
    // cv::Mat dest = cv::Mat(256, 256, CV_8UC3); // 三通道图像
    // dest = cv::Scalar(0, 0, 255);              // BGR(0, 0, 255)

    // 1.2>
    // cv::Mat dest = cv::Mat(cv::Size(256, 256), CV_8UC3);
    // dest = cv::Scalar(255, 0, 255); // BGR(255, 0, 255)

    // 1.3>
    // cv::Mat dest = cv::Mat::zeros(cv::Size(256, 256), CV_8UC3);

    // 2.从现有图像创建
    // 2.1> 图片拷贝
    // cv::Mat dest = src;         // dest和src指向同一个数据块
    // cv::Mat dest = src.clone(); // 复制一份新的数据块
    // cv::Mat dest; // 复制一份新的数据块
    // src.copyTo(dest);
    // dest = cv::Scalar(0, 255, 255);

    // 2.2>
    cv::Mat dest = cv::Mat::zeros(src.size(), src.type());

    // 3.创建填充值的Mat对象
    // 4.创建单通道与多通道Mat对象
    cv::namedWindow("Output", cv::WINDOW_AUTOSIZE);
    cv::imshow("Input", src);
    cv::imshow("Output", dest);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
