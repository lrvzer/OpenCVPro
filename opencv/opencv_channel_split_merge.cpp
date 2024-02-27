#include <iostream>
#include <opencv2/opencv.hpp>

/**
 * 图像的加载和保存
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
    cv::Mat src = cv::imread(filename, cv::IMREAD_ANYCOLOR); // 读取一张图像
    if (src.empty())
    {
        std::cout << "picture could not find." << std::endl;
        return -1;
    }

    std::vector<cv::Mat> mv;
    cv::split(src, mv); // 分离

    printf("size: %ld\n", mv.size());

    cv::imshow("B", mv[0]);
    cv::imshow("G", mv[1]);
    cv::imshow("R", mv[2]);

    cv::Mat dst;
    // mv[2] = cv::Scalar(0, 0, 0);
    cv::merge(mv, dst); // 合并
    cv::imshow("dst", dst);

    // ROI
    cv::Rect roi;
    roi.x = 100;
    roi.y = 100;
    roi.width = 250;
    roi.height = 250;

    cv::Mat sub = src(roi).clone(); // clone() 深拷贝
    cv::bitwise_not(sub, sub);
    cv::imshow("roi", sub);

    cv::rectangle(src, roi, cv::Scalar(0, 255, 255), 1, 8);

    cv::namedWindow("Input", cv::WINDOW_NORMAL);
    cv::imshow("Input", src);
    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
