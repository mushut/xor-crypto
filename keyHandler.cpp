/* xor-crypto
 * Aki Sipovaara
 */

#include "keyHandler.h"

// Function for createKeyBinary - string to int
unsigned int keyStringToBinary(std::string key)
{
	unsigned int bitwise_key = 0;
	std::string::reverse_iterator ptr;
	int key_length = 0;
	for (ptr = key.rbegin(); ptr != key.rend(); ++ptr) {
		if (*ptr == '1') {
			bitwise_key |= (1 << key_length);
		}

		key_length++;
	}

	return bitwise_key;
}

// Function for createKeyBinary int to vector (8-bit sized elements)
std::vector<unsigned int> bitwiseKeyToVector(unsigned int bitwise_key, int key_length)
{
	std::vector<unsigned int> results;
	if (key_length == 8) {
		results.push_back(bitwise_key);
	}

	else {
		// Create masks (needs function)

		// Check bit by bit
	}

	return results;
}

HandleKey::HandleKey(void)
{
}

HandleKey::HandleKey(std::string key)
{
	keyString = key;
}

int HandleKey::createKeyBinary(void)
{
	unsigned int bitwise_key = 0;

	if (!keyString.empty) {
		bitwise_key = keyStringToBinary(keyString);
		if (bitwise_key <= 0x100) {
			keyBinary = bitwiseKeyToVector(bitwise_key, keyString.size());
			return 0;
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

std::vector<unsigned int> HandleKey::getKeyBinary(void)
{
}
