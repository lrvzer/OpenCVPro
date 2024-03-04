#include <iostream>
#include <opencv2/opencv.hpp>

void add_salt_and_pepper_noise(cv::Mat& image);
void add_gaussian_noise(cv::Mat& image);

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

    cv::imshow("src", src);
    cv::Mat image = src.clone();

    // add_salt_and_pepper_noise(image);
    add_gaussian_noise(image);

    // 中值滤波
    cv::Mat m_dst;
    cv::medianBlur(image, m_dst, 5);
    cv::imshow("medianBlur_dst", m_dst);

    // 高斯滤波
    cv::Mat g_dst;
    cv::GaussianBlur(image, g_dst, cv::Size(5, 5), 0);
    cv::imshow("gaussianBlur_dst", g_dst);

    // 高斯双边
    cv::Mat b_dst;
    cv::bilateralFilter(src, b_dst, 0, 100, 10);
    cv::imshow("bilateralFilter_dst", b_dst);

    cv::Mat f_dst1, f_dst2, gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    // cv::fastNlMeansDenoisingColored(src, f_dst1, 3., 3., 7, 21);
    cv::fastNlMeansDenoising(gray, f_dst2, 15, 10, 30);
    // cv::imshow("fastNlMeansDenoisingColored_dst", f_dst1);
    cv::imshow("fastNlMeansDenoising", f_dst2);

    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}

// salt and pepper
void add_salt_and_pepper_noise(cv::Mat& image)
{
    cv::RNG rng(12345);
    int h = image.rows;
    int w = image.cols;
    int nums = 10000;
    for (int i = 0; i < nums; i++)
    {
        int x = rng.uniform(0, w);
        int y = rng.uniform(0, h);

        if (i % 2 == 1)
        {
            image.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 255, 255);
        }
        else
        {
            image.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0);
        }
    }

    cv::imshow("salt_noise", image);
}

// 高斯噪声
void add_gaussian_noise(cv::Mat& image)
{
    cv::Mat nosie = cv::Mat::zeros(image.size(), image.type());
    cv::randn(nosie, cv::Scalar(15, 15, 15), cv::Scalar(30, 30, 30));
    cv::Mat dst;
    cv::add(image, nosie, dst);
    cv::imshow("gaussian_noise", dst);
    dst.copyTo(image);
}