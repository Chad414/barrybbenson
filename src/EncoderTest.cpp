/*
 * EncoderTest.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: Robo13
 */

#include <EncoderTest.h>
#include "Encoder.h"

namespace EncoderTest {

EncoderTest::EncoderTest()
: encoder(0,1)
{

}

double EncoderTest::Get(){
	return encoder.Get();
}

void EncoderTest::Set(double value){
	encoder.SetMinRate(1);
	encoder.SetDistancePerPulse(5);
}

EncoderTest::~EncoderTest() {
	// TODO Auto-generated destructor stub
}

} /* namespace EncoderTest */
