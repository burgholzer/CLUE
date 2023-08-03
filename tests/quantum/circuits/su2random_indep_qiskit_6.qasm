// Benchmark was created by MQT Bench on 2022-12-15
// For more information about MQT Bench, please visit https://www.cda.cit.tum.de/mqtbench/
// MQT Bench version: 0.2.2
// Qiskit version: {'qiskit-terra': '0.22.3', 'qiskit-aer': '0.11.1', 'qiskit-ignis': '0.7.0', 'qiskit-ibmq-provider': '0.19.2', 'qiskit': '0.39.3', 'qiskit-nature': '0.5.1', 'qiskit-finance': '0.3.4', 'qiskit-optimization': '0.4.0', 'qiskit-machine-learning': '0.5.0'}

OPENQASM 2.0;
include "qelib1.inc";
qreg q[6];
creg meas[6];
u3(0.34597359,0.43744856,0) q[0];
u3(0.92896211,0.83968693,0) q[1];
cx q[0],q[1];
u3(0.17729172,0.75469799,0) q[2];
cx q[0],q[2];
cx q[1],q[2];
u3(0.8897231,0.15782943,0) q[3];
cx q[0],q[3];
cx q[1],q[3];
cx q[2],q[3];
u3(0.88806785,0.30535942,0) q[4];
cx q[0],q[4];
cx q[1],q[4];
cx q[2],q[4];
cx q[3],q[4];
u3(0.44791673,0.20405002,0) q[5];
cx q[0],q[5];
u3(0.49600037,0.87806698,0) q[0];
cx q[1],q[5];
u3(0.93053933,0.61534486,0) q[1];
cx q[0],q[1];
cx q[2],q[5];
u3(0.36175966,0.58573194,0) q[2];
cx q[0],q[2];
cx q[1],q[2];
cx q[3],q[5];
u3(0.04735545,0.94404993,0) q[3];
cx q[0],q[3];
cx q[1],q[3];
cx q[2],q[3];
cx q[4],q[5];
u3(0.041646114,0.17231304,0) q[4];
cx q[0],q[4];
cx q[1],q[4];
cx q[2],q[4];
cx q[3],q[4];
u3(0.54988007,0.1567303,0) q[5];
cx q[0],q[5];
u3(0.77955409,0.22207655,0) q[0];
cx q[1],q[5];
u3(0.31187127,0.47021141,0) q[1];
cx q[0],q[1];
cx q[2],q[5];
u3(0.99239276,0.20695346,0) q[2];
cx q[0],q[2];
cx q[1],q[2];
cx q[3],q[5];
u3(0.21896571,0.39089583,0) q[3];
cx q[0],q[3];
cx q[1],q[3];
cx q[2],q[3];
cx q[4],q[5];
u3(0.61000413,0.098510831,0) q[4];
cx q[0],q[4];
cx q[1],q[4];
cx q[2],q[4];
cx q[3],q[4];
u3(0.9605572,0.62929893,0) q[5];
cx q[0],q[5];
u3(0.42806545,0.68376035,0) q[0];
cx q[1],q[5];
u3(0.76834005,0.27471124,0) q[1];
cx q[2],q[5];
u3(0.15698093,0.96478905,0) q[2];
cx q[3],q[5];
u3(0.59256226,0.92646702,0) q[3];
cx q[4],q[5];
u3(0.040194977,0.26254046,0) q[4];
u3(0.6306672,0.91889796,0) q[5];
barrier q[0],q[1],q[2],q[3],q[4],q[5];
measure q[0] -> meas[0];
measure q[1] -> meas[1];
measure q[2] -> meas[2];
measure q[3] -> meas[3];
measure q[4] -> meas[4];
measure q[5] -> meas[5];
