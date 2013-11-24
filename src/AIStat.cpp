#include "AIStat.h"


AIStat::AIStat()
{
	//
}

AIStat::AIStat(float scout, float assault, float defend, float capture, int front_rank, int priority)
{
	set_scout(scout);
	set_assault(assault);
	set_defend(defend);
	set_capture(capture);
	set_front_rank(front_rank);
	set_priority(priority);	
}

// --- METHODES ---

// --- GET ---

float AIStat::get_scout()
{
	return _scout;
}

float AIStat::get_assault()
{
	return _assault;
}

float AIStat::get_defend()
{
	return _defend;
}

float AIStat::get_capture()
{
	return _capture;
}

int AIStat::get_front_rank()
{
	return _front_rank;
}

int AIStat::get_priority()
{
	return _priority;
}


// --- SET ---

void AIStat::set_scout(float scout)
{
	_scout = scout;
}

void AIStat::set_assault(float assault)
{
	_assault = assault;
}

void AIStat::set_defend(float defend)
{
	_defend = defend;
}

void AIStat::set_capture(float capture)
{
	_capture = capture;
}

void AIStat::set_front_rank(int front_rank)
{
	_front_rank = front_rank;
}

void AIStat::set_priority(int priority)
{
	_priority = priority;
}
