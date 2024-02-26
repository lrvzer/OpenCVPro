#include <iostream>
#include <opencv2/opencv.hpp>

/**
 * 认识opencv mat对象
 *
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
    int width = src.cols;
    int height = src.rows;
    int dim = src.channels();
    int depth = src.depth();
    int type = src.type();
    if (type == CV_8UC3)
    {
        printf("width: %d, height: %d, dim: %d, depth: %d, type: %d\n", width, height, dim, depth, type);
    }
    cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
    cv::imshow("Input", src);
    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}

/*
+----+-----+
|  Header  |
+----+-----+
|   Data   |
+----+-----+
*/