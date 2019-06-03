#pragma once

#ifndef TIMER_H
#define TIMER_H


class Timer {
public:
	Timer();
	Timer(float time);
	void Update(float dt);
	void Restart();
	float Get();

	void Set(float time);
		
private:
	float time;
};

#endif	//TIMER_H