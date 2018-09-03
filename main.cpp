/* xor-crypto
 * Aki Sipovaara 2018
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>

// Start using classes and functions
int main(int argc, char** argv)
{
	std::string input_filename;
	std::string output_filename;
	std::string key;

	std::cout << "xor-crypto" << std::endl;

	// argc and argv should be checked.
	if (argc == 1) {
		std::cout << "Input filename:" << std::endl;
		std::cin >> input_filename;
		std::cout << "Output filename:" << std::endl;
		std::cin >> output_filename;
		
		// Keys equal or shorter than 8 bits should work
		std::cout << "Key (max. 32-bit):" << std::endl;
		std::cin >> key;
	}
	else {
		input_filename = std::string(*(argv + 1));
		output_filename = std::string(*(argv + 2));
		std::string temp(*(argv + 3));
		std::stringstream str(temp);
		str >> key;
	}
	
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
	//int bit_masks[8];	// Used for creating 8-bit tempKey for encryption
	std::vector<unsigned int> tempKeys;	

	//for (int i = 0; i < 8; i++) {
	//	bit_masks[i] = (1 << (7 - i));	// Mask variables start from most significant bit
	//}	

	if (key_length < 8) {
		// tempKey must be exactly 8 bits length, so continue bit values from bitwise_key
		// Naming is bit unclear. 
		int tempKeysLength = key_length;
		int i = 1;
		while (tempKeysLength % 8 != 0) {
			tempKeysLength += key_length;
			i++;
		}

		// Generate bit_masks
		int bit_masks[key_length];
		for (int i = 0; i < key_length; i++) {
			bit_masks[i] = (1 << (key_length - 1) - i);
		}

		int bitsInserted = 0;
		// Assign valuet to tempKeys so that the key continues throughout the vector
		// Does not work.
		for (int j = 0; j < i; j++) {
			unsigned int element = 0;

			for (int k = 0; k < 8; k++) {
				int bit = 0;

				int index = bitsInserted % key_length;
				bit = (bit_masks[index] & bitwise_key) == bit_masks[index];

				element = (bit << (7 - k));
				bitsInserted++;
			}			

			tempKeys.push_back(element);
		}
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
	int index = 0;
	while (input_file.get(character)) {
		// tempKey must be changed if key_length is not exactly 8 bits long
		// for every iteration.
		// TBD
		if (key_length == 8) {
			result = character ^ tempKey;
		}
		
		if (key_length > 0 && key_length < 8) {
			result = character ^ tempKeys[index];
			index++;

			if (index >= tempKeys.size()) {
				index = 0;
			}
		}

		output_file.put(result);
	}

	output_file.close();

	input_file.close();

	return 0;
}
