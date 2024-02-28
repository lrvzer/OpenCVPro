#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

/**
 * "${workspaceFolder}/images/WindowsLogo.jpg"
 * "${workspaceFolder}/images/LinuxLogo.jpg"
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char const* argv[])
{
    std::string logo_win;
    std::string logo_linux;
    if (argc < 3)
    {
        std::cout << "please input image path!" << std::endl;
        return -1;
    }
    logo_win = argv[1];
    logo_linux = argv[2];
    cv::Mat srcWin = cv::imread(logo_win, cv::IMREAD_COLOR);     // 读取一张图像
    cv::Mat srcLinux = cv::imread(logo_linux, cv::IMREAD_COLOR); // 读取一张图像

    cv::Mat hist1, hist2;
    int channels[] = { 0, 1, 2 };
    int hintSize[] = { 256, 256, 256 };
    float range1[] = { 0, 255 };
    float range2[] = { 0, 255 };
    float range3[] = { 0, 255 };
    const float* hintRanges[] = { range1, range2, range3 };

    cv::calcHist(&srcWin, 1, channels, cv::Mat(), hist1, 3, hintSize, hintRanges, true, false);
    cv::calcHist(&srcLinux, 1, channels, cv::Mat(), hist2, 3, hintSize, hintRanges, true, false);

    // 归一化
    cv::normalize(hist1, hist1, 0, 1.0, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(hist2, hist2, 0, 1.0, cv::NORM_MINMAX, -1, cv::Mat());

    // 比较
    // 巴氏距离
    double b12 = cv::compareHist(hist1, hist2, cv::HISTCMP_BHATTACHARYYA);
    double b11 = cv::compareHist(hist1, hist1, cv::HISTCMP_BHATTACHARYYA);
    printf("b12: %.2f, b11: %.2f\n", b12, b11);

    // 相关性
    double c12 = cv::compareHist(hist1, hist2, cv::HISTCMP_CORREL);
    double c11 = cv::compareHist(hist1, hist1, cv::HISTCMP_CORREL);
    printf("c12: %.2f, c11: %.2f\n", c12, c11);
    return 0;
}