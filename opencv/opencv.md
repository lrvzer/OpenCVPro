[opencv_read_write](opencv_read_write.cpp)

API:

- cv::imread
- cv::imwrite
- cv::namedWindow
- cv::imshow
- cv::waitKey
- cv::destroyAllWindows

---

认识OpenCV中Mat对象

[opencv_mat](opencv_mat.cpp)

API:

- cv::Mat
  - cols
  - rows
  - channels
  - depth
  - type
  - empty

---

Mat对象的创建和使用

[opencv_mat_create_use](opencv_mat_create_use.cpp)

API:

- cv::Mat
  - cv::Mat::zeros
  - clone
  - copyTo
  - size()
- cv::Scalar


---

像素操作: 遍历和访问

[opencv_pixel_accessing](opencv_pixel_accessing.cpp)

API:

- cv::Mat 
  - at&lt;T&gt;(row, col)
  - ptr&lt;T&gt;(row)

---

图像算数操作

[opencv_arithmetic](opencv_arithmetic.cpp)

- cv::add
- cv::subtract
- cv::multiply
- cv::divide
- cv::addWeighted

---

图像位操作

[opencv_bit](opencv_bit.cpp)

API:

- cv::bitwise_not
- cv::bitwise_and
- cv::bitwise_or

---

像素信息统计

[opencv_pixel_info](opencv_pixel_info.cpp)

- cv::mean
- cv::meanStdDev
---

图形绘制与填充

[opencv_draw](opencv_draw.cpp)

API:

- cv::line
- cv::rectangle
- cv::circle
- cv::ellipse
- cv::putText
- cv::RNG
  - uniform
---

图像通道合并与分离

[opencv_channel_split_merge](opencv_channel_split_merge.cpp)

API:

- cv::split
- cv::merge

---

图像直方图统计

[opencv_hist](opencv_hist.cpp)

- cv::calcHist
- cv::normalize

图像直方图均衡化

[opencv_hist_equalize](opencv_hist_equalize.cpp)

- cv::cvtColor
- cv::equalizeHist

图像直方图比较

[opencv_hist_compare](opencv_hist_compare.cpp)

- cv::compareHist

---

图像查找表与颜色表

[opencv_lut](opencv_lut.cpp)

- cv::LUT
- cv::applyColorMap

---

图像卷积
卷积边缘处理

[opencv_convolution](opencv_filter_convolution.cpp)

- cv::blur
- cv::copyMakeBorder

图像模糊

高斯模糊
盒子模糊

[opencv_blur](opencv_filter_blur.cpp)

- cv::GaussianBlur
- cv::boxFilter

自定义滤波器

输出图像类型

- 针对不同卷积核系数，图像输出类型数值范围
- CV_32F/CV_32S
- 类型转换与现实支持

[opencv_filter_custom](opencv_filter_custom.cpp)

梯度

[opencv_filter_grad](opencv_filter_grad.cpp)

锐化

[opencv_filter_sharpen](opencv_filter_sharpen.cpp)

噪声

类型

- 椒盐噪声
- 高斯噪声
- 其他噪声

[opencv_noise](opencv_noise.cpp)

去噪

- 均值滤波
- 高斯滤波

[opencv_noise_denoise](opencv_nosie_denoise.cpp)

EPF滤波概述

- 均值和高斯滤波的缺点
  - 均值滤波没有考虑中心像素点对整个输出像素的贡献，实际上，锚定的那个点贡献才是最大的，相应的权重值最高。并没有提高图像的质量
  - 高斯滤波考虑了中心像素点对整个输出像素的贡献，权重值最高，但是，当中心像素点与其他周围的像素点的差值很大的时候，需要考虑率像素之间可能是边缘或者是一个梯度的值，降低中心像素点的权重，保持像素之间的差异
- 边缘保留滤波算法
  - 高斯双边
  - 均值迁移
  - 非局部均值去噪
  - 局部均方差

边缘提取

[opencv_canny](opencv_canny.cpp)

---

二值图像

- 灰度图像 单通道，取值范围0-255
- 二值图像 单通道，取值0（黑色）与255（白色）

[opencv_binary](opencv_threshold_binary.cpp)

全局阈值

- 均值法
- OTSU

自适应阈值