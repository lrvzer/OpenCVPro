#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

cv::Mat src;
int t1 = 50;
cv::RNG rng(12345);

void ccl_stats_demo(cv::Mat& image);

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

    cv::GaussianBlur(src, src, cv::Size(3, 3), 0);
    cv::Mat gray, binary;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::imshow("binary", binary);

    ccl_stats_demo(binary);

    // cv::Mat labels = cv::Mat::zeros(src.size(), CV_32S);
    // int num_labels = cv::connectedComponents(binary, labels, 8, CV_32S, cv::CCL_DEFAULT);
    // printf("total labels: %d\n", (num_labels - 1));

    // std::vector<cv::Vec3b> colorTable(num_labels);
    // colorTable[0] = cv::Vec3b(0, 0, 0);
    // for (int i = 0; i < num_labels; i++)
    // {
    //     colorTable[i] = cv::Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
    // }
    // cv::Mat result = cv::Mat::zeros(src.size(), src.type());
    // int w = result.cols;
    // int h = result.rows;

    // for (int row = 0; row < h; row++)
    // {
    //     for (int col = 0; col < w; col++)
    //     {
    //         int label = labels.at<int>(row, col);
    //         result.at<cv::Vec3b>(row, col) = colorTable[label];
    //     }
    // }

    // cv::putText(result, cv::format("number: %d", num_labels - 1), cv::Point(50, 50), cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(255, 255, 0), 1);
    // cv::imshow("CCL", result);

    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}

void ccl_stats_demo(cv::Mat& image)
{
    cv::Mat labels = cv::Mat::zeros(src.size(), CV_32S);
    cv::Mat stats, centroids;
    int num_labels = cv::connectedComponentsWithStats(image, labels, stats, centroids, 8, CV_32S, cv::CCL_DEFAULT);
    std::vector<cv::Vec3b> colorTable(num_labels);
    colorTable[0] = cv::Vec3b(0, 0, 0);
    for (int i = 0; i < num_labels; i++)
    {
        colorTable[i] = cv::Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
    }
    cv::Mat result = cv::Mat::zeros(src.size(), CV_8UC3);
    int w = result.cols;
    int h = result.rows;

    for (int row = 0; row < h; row++)
    {
        for (int col = 0; col < w; col++)
        {
            int label = labels.at<int>(row, col);
            result.at<cv::Vec3b>(row, col) = colorTable[label];
        }
    }
    for (int i = 1; i < num_labels; i++)
    {
        // center
        int cx = centroids.at<double>(i, 0);
        int cy = centroids.at<double>(i, 1);

        // rectangle and area
        int x = stats.at<int>(i, cv::CC_STAT_LEFT);
        int y = stats.at<int>(i, cv::CC_STAT_TOP);
        int width = stats.at<int>(i, cv::CC_STAT_WIDTH);
        int height = stats.at<int>(i, cv::CC_STAT_HEIGHT);
        int area = stats.at<int>(i, cv::CC_STAT_AREA);

        cv::circle(result, cv::Point(cx, cy), 3, cv::Scalar(0, 0, 255), 2, 8, 0);

        cv::Rect box(x, y, width, height);
        cv::rectangle(result, box, cv::Scalar(0, 255, 0), 2, 8);
        cv::putText(result, cv::format("%d", area), cv::Point(x, y), cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0, 255, 255), 1);
    }

    cv::imshow("CCL-demo", result);
}