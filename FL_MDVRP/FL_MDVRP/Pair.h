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
	short int i_int;
	short int j_int;
	float i_float;
	float j_float;
	
public:
	Pair(PairType type);

	Pair(PairType type, short int pairId);

	~Pair();

	PairType getType();

	void setType(PairType typeValue);

	short int get_i_IntValue();
	void set_i_IntValue(short int intValue);
	
	short int get_j_IntValue();
	void set_j_IntValue(short int intValue);
	
	float get_i_FloatValue();
	float set_i_FloatValue(float floatValue);

	float get_j_FloatValue();
	float set_j_FloatValue(float floatValue);

	// abstract methods
	void printFrogObj();

	bool isTheSame(FrogObject * fs);
};
#endif
