/*
 * File: main.c
 * Creator: Patrice Douge
 * Created: Mon Nov 28 14:11:17 2016
 * Time-stamp: <Mon Nov 28 14:22:27 EST 2016 ferguson>
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"

/**
 * Two AND gates connected to make a 3-input AND circuit.
 */
static Circuit* Circuits_and3() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Value* in2 = new_Value(false);
	Gate* and0 = new_AndGate(in0, in1);
	Gate* and1 = new_AndGate(Gate_getOutput(and0), in2);

	Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(and1);
	Gate** gates = new_Gate_array(2);
	gates[0] = and0;
	gates[1] = and1;
	return new_Circuit(3, inputs, 1, outputs, 2, gates);
}

static char* b2s(bool b) {
	return b ? "T" : "F";
}

static void test3In1Out(Circuit* circuit, bool in0, bool in1, bool in2) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	//Circuit_dump(circuit);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s %s %s -> %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0));
}

static void test3In2Out(Circuit* circuit, bool in0, bool in1, bool in2) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	//Circuit_dump(circuit);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	bool out1 = Circuit_getOutput(circuit, 1);
	printf("%s %s %s -> %s %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0),b2s(out1));
}

static void test2In1Out(Circuit *circuit, bool in0, bool in1) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	//Circuit_dump(circuit);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s %s -> %s\n", b2s(in0), b2s(in1), b2s(out0));
}

static void testAll2In1Out(Circuit *circuit) {
	test2In1Out(circuit, false, false);
	test2In1Out(circuit, false, true);
	test2In1Out(circuit, true, false);
	test2In1Out(circuit, true, true);
}

static void testAll3In1Out(Circuit *circuit) {

	test3In1Out(circuit, false, false, false);
	test3In1Out(circuit, false, false, true);
	test3In1Out(circuit, false, true, false);
	test3In1Out(circuit, false, true, true);
	test3In1Out(circuit, true, false, false);
	test3In1Out(circuit, true, false, true);
	test3In1Out(circuit, true, true, false);
	test3In1Out(circuit, true, true, true);
}

static void testAll3In2Out(Circuit *circuit) {

	test3In2Out(circuit, false, false, false);
	test3In2Out(circuit, false, false, true);
	test3In2Out(circuit, false, true, false);
	test3In2Out(circuit, false, true, true);
	test3In2Out(circuit, true, false, false);
	test3In2Out(circuit, true, false, true);
	test3In2Out(circuit, true, true, false);
	test3In2Out(circuit, true, true, true);
}

static Circuit* Circuits_a() {

	Value *in0 = new_Value(false);
	Value *in1 = new_Value(false);
	Value *in2 = new_Value(false);
	
	Gate *not0 = new_Inverter(in1);
	Gate *and0 = new_AndGate(in0, Gate_getOutput(not0));
	Gate *and1 = new_AndGate(in1, in2);
	Gate *or0 = new_OrGate(Gate_getOutput(and0), Gate_getOutput(and1));

	Value **inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value **outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(or0);
	Gate **gates = new_Gate_array(4);
	gates[0] = not0;
	gates[1] = and0;
	gates[2] = and1;
	gates[3] = or0;

	return new_Circuit(3, inputs, 1, outputs, 4, gates);
}

static Circuit* Circuits_b() {

	Value *in0 = new_Value(false);
	Value *in1 = new_Value(false);
	Value *in2 = new_Value(false);
	
	Gate *not0 = new_Inverter(in1);
	Gate *and0 = new_AndGate(in0, Gate_getOutput(not0));
	Gate *not1 = new_Inverter(Gate_getOutput(and0));
	Gate *and1 = new_AndGate(in1, in2);
	Gate *not2 = new_Inverter(Gate_getOutput(and1));
	Gate *or0 = new_OrGate(Gate_getOutput(and0), Gate_getOutput(and1));
	Gate *not3 = new_Inverter(Gate_getOutput(or0));

	Value **inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value **outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(not3);
	Gate **gates = new_Gate_array(7);
	gates[0] = not0;
	gates[1] = and0;
	gates[2] = and1;
	gates[3] = or0;
	gates[4] = not1;
	gates[5] = not2;
	gates[6] = not3;

	return new_Circuit(3, inputs, 1, outputs, 7, gates);
}

static Circuit* Circuits_c() {
	
	Value *in0 = new_Value(false);
	Value *in1 = new_Value(false);
	
	Gate *not0 = new_Inverter(in0);
	Gate *not1 = new_Inverter(in1);
	Gate *and0 = new_AndGate(in1, in0);
	Gate *and1 = new_AndGate(Gate_getOutput(not0), Gate_getOutput(not1));
	Gate *or0 = new_OrGate(Gate_getOutput(and0), Gate_getOutput(and1));

	Value **inputs = new_Value_array(2);
	inputs[0] = in0;
	inputs[1] = in1;
	Value **outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(or0);
	Gate **gates = new_Gate_array(5);
	gates[0] = not0;
	gates[1] = not1;
	gates[2] = and0;
	gates[3] = and1;
	gates[4] = or0;

	return new_Circuit(3, inputs, 1, outputs, 5, gates);
}

static Circuit* Circuits_d() {
	
	Value *in0 = new_Value(false);
	Value *in1 = new_Value(false);
	Value *in2 = new_Value(false);
	
	Gate *not0 = new_Inverter(in0);
	Gate *not1 = new_Inverter(in1);
	Gate *not2 = new_Inverter(in2);

	Gate *and0 = new_And3Gate(Gate_getOutput(not0), Gate_getOutput(not1), in2);
	Gate *and1 = new_And3Gate(Gate_getOutput(not0), in1, Gate_getOutput(not2));
	Gate *and2 = new_And3Gate(Gate_getOutput(not0), in1, in2);
	Gate *and3 = new_And3Gate(in0, Gate_getOutput(not1), Gate_getOutput(not2));
	Gate *and4 = new_And3Gate(in0, Gate_getOutput(not1), in2);
	Gate *and5 = new_And3Gate(in0, in1, Gate_getOutput(not2));
	Gate *and6 = new_And3Gate(in0, in1, in2);

	Gate *or0 = new_Or4Gate(Gate_getOutput(and0), Gate_getOutput(and1), Gate_getOutput(and3), Gate_getOutput(and6));
	Gate *or1 = new_Or4Gate(Gate_getOutput(and2), Gate_getOutput(and4), Gate_getOutput(and5), Gate_getOutput(and6));

	Value **inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value **outputs = new_Value_array(2);
	outputs[0] = Gate_getOutput(or0);
	outputs[1] = Gate_getOutput(or1);
	Gate **gates = new_Gate_array(12);
	gates[0] = not0;
	gates[1] = not1;
	gates[2] = not2;
	gates[3] = and0;
	gates[4] = and1;
	gates[5] = and2;
	gates[6] = and3;
	gates[7] = and4;
	gates[8] = and5;
	gates[9] = and6;
	gates[10] = or0;
	gates[11] = or1;

	return new_Circuit(3, inputs, 2, outputs, 12, gates);
}


int main(int argc, char **argv) {
	Circuit* c = Circuits_and3();
	printf("Some input(s) false: should be false\n");
	test3In1Out(c, true, true, false);
	printf("All inputs true: should be true\n");
	test3In1Out(c, true, true, true);

	printf("%s\n");
	testAll3In1Out(Circuits_a());
	printf("%s\n");
	testAll3In1Out(Circuits_b());
	printf("%s\n");
	testAll2In1Out(Circuits_c());
	printf("%s\n");
	testAll3In2Out(Circuits_d());
}
