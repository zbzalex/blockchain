#ifndef TEST_H
#define TEST_H

//
// test function
//
#define TEST(fn) \
	if (fn()) std::cout << "[TEST SUCCESS] " << #fn << "\n"; \
	else 	  std::cout << "[TEST FAILED ] " << #fn << "\n"; \

#endif // TEST_H