
class Item
{
private:
	int coneimage;
	int rand;

public:
	Item();
	~Item();
	void Update();
	void Draw()const;

	struct CONE
	{
		int x, y;
		int w, h;
		int image;
		int flg;
	};
	struct CONE cone[3];
};
