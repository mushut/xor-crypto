/* xor-crypto
 * Aki Sipovaara 2018
 */

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

int main(void)
{
	std::string input_filename;
	std::string output_filename;
	std::string key;

	std::cout << "xor-crypto" << std::endl;
	std::cout << "Input filename:" << std::endl;
	std::cin >> input_filename;
	std::cout << "Output filename:" << std::endl;
	std::cin >> output_filename;
	
	// Key as at maximum 32-bit value
	// At this moment only use 8-bit values
	std::cout << "Key (max. 32-bit):" << std::endl;
	std::cin >> key;
	unsigned int bitwise_key = 0;
	std::string::reverse_iterator ptr;
	int key_length = 0;
	for (ptr = key.rbegin(); ptr < key.rend(); ptr++) {
		if (*ptr == '1') {
			bitwise_key |= (1 << key_length);
		}
 
		key_length++;
	}

	// Operation
	std::ifstream input_file;
	input_file.open(input_filename.c_str(), std::ifstream::in);

	std::ofstream output_file;
	output_file.open(output_filename.c_str(), std::ofstream::out | std::ofstream::app);
	
	// Write to file
	unsigned int tempKey;	// Temporary holder for 8-bit part of key
	int bit_masks[8];	// Used for creating 8-bit tempKey for encrytpion
	for (int i = 0; i < 8; i++) {
		bit_masks[i] = (1 << (7 - i));	// Mask variables start from most significant bit
	}	

	if (key_length < 8) {
		// tempKey must be exactly 8 bits length, so continue bit values from bitwise_key
		// TBD
	}
	if (key_length == 8) {
		// tempKey doesn't change during encryption.
		tempKey = bitwise_key;
	}
	if (key_length > 8) {
		// tempKey must be exactly 8 bits length, so continue bit values from bitwise_key
		// TBD
	}

	char character;
	char result;
	while (input_file.get(character)) {
		// tempKey must be changed if key_length is not exactly 8 bits long
		// for every iteration.
		result = character ^ tempKey;

		output_file.put(result);
	}

	output_file.close();

	input_file.close();

	return 0;
}
