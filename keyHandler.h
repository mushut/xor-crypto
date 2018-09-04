/* xor-crypto
 * Aki Sipovaara 2018
 */

#include <string>
#include <vector>

// Class to handle xor cipher key
class HandleKey 
{
public:
	HandleKey(void);
	HandleKey(std::string key);
	int createKeyBinary(void);
	std::vector<unsigned int> getKeyBinary(void);
private:
	std::string keyString;
	std::vector<unsigned int> keyBinary;
};
