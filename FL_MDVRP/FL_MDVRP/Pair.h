#ifndef PAIR_H_   /* Include guard */
#define PAIR_H_

//=================================
// included dependencies
#include "FrogObject.h"

class FrogObjectCol;

enum class PairType{IntVsInt, IntVsFloat, FloatVsInt, FloatVsFloat};

class Pair : public FrogObject
{
	PairType pairtype;
	int i_int;
	int j_int;
	float i_float;
	float j_float;
	
public:
	Pair(PairType type);

	Pair(PairType type, int pairId);

	~Pair();

	PairType getType();

	void setType(PairType typeValue);

	int get_i_IntValue();
	void set_i_IntValue(int intValue);
	
	int get_j_IntValue();
	void set_j_IntValue(int intValue);
	
	float get_i_FloatValue();
	float set_i_FloatValue(float floatValue);

	float get_j_FloatValue();
	float set_j_FloatValue(float floatValue);

	// abstract methods
	void printFrogObj();

	bool isTheSame(FrogObject * fs);
};
#endif
