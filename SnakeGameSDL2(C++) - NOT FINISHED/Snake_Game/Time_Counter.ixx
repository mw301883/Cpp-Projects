export module Time_Counter;
import <string>;

export class Time_Counter {
private:
	std::string Time;
	int64_t Prev_Time;
	int Minutes;
	int Seconds;
	void Set_Time();
public:
	Time_Counter();
	void Add_Min();
	void Add_Sec();
	std::string Return_Time();
	void Reset();
	void Count();
	void Set_Prev_Time(const int& Prev_Time);
};