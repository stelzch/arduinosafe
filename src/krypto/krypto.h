class Krypto {
public:
	virtual Krypto(string key) = 0;
	virtual string encrypt(string text) = 0;
	virtual string decrypt(string text) = 0;
};