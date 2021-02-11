class Rack
{
	public:
	int weight[4] = { 5, 3, 2, 1 }, remainder = 0;
    //Functions for weights
	int fiveKG(int w, int r);
	int threeKG(int w, int r);
	int twoKG(int w, int r);
	int oneKG(int w, int r);
};


int Rack::fiveKG(int w, int r) {

	if (w * weight[0] > r) {
		return fiveKG(w - 1, r);
	}
	else return w;
}

int Rack::threeKG(int x, int r) {;
	if ((x * weight[1]) > r) {
		return threeKG(x - 1, r);
	}
	else return x;
}

int Rack::twoKG(int y, int r) {
	if ((y * weight[2]) > r) {
		return twoKG(y - 1, r);
	}
	else return y;
}

int Rack::oneKG(int z, int r) {
	if ((z * weight[3]) > r) {
		return oneKG(z - 1, r);
	}
	else return z;
}





