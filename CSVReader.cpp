#include "CSVReader.h"

CSVReader::CSVReader(std::string& filename) {
	std::vector<std::pair<std::string, std::vector<std::string>>> result;

	std::ifstream myFile(filename);

	if (!myFile.is_open()) throw std::runtime_error("Could not open file");

	std::string line, colname;
	std::string val;

	if (myFile.good()) {
		std::getline(myFile, line);

		std::stringstream ss(line);

		while (std::getline(ss, colname, ',')) {
			result.push_back({ colname, std::vector<std::string>{} });
		}
	}

	int cnt_clmn = result.size();
	while (std::getline(myFile, line)) {
		std::stringstream ss(line);

		int colIdx = 0;

		while (std::getline(ss, val, ',')) {
			if (cnt_clmn <= colIdx) {
				throw ErrorFormatTable("Invalid format table");
			}
			result.at(colIdx).second.push_back(val);
			colIdx++;
		}

	}

	myFile.close();
	table_ = std::move(result);
}

std::shared_ptr<Sheet> CSVReader::convSheet() const {
	if (table_.empty()) {
		throw ErrorFormatTable("Empty table");
	}
	size_t size_column = std::get<1>(table_[0]).size();

	std::vector<int> rows;
	for (const auto& i : std::get<1>(table_[0])) {
		try {
			rows.push_back(std::stoi(i));
		}
		catch (...) {
			throw ErrorFormatTable("Invalid row value");
		}
	}

	std::vector<std::string> columns;
	for (int i = 1; i < table_.size(); ++i) {
		if (std::get<1>(table_[i]).size() != size_column) {
			throw ErrorFormatTable("Invalid format table");
		}
		columns.push_back(std::get<0>(table_[i]));
	}

	std::shared_ptr<Sheet> sheet = std::make_shared<Sheet>();
	sheet->SetColumns(columns);
	sheet->SetRows(rows);

	for (int i = 1; i < table_.size(); ++i) {
		for (int row = 0; row < rows.size(); ++row) {
			sheet->SetCell(std::get<0>(table_[i]), rows[row],
				std::get<1>(table_[i])[row]);
		}
	}

	return sheet;
}