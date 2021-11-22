#pragma once
typedef uint8_t Uint8;

class Colour
{
public:
	Uint8 R;
	Uint8 G;
	Uint8 B;
	Uint8 A;

	Colour()
	{
		R = 255;
		G = 255;
		B = 255;
		A = 255;
	}

	Colour(Uint8 R, Uint8 G, Uint8 B, Uint8 A)
	{
		this->R = R;
		this->G = G;
		this->B = B;
		this->A = A;
	}
};

