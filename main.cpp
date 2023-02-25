#include <fstream>
#include <iostream>
#include "CSVReader.h"
#include "testSheet.h"

int main(int argc, char* argv[]) {
	try {
		std::string path = argv[1];
		CSVReader reader(path);
		std::shared_ptr<Sheet> sheet;
		sheet = reader.convSheet();
		sheet->PrintValue(std::cout);
	}
	catch (ErrorFormatTable& ex) {
		std::cout << ex.what() << std::endl;
		return 0;
	}
	catch (std::runtime_error& ex) {
		std::cout << ex.what() << std::endl;
	}

	return 0;
}
