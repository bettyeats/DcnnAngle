#include "AngleTest.hpp"

void DetectAngle(const cv::Mat& image, std::vector<float> &angle) {
    mDispatcher.DetectWithoutAlignment(image, angle);
}
