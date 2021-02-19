#pragma once
class Coins
{
public:
	static Coins& GetInstance(void)
	{

		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new Coins();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	int coins = 10;
	int kinken = 0;
private:
	static Coins* sInstance;
	Coins();
	~Coins();
};

