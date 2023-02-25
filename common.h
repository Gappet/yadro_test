#pragma once
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

using Value = std::variant<double, std::string>;

struct rawPosition {
	std::string column;
	int row;
};

class Position {
public:
	Position() = default;

	Position(const Position& pos);

	Position(int row = 0, int column = 0);

	bool operator==(const Position& pos) const;

	bool operator<(const Position& pos) const;

	bool isValid() const;

	int column_;
	int row_;
};

class SheetInterface {
public:
	virtual void SetCell(std::string column, int row,
		std::string text) = 0;

	virtual Value GetValue(const rawPosition& raw_pos) = 0;

	~SheetInterface() {};
};

class CellInterface {
public:
	virtual Value getValue() = 0;

	virtual const std::string& getText() = 0;

	virtual ~CellInterface() {}
};

class CircularDependencyException : public std::runtime_error {
public:
	using std::runtime_error::runtime_error;
};