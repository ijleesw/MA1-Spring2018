#define ERR 80

#include <iostream>
#include <NTL/ZZ.h>
using namespace NTL;

class User {
private:
	ZZ n, phi_n, e, d;
	long logn;
	ZZ encrypted_msg;
	ZZ decrypted_msg;

public:
	ZZ get_e() { return e; }
	ZZ get_n() { return n; }

	User(const ZZ p, const ZZ q) {
		ZZ tmp;

		n = p*q;
		phi_n = (p-1)*(q-1);
		tmp=1; logn=0;
		while (tmp <= n) { tmp *= 10; logn++; }
		e = GenPrime_ZZ(logn/2, ERR);
		XGCD(tmp, d, tmp, e, phi_n);
	}

	~User() {}

	ZZ send_to(User* user, ZZ msg) {
		ZZ target_e, target_n;

		target_e = user->get_e();
		target_n = user->get_n();

		ZZ enc_msg;
		enc_msg = PowerMod(msg%target_n, target_e, target_n);
		user->receive(enc_msg);

		return enc_msg;
	}

	void receive(ZZ msg) {
		encrypted_msg = msg;
	}

	void decrypt() {
		decrypted_msg = PowerMod(encrypted_msg, d, n);
	}

	void announce() {
		std::cout << decrypted_msg << std::endl;
	}
};

int main()
{
	std::string alice_msg;
	std::cout << "Type Alice's message: \t";
	std::cin >> alice_msg;

	unsigned long PRIME_BITS = alice_msg.length()*2;

	User Alice(GenPrime_ZZ(PRIME_BITS, ERR), GenPrime_ZZ(PRIME_BITS, ERR));
	User Bob(GenPrime_ZZ(PRIME_BITS, ERR), GenPrime_ZZ(PRIME_BITS, ERR));

	ZZ enc = Alice.send_to(&Bob, conv<ZZ>(alice_msg.c_str()));
	std::cout << "Alice's encrypted message: \t" << enc << std::endl;

	Bob.decrypt();
	std::cout << "Bob's decrypted message: \t"; Bob.announce();

	return 0;
}
