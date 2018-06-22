#ifndef FROGOBJECT_H_   /* Include guard */
#define FROGOBJECT_H_

class FrogObject
{
private:
	float value;

public:

	FrogObject();

	float getValue();

	void setValue(float valueV);

	virtual void printFrogObj() = 0;

	virtual bool isTheSame(FrogObject * fs) = 0;
};

#endif