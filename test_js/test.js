const hexdump = require('hexdump-nodejs')
const DoIP = require("../auto_gen/out/doip_packets.js")

var udsDiagSessionControl_1 = new DoIP.Uds_DiagSessionControl_Packet(0xEA00, 0x0005, 0x10, 0x03)
udsDiagSessionControl_1.serialize(0)
console.log("uds_1 udsDiagSessionControl_1 buffer: ")
console.log(hexdump(udsDiagSessionControl_1.buffer))
