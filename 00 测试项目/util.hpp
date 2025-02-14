#include <iostream>
#include <chrono>
#include <queue>

class RangeCodeTime
{
	std::queue<double> _times;
	double _time = 0;
	double _average = 0;
	double _d = 0;
	double _sum = 0;
	int _maxAvgCount = 60;
public:
	double GetTime()
	{
		return _time;
	}
	double GetAverage()
	{
		return _average;
	}
	void Begin()
	{
		_d = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() / 1e+9;
	}
	void End(const std::string& printLabel = "", bool isPrint = true)
	{
		_time = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() / 1e+9 - _d;
		_times.push(_time);
		_sum += _time;
		_average = _sum / _times.size();
		if (_times.size() >= _maxAvgCount)
		{
			_sum -= _times.front();
			_times.pop();
		}
		if (isPrint)
		{
			printf("%sºÄÊ±(s):%lf\n", printLabel.c_str(), _time);
		}
	}
};
