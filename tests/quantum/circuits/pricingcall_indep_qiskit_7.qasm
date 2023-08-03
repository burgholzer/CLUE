// Benchmark was created by MQT Bench on 2022-12-15
// For more information about MQT Bench, please visit https://www.cda.cit.tum.de/mqtbench/
// MQT Bench version: 0.2.2
// Qiskit version: {'qiskit-terra': '0.22.3', 'qiskit-aer': '0.11.1', 'qiskit-ignis': '0.7.0', 'qiskit-ibmq-provider': '0.19.2', 'qiskit': '0.39.3', 'qiskit-nature': '0.5.1', 'qiskit-finance': '0.3.4', 'qiskit-optimization': '0.4.0', 'qiskit-machine-learning': '0.5.0'}

OPENQASM 2.0;
include "qelib1.inc";
qreg q[7];
creg meas[7];
ry(1.7092511) q[0];
ry(1.682873) q[1];
ry(1.5108045) q[2];
cx q[2],q[1];
ry(1.0354508) q[1];
cx q[2],q[1];
cx q[1],q[0];
ry(0.31774998) q[0];
cx q[2],q[0];
ry(0.15368908) q[0];
cx q[1],q[0];
ry(0.68140462) q[0];
cx q[2],q[0];
ry(3*pi/8) q[3];
cry(0) q[0],q[3];
cry(0) q[1],q[3];
cry(0) q[2],q[3];
x q[2];
x q[4];
cx q[0],q[5];
ccx q[1],q[5],q[6];
x q[6];
ccx q[2],q[6],q[4];
x q[2];
cx q[4],q[3];
u(0.29425236,0,0) q[3];
cx q[4],q[3];
u3(0.29425236,-pi,-pi) q[3];
cx q[4],q[3];
u(-0.04906796,0,0) q[3];
cx q[4],q[3];
u(0.04906796,0,0) q[3];
x q[6];
ccx q[1],q[5],q[6];
cx q[0],q[5];
ccx q[4],q[0],q[3];
cx q[4],q[3];
u(0.04906796,0,0) q[3];
cx q[4],q[3];
u(-0.04906796,0,0) q[3];
ccx q[4],q[0],q[3];
cx q[0],q[5];
cx q[4],q[3];
u(-0.098135921,0,0) q[3];
cx q[4],q[3];
u(0.098135921,0,0) q[3];
ccx q[4],q[1],q[3];
cx q[4],q[3];
u(0.098135921,0,0) q[3];
cx q[4],q[3];
u(-0.098135921,0,0) q[3];
ccx q[4],q[1],q[3];
ccx q[1],q[5],q[6];
cx q[4],q[3];
u(-0.19627184,0,0) q[3];
cx q[4],q[3];
u(0.19627184,0,0) q[3];
ccx q[4],q[2],q[3];
cx q[4],q[3];
u(0.19627184,0,0) q[3];
cx q[4],q[3];
u(-0.19627184,0,0) q[3];
ccx q[4],q[2],q[3];
x q[2];
x q[6];
ccx q[2],q[6],q[4];
x q[2];
x q[4];
x q[6];
ccx q[1],q[5],q[6];
cx q[0],q[5];
barrier q[0],q[1],q[2],q[3],q[4],q[5],q[6];
measure q[0] -> meas[0];
measure q[1] -> meas[1];
measure q[2] -> meas[2];
measure q[3] -> meas[3];
measure q[4] -> meas[4];
measure q[5] -> meas[5];
measure q[6] -> meas[6];
