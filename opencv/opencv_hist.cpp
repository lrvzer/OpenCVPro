#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

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
    std::vector<cv::Mat> mv;
    cv::split(src, mv);

    cv::Mat b_hist, g_hist, r_hist;
    int hintSize = 256;
    float range[] = { 0, 255 };
    const float* hintRanges = { range };
    cv::calcHist(&mv[0], 1, 0, cv::Mat(), b_hist, 1, &hintSize, &hintRanges, true, false);
    cv::calcHist(&mv[1], 1, 0, cv::Mat(), g_hist, 1, &hintSize, &hintRanges, true, false);
    cv::calcHist(&mv[2], 1, 0, cv::Mat(), r_hist, 1, &hintSize, &hintRanges, true, false);

    cv::Mat result = cv::Mat::zeros(cv::Size(600, 400), CV_8UC3);
    int margin = 50;
    int mn = result.rows - 2 * margin; // 竖直区间画图 y方向 画图区间[50, 350]
    cv::normalize(b_hist, b_hist, 0, mn, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(g_hist, g_hist, 0, mn, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(r_hist, r_hist, 0, mn, cv::NORM_MINMAX, -1, cv::Mat());

    float w_step = (float)(result.cols - 2 * margin) / 256; // 256个数据，画图区间在[50, 550]内，左右留白各50，即水平区间x方向

    for (int i = 0; i < 255; i++)
    {
        // + margin 保证留白内容
        cv::line(result, cv::Point(w_step * i + margin, margin + (mn - b_hist.at<float>(i, 0))), cv::Point(w_step * (i + 1) + margin, margin + (mn - b_hist.at<float>(i + 1, 0))), cv::Scalar(255, 0, 0), 2, 8);
        cv::line(result, cv::Point(w_step * i + margin, margin + (mn - g_hist.at<float>(i, 0))), cv::Point(w_step * (i + 1) + margin, margin + (mn - g_hist.at<float>(i + 1, 0))), cv::Scalar(0, 255, 0), 2, 8);
        cv::line(result, cv::Point(w_step * i + margin, margin + (mn - r_hist.at<float>(i, 0))), cv::Point(w_step * (i + 1) + margin, margin + (mn - r_hist.at<float>(i + 1, 0))), cv::Scalar(0, 0, 255), 2, 8);
    }

    cv::imshow("result", result);

    cv::namedWindow("Input", cv::WINDOW_NORMAL);
    cv::imshow("Input", src);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
