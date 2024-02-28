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