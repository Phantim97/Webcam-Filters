#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <functional>

cv::Mat inline no_filter(cv::Mat f)
{
	return f;
}

cv::Mat sobel_filter(cv::Mat f)
{
	cv::Mat res;
	GaussianBlur(f, f, cv::Size(3, 3), 1, 1);
	cv::Mat grad_x, grad_y;
	cv::cvtColor(f, f, cv::COLOR_BGR2GRAY);
	cv::Sobel(f, grad_x, CV_16S, 1, 0);
	cv::Sobel(f, grad_y, CV_16S, 0, 1);
	cv::convertScaleAbs(grad_x, grad_x);
	cv::convertScaleAbs(grad_y, grad_y);

	cv::addWeighted(grad_x, 0.5, grad_y, 0.5, 0, res);

	return res;
}

cv::Mat cartoon_filter(cv::Mat f)
{
	cv::Mat res;
	cv::Mat mask;

	//Reduce Noise
	cv::GaussianBlur(f, f, cv::Size(3, 3), 1, 1);//Removing Noise From Image
	cv::cvtColor(f, mask, cv::COLOR_BGR2GRAY);

	//Edge Detection
	cv::Laplacian(mask, mask, CV_8U, 5);
	cv::threshold(mask, mask, 75, 255, cv::THRESH_BINARY_INV);

	//Place Laplacian onto base image
	f.copyTo(res, mask);
	return res;
}

cv::Mat pencil_filter(cv::Mat f)
{
	cv::Mat res;
	GaussianBlur(f, res, cv::Size(3, 3), 1, 1);
	cv::cvtColor(res, res, cv::COLOR_BGR2GRAY);
	cv::Laplacian(res, res, CV_8U, 5);
	cv::threshold(res, res, 75, 255, cv::THRESH_BINARY_INV);
	return res;
}

cv::Mat hsv_filter(cv::Mat f)
{
	cv::cvtColor(f, f, cv::COLOR_BGR2HSV);
	return f;
}

cv::Mat red_filter(cv::Mat f)
{
	cv::Mat channels[3];
	cv::split(f, channels);
	channels[0] *= 0;
	channels[1] *= 0;
	cv::merge(channels,3, f);
	return f;
}

cv::Mat green_filter(cv::Mat f)
{
	cv::Mat channels[3];
	cv::split(f, channels);
	channels[0] *= 0;
	channels[2] *= 0;
	cv::merge(channels, 3, f);
	return f;
}

cv::Mat blue_filter(cv::Mat f)
{
	cv::Mat channels[3];
	cv::split(f, channels);
	channels[1] *= 0;
	channels[2] *= 0;
	cv::merge(channels, 3, f);
	return f;
}

cv::Mat grayscale_filter(cv::Mat f)
{
	cv::cvtColor(f, f, cv::COLOR_BGR2GRAY);
	return f;
}

cv::Mat negative_filter(cv::Mat f)
{
	cv::Mat channels[3];
	cv::split(f, channels);
	channels[0] = 255 - channels[0];
	channels[1] = 255 - channels[1];
	channels[2] = 255 - channels[2];
	cv::merge(channels, 3, f);
	return f;
}

enum Filters
{
	NONE,
	SOBEL,
	CARTOON,
	PENCIL,
	HSV,
	RED,
	BLUE,
	GREEN,
	BW,
	NEGATIVE,
	COUNT
};

static int filter_value = 0;

int main()
{
	cv::namedWindow("WebcamFilters", cv::WINDOW_FREERATIO);
	cv::createTrackbar("Filters", "WebcamFilters", &filter_value, COUNT-1);

	cv::VideoCapture cap(0);
	cv::Mat frame;

	std::function<cv::Mat(cv::Mat f)> filters[COUNT] = { no_filter, sobel_filter, cartoon_filter, pencil_filter, hsv_filter, red_filter, blue_filter, green_filter, grayscale_filter, negative_filter };

	int k = 0;
	while (k != 27)
	{
		cap >> frame;

		frame = filters[filter_value](frame);

		cv::imshow("WebcamFilters", frame);
		k = cv::waitKey(20) & 0xFF;
	}

	return 0;
}