#pragma once
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

#include "Sheet.h"

void TestAddCell() {
	Sheet sh;
	std::ostringstream out;
	sh.SetColumns({ "A", "B", "Cell" });
	sh.SetRows({ 1, 2, 30 });
	sh.SetCell("A", 1, "1");
	sh.SetCell("A", 2, "2");
	sh.SetCell("A", 30, "30");
	sh.SetCell("B", 1, "0");
	sh.SetCell("B", 2, "2");
	sh.SetCell("B", 30, "32");
	sh.SetCell("Cell", 1, "4");
	sh.SetCell("Cell", 2, "5");
	sh.SetCell("Cell", 30, "6");
	sh.PrintValue(out);
	std::string answer(",A,B,Cell\n1,1,0,4\n2,2,2,5\n30,30,32,6\n");
	assert(out.str() == answer);
	std::cout << "Tets add cell done" << std::endl;
}

void TestPlusCell() {
	Sheet sh;
	std::ostringstream out;
	sh.SetColumns({ "A", "B", "Cell" });
	sh.SetRows({ 1, 2, 30 });
	sh.SetCell("A", 1, "1");
	sh.SetCell("A", 2, "6");
	sh.SetCell("A", 30, "0");
	sh.SetCell("B", 1, "0");
	sh.SetCell("B", 2, "=A1+Cell30");
	sh.SetCell("B", 30, "=B1+A1");
	sh.SetCell("Cell", 1, "1");
	sh.SetCell("Cell", 2, "0");
	sh.SetCell("Cell", 30, "5");
	sh.PrintValue(out);
	std::string answer(",A,B,Cell\n1,1,0,1\n2,6,6,0\n30,0,1,5\n");
	assert(out.str() == answer);
	std::cout << "Tets sum cell done" << std::endl;
}

void TestCircleCell() {
	Sheet sh;
	std::ostringstream out;
	sh.SetColumns({ "A", "B", "C" });
	sh.SetRows({ 1, 2, 3 });
	sh.SetCell("A", 1, "0");
	sh.SetCell("A", 2, "1");
	sh.SetCell("A", 3, "2");
	sh.SetCell("B", 1, "=A1+B1");
	sh.SetCell("B", 2, "=A2+C3");
	sh.SetCell("B", 3, "=A1+A2");
	sh.SetCell("C", 1, "3");
	sh.SetCell("C", 2, "4");
	sh.SetCell("C", 3, "=B2+C2");
	sh.PrintValue(out);
	std::string answer(",A,B,C\n1,0,CR,3\n2,1,CR,4\n3,2,1,CR\n");
	assert(out.str() == answer);
	std::cout << "Tets circle reference done" << std::endl;
	// std::cout << std::get<int>(sh.GetValue(a, 1)) << std::endl;
}

void TetsInvalidFormula() {
	Sheet sh;
	std::ostringstream out;
	sh.SetColumns({ "A", "B", "C" });
	sh.SetRows({ 1, 2, 3 });
	sh.SetCell("A", 1, "0");
	sh.SetCell("A", 2, "1");
	sh.SetCell("A", 3, "2");
	sh.SetCell("B", 1, "=4-");
	sh.SetCell("B", 2, "=A20+A1");
	sh.SetCell("B", 3, "=a+6");
	sh.SetCell("C", 1, "3");
	sh.SetCell("C", 2, "4");
	sh.SetCell("C", 3, "=");
	sh.PrintValue(out);
	std::string answer(",A,B,C\n1,0,InF,3\n2,1,InF,4\n3,2,InF,InF\n");
	assert(out.str() == answer);
	std::cout << "Tets invalid formula done" << std::endl;
}

void TestOtherCalcl() {
	Sheet sh;
	std::ostringstream out;
	sh.SetColumns({ "A", "B", "C" });
	sh.SetRows({ 1, 2, 3 });
	sh.SetCell("A", 1, "0");
	sh.SetCell("A", 2, "1");
	sh.SetCell("A", 3, "2");
	sh.SetCell("B", 1, "6");
	sh.SetCell("B", 2, "=A3-A2");
	sh.SetCell("B", 3, "=B1*A3");
	sh.SetCell("C", 1, "=C2/A3");
	sh.SetCell("C", 2, "4");
	sh.SetCell("C", 3, "=B1/A1");
	sh.PrintValue(out);
	std::string answer(",A,B,C\n1,0,6,2\n2,1,1,4\n3,2,12,DiV0\n");
	assert(out.str() == answer);
	std::cout << "Tets Other Calcl done" << std::endl;
}

