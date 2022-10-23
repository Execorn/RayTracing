#include "DataTypes.h"

int testvector() {
    DataTypes::TArray_<int, 10> test_array(5);
    for (size_t i = 0; i < test_array.size(); ++i) {
        test_array[i] = i;
        fprintf(stderr, "Got %i\n", test_array[i]);
    }    

    std::cout << test_array << std::endl;

    DataTypes::TVector_<int> test_vector(0);

    test_vector.push_back(1);
    test_vector.push_back(2);
    test_vector.push_back(3);
    test_vector.push_back(4);
    test_vector.push_back(5);

    test_vector.change_size(10);

    test_vector.push_back(6);
    test_vector.push_back(7);

    std::cout << test_vector << std::endl;

    return 0;
}