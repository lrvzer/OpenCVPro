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

    cv::Mat image = src.clone();

    // salt and pepper
    cv::RNG rng(12345);
    int h = src.rows;
    int w = src.cols;
    int nums = 10000;
    for (int i = 0; i < nums; i++)
    {
        int x = rng.uniform(0, w);
        int y = rng.uniform(0, h);

        if (i % 2 == 1)
        {
            src.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 255, 255);
        }
        else
        {
            src.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0);
        }
    }

    // 高斯噪声
    cv::Mat nosie = cv::Mat::zeros(image.size(), image.type());
    cv::randn(nosie, cv::Scalar(15, 15, 15), cv::Scalar(30, 30, 30));
    cv::Mat dst;
    cv::add(image, nosie, dst);
    cv::imshow("gaussian noise", dst);

    cv::namedWindow("Input", cv::WINDOW_NORMAL);
    cv::imshow("Input", src);
    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
