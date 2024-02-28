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

    cv::Mat canvas = cv::Mat::zeros(cv::Size(512, 512), CV_8UC3);

    cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);

    // 相关绘制API演示
    cv::line(canvas, cv::Point(10, 10), cv::Point(400, 400), cv::Scalar(0, 0, 255), 1, cv::LINE_8);

    cv::Rect rect(100, 100, 200, 200);
    cv::rectangle(canvas, rect, cv::Scalar(255, 0, 0), 1, 8);                  // 方形
    cv::circle(canvas, cv::Point(256, 256), 100, cv::Scalar(0, 255, 0), 1, 8); // 圆形

    cv::RotatedRect rrt;
    rrt.center = cv::Point(256, 256);
    rrt.angle = 45;
    rrt.size = cv::Size(100, 200);
    cv::ellipse(canvas, rrt, cv::Scalar(255, 255, 0), -1, 8); // 椭圆形

    // 绘制文字
    cv::putText(canvas, "hello, opencv", cv::Point(100, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2, 8);
    cv::imshow("Input", canvas);

    cv::Mat image = cv::Mat::zeros(cv::Size(512, 512), CV_8UC3);
    int x1 = 0, y1 = 0;
    int x2 = 0, y2 = 0;
    cv::RNG rng(12345);
    while (true)
    {
        x1 = (int)rng.uniform(0, 512);
        y1 = (int)rng.uniform(0, 512);
        x2 = (int)rng.uniform(0, 512);
        y2 = (int)rng.uniform(0, 512);

        int w = abs(x2 - x1);
        int h = abs(y2 - y1);

        rect.x = x1;
        rect.y = y2;
        rect.width = w;
        rect.height = h;
        image = cv::Scalar(0, 0, 0);
        cv::rectangle(image, rect, cv::Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256)), 1, 8); // 方形

        // cv::line(image, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256)), 1, cv::LINE_8);
        cv::imshow("image", image);
        char c = cv::waitKey(10);
        if (c == 27) // ESC
            break;
    }

    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