void TestRef2() {
	Sheet sh;
	std::ostringstream out;
	sh.SetColumns({ "A", "B", "C" });
	sh.SetRows({ 1, 2, 3 });
	sh.SetCell("A", 1, "=A2+C1");
	sh.SetCell("A", 2, "1");
	sh.SetCell("A", 3, "2");
	sh.SetCell("B", 1, "6");
	sh.SetCell("B", 2, "=A3-A2");
	sh.SetCell("B", 3, "=B2*A3");
	sh.SetCell("C", 1, "=C2/A3");
	sh.SetCell("C", 2, "4");
	sh.SetCell("C", 3, "=B1/A1");	
	sh.PrintValue(out);
	std::string answer(",A,B,C\n1,3,6,2\n2,1,1,4\n3,2,2,2\n");
	assert(out.str() == answer);
	std::cout << "Tets Ref cell 2" << std::endl;

}

void TestGibridFormula() {
	Sheet sh;
	std::ostringstream out;


	sh.SetColumns({ "A", "B", "C" , "D"});
	sh.SetRows({ 1, 2, 3, 4});	
	sh.SetCell("A", 1, "=1-2");
	sh.SetCell("A", 2, "2");
	sh.SetCell("A", 3, "=C1+1");
	sh.SetCell("A", 4, "6");
	sh.SetCell("B", 1, "=1+2");
	sh.SetCell("B", 2, "=A2/1");
	sh.SetCell("B", 3, "=1+C1");
	sh.SetCell("B", 4, "7");
	sh.SetCell("C", 1, "=3/1");
	sh.SetCell("C", 2, "=1/A2");
	sh.SetCell("C", 3, "=D1*3");
	sh.SetCell("C", 4, "8");
	sh.SetCell("D", 1, "=6*2");
	sh.SetCell("D", 2, "=1-2");
	sh.SetCell("D", 3, "=3*D1");
	sh.SetCell("D", 4, "9");

	sh.PrintValue(out);
	std::string answer(",A,B,C,D\n1,-1,3,3,12\n2,2,2,0.5,-1\n3,4,4,36,36\n4,6,7,8,9\n");
	assert(out.str() == answer);
	std::cout << "Test gibrid formula" << std::endl;
}


void InvalidFormulaII() {
	Sheet sh;
	std::ostringstream out;
	sh.SetColumns({ "A", "B", "C" });
	sh.SetRows({ 1, 2, 3 });
	sh.SetCell("A", 1, "=");
	sh.SetCell("A", 2, "=A1+");
	sh.SetCell("A", 3, "=+");
	sh.SetCell("B", 1, "=4-");
	sh.SetCell("B", 2, "=A20+A1");
	sh.SetCell("B", 3, "=a+6");
	sh.SetCell("C", 1, "3");
	sh.SetCell("C", 2, "=-4");
	sh.SetCell("C", 3, "=");
	sh.PrintValue(out);
	std::string answer(",A,B,C\n1,InF,InF,3\n2,InF,InF,InF\n3,InF,InF,InF\n");
	assert(out.str() == answer);
	std::cout << "Tets invalid formula II done" << std::endl;
}

void TestOFSheetPrecision() {
	Sheet sh;
	std::ostringstream out;
	sh.SetColumns({ "A", "B", "C" });
	sh.SetRows({ 1, 2, 3 });
	sh.SetCell("A", 1, "=1/3");
	sh.SetCell("A", 2, "=A1+2");
	sh.SetCell("A", 3, "=4+8");
	sh.SetCell("B", 1, "=4-102");
	sh.SetCell("B", 2, "=A2+A1");
	sh.SetCell("B", 3, "=a+6");
	sh.SetCell("C", 1, "3");
	sh.SetCell("C", 2, "=50-4");
	sh.SetCell("C", 3, "=1+5");
	sh.PrintValue(out);
	std::string answer(",A,B,C\n1,0.33,-98,3\n2,2.3,2.7,46\n3,12,InF,6\n");
	assert(out.str() == answer);
	std::cout << "Tets formula with precision done" << std::endl;
}

void testSheet() {
	TestAddCell();
	TestPlusCell();
	TestCircleCell();
	TetsInvalidFormula();
	InvalidFormulaII();
	TestOtherCalcl();
	TestRef2();
	TestGibridFormula();
	TestOFSheetPrecision();
	std::cout << "Test sheet done" << std::endl;;
}