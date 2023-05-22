import Time_Counter;
import <string>;
import "SDL.h";

Time_Counter::Time_Counter() : Time("00 : 00"), Prev_Time(0), Minutes(0), Seconds(0) {}

void Time_Counter::Set_Time() {
	if (this->Minutes < 10) {
		this->Time = "0" + std::to_string(this->Minutes) + " : ";
	}
	else {
		this->Time = std::to_string(this->Minutes) + " : ";
	}
	if (this->Seconds < 10) {
		this->Time += ("0" + std::to_string(this->Seconds));
	}
	else {
		this->Time += std::to_string(this->Seconds);
	}
}

void Time_Counter::Add_Min() {
	if (this->Minutes < 59) {
		++this->Minutes;
	}
	else {
		this->Minutes = 0;
	}
	Set_Time();
}

void Time_Counter::Add_Sec() {
	if (this->Seconds < 59) {
		++this->Seconds;
	}
	else {
		this->Seconds = 0;
		Add_Min();
		return;
	}
	Set_Time();
}

std::string Time_Counter::Return_Time() {
	return this->Time;
}

void Time_Counter::Reset() {
	this->Time = "00 : 00";
	this->Seconds = 0;
	this->Minutes = 0;
	this->Prev_Time = 0;
}

void Time_Counter::Count() {
	int64_t Current_Time = (SDL_GetTicks64() - this->Prev_Time)/100;
	if (Current_Time % 10 == 0) {
		Add_Sec();
		SDL_Delay(20);
	}
}

void Time_Counter::Set_Prev_Time(const int& Prev_Time) {
	this->Prev_Time = Prev_Time;
}