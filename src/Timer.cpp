#include "Timer.h"

Timer::Timer() {
	time = 0;
}

// todo - ver melhor isso
Timer::Timer(float time) {
	this->time = time;
}

void Timer::Update(float dt) {
	time += dt;
}

void Timer::Restart() {
	time = 0;
}

float Timer::Get() {
	return time;
}

// todo - ver melhor isso
void Timer::Set(float time) {
	this->time = time;
}

