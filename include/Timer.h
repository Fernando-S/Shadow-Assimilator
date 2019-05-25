#pragma once

#ifndef TIMER_H
#define TIMER_H


class Timer {
public:
	Timer();
	// todo - ver melhor isso
	Timer(float time);
	void Update(float dt);
	void Restart();
	float Get();

	// todo - ver melhor isso
	void Set(float time);
		
private:
	float time;
};

#endif	//TIMER_H