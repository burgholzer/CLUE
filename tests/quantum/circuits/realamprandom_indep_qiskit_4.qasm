// Benchmark was created by MQT Bench on 2022-12-15
// For more information about MQT Bench, please visit https://www.cda.cit.tum.de/mqtbench/
// MQT Bench version: 0.2.2
// Qiskit version: {'qiskit-terra': '0.22.3', 'qiskit-aer': '0.11.1', 'qiskit-ignis': '0.7.0', 'qiskit-ibmq-provider': '0.19.2', 'qiskit': '0.39.3', 'qiskit-nature': '0.5.1', 'qiskit-finance': '0.3.4', 'qiskit-optimization': '0.4.0', 'qiskit-machine-learning': '0.5.0'}

OPENQASM 2.0;
include "qelib1.inc";
qreg q[4];
creg meas[4];
ry(0.437736045249968) q[0];
ry(0.18321892262315) q[1];
cx q[0],q[1];
ry(0.575611746244093) q[2];
cx q[0],q[2];
cx q[1],q[2];
ry(0.776686202106466) q[3];
cx q[0],q[3];
ry(0.534352403109019) q[0];
cx q[1],q[3];
ry(0.34528158282276) q[1];
cx q[0],q[1];
cx q[2],q[3];
ry(0.354179833958195) q[2];
cx q[0],q[2];
cx q[1],q[2];
ry(0.788201819097312) q[3];
cx q[0],q[3];
ry(0.932527774863635) q[0];
cx q[1],q[3];
ry(0.669867516573648) q[1];
cx q[0],q[1];
cx q[2],q[3];
ry(0.0916302275882332) q[2];
cx q[0],q[2];
cx q[1],q[2];
ry(0.99697407372944) q[3];
cx q[0],q[3];
ry(0.942725612812279) q[0];
cx q[1],q[3];
ry(0.563893755728657) q[1];
cx q[2],q[3];
ry(0.511353614285624) q[2];
ry(0.693661683207207) q[3];
barrier q[0],q[1],q[2],q[3];
measure q[0] -> meas[0];
measure q[1] -> meas[1];
measure q[2] -> meas[2];
measure q[3] -> meas[3];