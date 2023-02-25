#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <string_view>
#include <vector>

#include "Cell.h"
#include "common.h"

class Sheet : public SheetInterface {
public:
	void SetCell(std::string column, int row, std::string text) override;

	Value GetValue(const rawPosition& raw_pos) override;

	void isCirced(const rawPosition& pos, const std::vector<rawPosition>& ref_pos);

	void SetColumns(std::vector<std::string> columns);

	void SetRows(std::vector<int> rows);

	void PrintValue(std::ostream& out);

	void PrintText(std::ostream& out);

	~Sheet();



private:
	Position convRawPos(const rawPosition& pos);

	void IsCicled(Position& pos, std::set<Position>& poses,
		std::set<Position>& buffer);

	int next_row_ = 0;

	std::map<int, int> rows_;
	std::vector<int> oreder_row_;

	std::map<std::string, int> columns_;
	std::vector<std::string> order_column_;
	int next_column_ = 0;

	std::map<Position, std::shared_ptr<cell::Cell>> cells_;
	std::map<Position, std::set<Position>> used_cells_;
};
