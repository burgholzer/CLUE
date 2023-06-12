// Benchmark was created by MQT Bench on 2022-12-15
// For more information about MQT Bench, please visit https://www.cda.cit.tum.de/mqtbench/
// MQT Bench version: 0.2.2
// Qiskit version: {'qiskit-terra': '0.22.3', 'qiskit-aer': '0.11.1', 'qiskit-ignis': '0.7.0', 'qiskit-ibmq-provider': '0.19.2', 'qiskit': '0.39.3', 'qiskit-nature': '0.5.1', 'qiskit-finance': '0.3.4', 'qiskit-optimization': '0.4.0', 'qiskit-machine-learning': '0.5.0'}

OPENQASM 2.0;
include "qelib1.inc";
qreg q[6];
creg meas[6];
creg meas3[6];
u2(-3.0353524e-05,-pi) q[0];
u2(-3.7986612e-06,-pi) q[1];
rzz(-0.0262391625046928) q[0],q[1];
u2(0.00015561292,-pi) q[2];
rzz(-0.0262375265385264) q[0],q[2];
rzz(-0.0262381191423384) q[1],q[2];
u2(7.6054596e-05,-pi) q[3];
rzz(-0.0262391215490247) q[0],q[3];
rzz(-0.0262388554932538) q[1],q[3];
rzz(-0.0262389854262818) q[2],q[3];
u2(-3.7946743e-05,-pi) q[4];
rzz(-0.0262382604459212) q[0],q[4];
rzz(-0.0262390366673601) q[1],q[4];
rzz(-0.0262392617513034) q[2],q[4];
rzz(-0.0262385724310715) q[3],q[4];
u2(-0.00014975057,-pi) q[5];
rzz(-0.0262403722994893) q[0],q[5];
u3(3.0099168,-1.5703345,pi/2) q[0];
rzz(-0.0262392176399683) q[1],q[5];
u3(3.0099168,-1.5707385,pi/2) q[1];
rzz(0.399245557389473) q[0],q[1];
rzz(-0.0262378972135298) q[2],q[5];
u3(3.0099168,-1.5731641,pi/2) q[2];
rzz(0.399220665123042) q[0],q[2];
rzz(0.399229681967204) q[1],q[2];
rzz(-0.0262381353548895) q[3],q[5];
u3(3.0099168,-1.5719535,pi/2) q[3];
rzz(0.399244934222917) q[0],q[3];
rzz(0.399240886015031) q[1],q[3];
rzz(0.399242863028747) q[2],q[3];
rzz(-0.0262376202159157) q[4],q[5];
u3(3.0099168,-1.5702189,pi/2) q[4];
rzz(0.399231831991148) q[0],q[4];
rzz(0.399243642694366) q[1],q[4];
rzz(0.399247067489818) q[2],q[4];
rzz(0.399236579043772) q[3],q[4];
u3(3.0099168,-1.5685178,pi/2) q[5];
rzz(0.399263965187273) q[0],q[5];
u3(1.2410916,-1.5689178,pi/2) q[0];
rzz(0.39924639630778) q[1],q[5];
u3(1.2410916,-1.5705612,pi/2) q[1];
rzz(1.62388420493979) q[0],q[1];
rzz(0.399226305179135) q[2],q[5];
u3(1.2410916,-1.5804269,pi/2) q[2];
rzz(1.62378295858267) q[0],q[2];
rzz(1.62381963353257) q[1],q[2];
rzz(0.399229928651487) q[3],q[5];
u3(1.2410916,-1.5755032,pi/2) q[3];
rzz(1.62388167028334) q[0],q[3];
rzz(1.62386520467534) q[1],q[3];
rzz(1.6238732459454) q[2],q[3];
rzz(0.399222090484141) q[4],q[5];
u3(1.2410916,-1.5684479,pi/2) q[4];
rzz(1.62382837850132) q[0],q[4];
rzz(1.62387641714333) q[1],q[4];
rzz(1.6238903470948) q[2],q[4];
rzz(1.62384768657785) q[3],q[4];
u3(1.2410916,-1.5615286,pi/2) q[5];
rzz(1.62395907648574) q[0],q[5];
rx(-10.8720078390703) q[0];
rzz(1.62388761714104) q[1],q[5];
rx(-10.8720078390703) q[1];
rzz(1.62380589884546) q[2],q[5];
rx(-10.8720078390703) q[2];
rzz(1.62382063689179) q[3],q[5];
rx(-10.8720078390703) q[3];
rzz(1.62378875607079) q[4],q[5];
rx(-10.8720078390703) q[4];
rx(-10.8720078390703) q[5];
barrier q[0],q[1],q[2],q[3],q[4],q[5];
// measure q[0] -> meas[0];
// measure q[1] -> meas[1];
// measure q[2] -> meas[2];
// measure q[3] -> meas[3];
// measure q[4] -> meas[4];
// measure q[5] -> meas[5];
barrier q[0],q[1],q[2],q[3],q[4],q[5];
// measure q[0] -> meas3[0];
// measure q[1] -> meas3[1];
// measure q[2] -> meas3[2];
// measure q[3] -> meas3[3];
// measure q[4] -> meas3[4];
// measure q[5] -> meas3[5];