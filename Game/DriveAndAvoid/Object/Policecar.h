#pragma once
#include"DxLib.h"

#include"../Utility/Vector2D.h"

class Policecar
{
private:
	int x;
	int y;
	int image;

public:
	Policecar();
	~Policecar();

	void Initialize();        //‰Šú‰»ˆ—
	void Update();            //XVˆ—
	void Draw();              //•`‰æˆ—
	void Finalize();          //I—¹ˆ—


};

