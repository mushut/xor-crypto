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
	std::vector<unsigned int> tempKeys;	

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
		for (int k = 0; k < key_length; k++) {
			bit_masks[k] = (1 << (key_length - 1) - k);
		}

		int bitsInserted = 0;
		// Assign valuet to tempKeys so that the key continues throughout the vector
		for (int j = 0; j < i; j++) {
			unsigned int element = 0;

			for (int k = 0; k < 8; k++) {
				int bit = 0;

				int index = bitsInserted % key_length;
				bit = (bit_masks[index] & bitwise_key) == bit_masks[index];

				element += (bit << (7 - k));
				bitsInserted++;
			}			

			tempKeys.push_back(element);
		}
	}
	if (key_length == 8) {
		// tempKey doesn't change during encryption.
		tempKey = bitwise_key;
	}

	// Maximum is 32 bits
	if (key_length > 8) {
		// tempKey must be exactly 8 bits length, so continue bit values from bitwise_key
		int tempKeysLength = key_length;
		int i = 1;
		while (tempKeysLength % 8 != 0) {
			tempKeysLength += key_length;
			i++;
		}

		// Maybe a common function for keys != 8 bits?
		int bit_masks[key_length];
		for (int k = 0; k < key_length; k++) {
			bit_masks[k] = (1 << (key_length - 1) - k);
		}

		int bitsInserted = 0;
		for (int j = 0; j < i; j++) {
			unsigned int element = 0;

			for (int l = 0; l < 8; l++) {
				int bit = 0;

				int index = bitsInserted % key_length;
				bit = (bit_masks[index] & bitwise_key) == bit_masks[index];

				element += (bit << (7 - l));
				bitsInserted++;
			}

			tempKeys.push_back(element);
		}
		int temp = 0;
	}

	char character;
	char result;
	int index = 0;
	while (input_file.get(character)) {
		// tempKey must be changed if key_length is not exactly 8 bits long
		// for every iteration.
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

		if (key_length > 8 && key_length <= 32) {
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
