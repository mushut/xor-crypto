/* xor-crypto
 * Aki Sipovaara 2018
 */

#include <iostream>
#include <string>
#include <fstream>

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
	unsigned int bitwise_key;

	// Operation
	std::ifstream input_file;
	input_file.open(input_filename);

	std::ofstream output_file;
	output_file.open(output_filename);
	// Write to file
	output_file.close();

	input_file.close();

	return 0;
}
