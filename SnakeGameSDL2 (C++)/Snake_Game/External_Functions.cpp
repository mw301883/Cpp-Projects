import External_Functions;

int Check_Record_Score(const char& ch_one, const char& ch_two, const char& ch_three) {
	if (ch_two == ' ' && ch_three == ' ') {
		return ch_one - '0';
	}
	else if (ch_three == ' ') {
		return (ch_one - '0') * 10 + (ch_two - '0');
	}
	else {
		return (ch_one - '0') * 100 + (ch_two - '0') * 10 + (ch_three - '0');
	}
}