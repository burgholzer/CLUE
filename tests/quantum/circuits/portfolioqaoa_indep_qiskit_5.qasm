// Benchmark was created by MQT Bench on 2022-12-15
// For more information about MQT Bench, please visit https://www.cda.cit.tum.de/mqtbench/
// MQT Bench version: 0.2.2
// Qiskit version: {'qiskit-terra': '0.22.3', 'qiskit-aer': '0.11.1', 'qiskit-ignis': '0.7.0', 'qiskit-ibmq-provider': '0.19.2', 'qiskit': '0.39.3', 'qiskit-nature': '0.5.1', 'qiskit-finance': '0.3.4', 'qiskit-optimization': '0.4.0', 'qiskit-machine-learning': '0.5.0'}

OPENQASM 2.0;
include "qelib1.inc";
qreg q[5];
creg meas[5];
creg meas2[5];
u2(-2.9364045,-pi) q[0];
u2(-2.8965604,-pi) q[1];
rzz(-3.36411465683408) q[0],q[1];
u2(-2.9222125,-pi) q[2];
rzz(-3.36270631869151) q[0],q[2];
rzz(-3.36208859292798) q[1],q[2];
u2(-2.9156664,-pi) q[3];
rzz(-3.36258811886834) q[0],q[3];
rzz(-3.36251313982233) q[1],q[3];
rzz(-3.36241694530925) q[2],q[3];
u2(-2.7260931,-pi) q[4];
rzz(-3.36403719842143) q[0],q[4];
u3(2.8275379,1.4709689,pi/2) q[0];
rzz(-3.36971451477506) q[1],q[4];
u3(2.8275379,1.5071817,pi/2) q[1];
rzz(-3.05751929556147) q[0],q[1];
rzz(-3.36210264457705) q[2],q[4];
u3(2.8275379,1.4838674,pi/2) q[2];
rzz(-3.05623930915053) q[0],q[2];
rzz(-3.05567788106795) q[1],q[2];
rzz(-3.36171465444023) q[3],q[4];
u3(2.8275379,1.4898169,pi/2) q[3];
rzz(-3.05613188170618) q[0],q[3];
rzz(-3.05606373602646) q[1],q[3];
rzz(-3.05597630839397) q[2],q[3];
u3(2.8275379,1.6621131,pi/2) q[4];
rzz(-3.05744889647718) q[0],q[4];
u3(3.0314751,-2.2570464,-pi/2) q[0];
rzz(-3.06260879917638) q[1],q[4];
u3(3.0314751,-2.3026177,-pi/2) q[1];
rzz(3.84766811066656) q[0],q[1];
rzz(-3.0556906520917) q[2],q[4];
u3(3.0314751,-2.2732783,-pi/2) q[2];
rzz(3.84605733983591) q[0],q[2];
rzz(3.84535082297666) q[1],q[2];
rzz(-3.05533802221703) q[3],q[4];
u3(3.0314751,-2.2807653,-pi/2) q[3];
rzz(3.84592215012429) q[0],q[3];
rzz(3.84583639368798) q[1],q[3];
rzz(3.84572637230103) q[2],q[3];
u3(3.0314751,-2.4975877,-pi/2) q[4];
rzz(3.84757951848268) q[0],q[4];
rx(6.60957837932846) q[0];
rzz(3.85407288488553) q[1],q[4];
rx(6.60957837932846) q[1];
rzz(3.84536689439145) q[2],q[4];
rx(6.60957837932846) q[2];
rzz(3.84492313505831) q[3],q[4];
rx(6.60957837932846) q[3];
rx(6.60957837932846) q[4];
barrier q[0],q[1],q[2],q[3],q[4];
measure q[0] -> meas[0];
measure q[1] -> meas[1];
measure q[2] -> meas[2];
measure q[3] -> meas[3];
measure q[4] -> meas[4];
barrier q[0],q[1],q[2],q[3],q[4];
measure q[0] -> meas2[0];
measure q[1] -> meas2[1];
measure q[2] -> meas2[2];
measure q[3] -> meas2[3];
measure q[4] -> meas2[4];