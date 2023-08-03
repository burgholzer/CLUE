// Benchmark was created by MQT Bench on 2022-12-15
// For more information about MQT Bench, please visit https://www.cda.cit.tum.de/mqtbench/
// MQT Bench version: 0.2.2
// Qiskit version: {'qiskit-terra': '0.22.3', 'qiskit-aer': '0.11.1', 'qiskit-ignis': '0.7.0', 'qiskit-ibmq-provider': '0.19.2', 'qiskit': '0.39.3', 'qiskit-nature': '0.5.1', 'qiskit-finance': '0.3.4', 'qiskit-optimization': '0.4.0', 'qiskit-machine-learning': '0.5.0'}

OPENQASM 2.0;
include "qelib1.inc";
qreg q[9];
creg meas[9];
ry(1.6653032) q[0];
ry(1.6795034) q[1];
ry(1.6593386) q[2];
ry(1.5137858) q[3];
cx q[3],q[2];
ry(0.92894651) q[2];
cx q[3],q[2];
cx q[2],q[1];
ry(0.28542724) q[1];
cx q[3],q[1];
ry(0.13151599) q[1];
cx q[2],q[1];
ry(0.591118) q[1];
cx q[3],q[1];
cx q[1],q[0];
ry(0.093121624) q[0];
cx q[2],q[0];
ry(0.023280045) q[0];
cx q[1],q[0];
ry(0.18666819) q[0];
cx q[3],q[0];
ry(0.10136095) q[0];
cx q[1],q[0];
ry(0.010077397) q[0];
cx q[2],q[0];
ry(0.049324335) q[0];
cx q[1],q[0];
ry(0.34868875) q[0];
cx q[3],q[0];
ry(3*pi/8) q[4];
cry(0) q[0],q[4];
cry(0) q[1],q[4];
cry(0) q[2],q[4];
cry(0) q[3],q[4];
x q[3];
x q[5];
cx q[0],q[6];
ccx q[1],q[6],q[7];
ccx q[2],q[7],q[8];
x q[8];
ccx q[3],q[8],q[5];
x q[3];
cx q[5],q[4];
u(0.29425236,0,0) q[4];
cx q[5],q[4];
u3(0.29425236,-pi,-pi) q[4];
cx q[5],q[4];
u(-0.022898382,0,0) q[4];
cx q[5],q[4];
u(0.022898382,0,0) q[4];
x q[8];
ccx q[2],q[7],q[8];
ccx q[1],q[6],q[7];
cx q[0],q[6];
ccx q[5],q[0],q[4];
cx q[5],q[4];
u(0.022898382,0,0) q[4];
cx q[5],q[4];
u(-0.022898382,0,0) q[4];
ccx q[5],q[0],q[4];
cx q[0],q[6];
cx q[5],q[4];
u(-0.045796763,0,0) q[4];
cx q[5],q[4];
u(0.045796763,0,0) q[4];
ccx q[5],q[1],q[4];
cx q[5],q[4];
u(0.045796763,0,0) q[4];
cx q[5],q[4];
u(-0.045796763,0,0) q[4];
ccx q[5],q[1],q[4];
ccx q[1],q[6],q[7];
cx q[5],q[4];
u(-0.091593526,0,0) q[4];
cx q[5],q[4];
u(0.091593526,0,0) q[4];
ccx q[5],q[2],q[4];
cx q[5],q[4];
u(0.091593526,0,0) q[4];
cx q[5],q[4];
u(-0.091593526,0,0) q[4];
ccx q[5],q[2],q[4];
ccx q[2],q[7],q[8];
cx q[5],q[4];
u(-0.18318705,0,0) q[4];
cx q[5],q[4];
u(0.18318705,0,0) q[4];
ccx q[5],q[3],q[4];
cx q[5],q[4];
u(0.18318705,0,0) q[4];
cx q[5],q[4];
u(-0.18318705,0,0) q[4];
ccx q[5],q[3],q[4];
x q[3];
x q[8];
ccx q[3],q[8],q[5];
x q[3];
x q[5];
x q[8];
ccx q[2],q[7],q[8];
ccx q[1],q[6],q[7];
cx q[0],q[6];
barrier q[0],q[1],q[2],q[3],q[4],q[5],q[6],q[7],q[8];
measure q[0] -> meas[0];
measure q[1] -> meas[1];
measure q[2] -> meas[2];
measure q[3] -> meas[3];
measure q[4] -> meas[4];
measure q[5] -> meas[5];
measure q[6] -> meas[6];
measure q[7] -> meas[7];
measure q[8] -> meas[8];
