#ifndef UTILITIES_H
#define UTILITIES_H

float CheckBounds(float LowerBound, float UpperBound, float Input) {
	if(Input < LowerBound){
		return LowerBound;
	}
	else if(Input > UpperBound){
		return UpperBound;
	}
	else{
		return Input;
	}
}

#endif
