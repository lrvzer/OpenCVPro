#include <iostream>
#include <opencv2/opencv.hpp>

/**
 * 算数操作
 * "${workspaceFolder}/images/WindowsLogo.jpg"
 * "${workspaceFolder}/images/LinuxLogo.jpg"
 *
 * 输入图片的大小与类型需要一致
 * 处理越界
 *
 * 图片亮度调整
 *     黑色 （0, 0, 0）
 *     白色 （255, 255, 255）
 * 对于RGB图像来说，亮度越大值越高
 *
 * 应用
 *     对比度
 *     透明度
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
    if (srcWin.empty() || srcLinux.empty())
    {
        std::cout << "picture could not find." << std::endl;
        return -1;
    }
    cv::Mat dstAdd;
    cv::add(srcWin, srcLinux, dstAdd);
    cv::imshow("dst-add", dstAdd);

    cv::Mat dstSub;
    cv::subtract(srcWin, srcLinux, dstSub);
    cv::imshow("dst-subtract", dstSub);

    cv::Mat dstMul;
    cv::multiply(srcWin, srcLinux, dstMul);
    cv::imshow("dst-multiply", dstMul);

    cv::Mat dstDiv;
    cv::divide(srcWin, srcLinux, dstDiv);
    cv::imshow("dst-divide", dstDiv);

    cv::Mat dstAddWeight;
    // dst = src1 * alpha + src2 * beta + gamma;
    cv::addWeighted(srcWin, 1.2, srcLinux, 0.5, 0.0, dstAddWeight);
    cv::imshow("dst-addWeighted", dstAddWeight);

    cv::imshow("Input1", srcWin);
    cv::imshow("Input2", srcLinux);
    cv::waitKey(0);          // 阻塞
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}
