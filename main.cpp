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
	std::cout << "Key (max. 32-bit):" << std::endl;
	std::cin >> key;
	unsigned int bitwise_key = 0;
	std::string::reverse_iterator ptr;
	int counter = 0;
	for (ptr = key.rbegin(); ptr < key.rend(); ptr++) {
		if (*ptr == "1") {
			bitwise_key |= (1 << counter);
		}
 
		counter++;
	}

	// Operation
	std::ifstream input_file;
	input_file.open(input_filename);

	std::ofstream output_file;
	output_file.open(output_filename);
	
	// Write to file
	unsigned int tempKey	// Temporary holder for 8 bit part of key
	char character;
	char result;
	while (input_file.get(character)) {
		result = character ^ tempKey;

		output_file.put(result);
	}

	output_file.close();

	input_file.close();

	return 0;
}
