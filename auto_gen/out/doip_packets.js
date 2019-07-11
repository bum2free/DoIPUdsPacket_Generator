var Doip_Packet = function () {
  this.version = 0x2;
  this.version_inv = 0xfd;
  this.payloadType = 0x0;
  this.payloadLength = 0x0;
}

Doip_Packet.prototype.serialize = function (len){
  var parse_index = 0;
  var buffer = Buffer.alloc(len + 8)

  this.payloadLength = len

  buffer.writeUInt8(this.version, parse_index)
  parse_index += 1
  buffer.writeUInt8(this.version_inv, parse_index)
  parse_index += 1
  buffer.writeUInt16BE(this.payloadType, parse_index)
  parse_index += 2
  buffer.writeUInt32BE(this.payloadLength, parse_index)
  parse_index += 4

  this.parse_index = parse_index;
  this.buffer = buffer
}
Doip_Packet.prototype.deserialize = function (buffer) {
  var parse_index = 0;
  this.version = buffer.readUInt8(parse_index)
  parse_index += 1
  this.version_inv = buffer.readUInt8(parse_index)
  parse_index += 1
  this.payloadType = buffer.readUInt16BE(parse_index)
  parse_index += 2
  this.payloadLength = buffer.readUInt32BE(parse_index)
  parse_index += 4

  this.parse_index = parse_index;
  this.buffer = buffer;
}
Doip_Packet.prototype.createFromBuffer = function (buffer) {
  var obj = {}
  Doip_Packet.prototype.deserialize.call(obj, buffer)
  return obj
}
module.exports.Doip_Packet = Doip_Packet


////////////////Packet: Doip_NegAck_Packet////////////////
var Doip_NegAck_Packet = function (
	code) {
	Doip_Packet.call(this)

	this.code = code
    this.payloadType = 0
}
Doip_NegAck_Packet.prototype.__proto__ = Doip_Packet.prototype
Doip_NegAck_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	Doip_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.code, parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Doip_NegAck_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.code = buffer.readUInt8(parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Doip_NegAck_Packet.prototype.createFromDoip_Packet = function (packet) {
	Doip_NegAck_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Doip_NegAck_Packet.prototype
	return packet
}

module.exports.Doip_NegAck_Packet = Doip_NegAck_Packet

////////////////Packet: Doip_VehicleReqEid_Packet////////////////
var Doip_VehicleReqEid_Packet = function (
	eid) {
	Doip_Packet.call(this)

	this.eid = eid
    this.payloadType = 2
}
Doip_VehicleReqEid_Packet.prototype.__proto__ = Doip_Packet.prototype
Doip_VehicleReqEid_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	if (this.eid != null) {
		ele_len += this.eid.length
	}
	Doip_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.copy(this.eid, parse_index)
	parse_index += 6
	this.parse_index = parse_index
}
Doip_VehicleReqEid_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.eid = Buffer.from(buffer, parse_index, 6)
	parse_index += 6
	this.parse_index = parse_index
}
Doip_VehicleReqEid_Packet.prototype.createFromDoip_Packet = function (packet) {
	Doip_VehicleReqEid_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Doip_VehicleReqEid_Packet.prototype
	return packet
}

module.exports.Doip_VehicleReqEid_Packet = Doip_VehicleReqEid_Packet

////////////////Packet: Doip_VehicleReqVin_Packet////////////////
var Doip_VehicleReqVin_Packet = function (
	vin) {
	Doip_Packet.call(this)

	this.vin = vin
    this.payloadType = 3
}
Doip_VehicleReqVin_Packet.prototype.__proto__ = Doip_Packet.prototype
Doip_VehicleReqVin_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	if (this.vin != null) {
		ele_len += this.vin.length
	}
	Doip_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.copy(this.vin, parse_index)
	parse_index += 17
	this.parse_index = parse_index
}
Doip_VehicleReqVin_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.vin = Buffer.from(buffer, parse_index, 17)
	parse_index += 17
	this.parse_index = parse_index
}
Doip_VehicleReqVin_Packet.prototype.createFromDoip_Packet = function (packet) {
	Doip_VehicleReqVin_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Doip_VehicleReqVin_Packet.prototype
	return packet
}

module.exports.Doip_VehicleReqVin_Packet = Doip_VehicleReqVin_Packet

////////////////Packet: Doip_VehicleResponse_Packet////////////////
var Doip_VehicleResponse_Packet = function (
	vin,
	addr,
	eid,
	gid,
	reserved,
	sync_state) {
	Doip_Packet.call(this)

	this.vin = vin
	this.addr = addr
	this.eid = eid
	this.gid = gid
	this.reserved = reserved
	this.sync_state = sync_state
    this.payloadType = 4
}
Doip_VehicleResponse_Packet.prototype.__proto__ = Doip_Packet.prototype
Doip_VehicleResponse_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	if (this.vin != null) {
		ele_len += this.vin.length
	}
	ele_len += 2
	if (this.eid != null) {
		ele_len += this.eid.length
	}
	if (this.gid != null) {
		ele_len += this.gid.length
	}
	ele_len += 1
	ele_len += 1
	Doip_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.copy(this.vin, parse_index)
	parse_index += 17
	buffer.writeUInt16BE(this.addr, parse_index)
	parse_index += 2
	buffer.copy(this.eid, parse_index)
	parse_index += 6
	buffer.copy(this.gid, parse_index)
	parse_index += 6
	buffer.writeUInt8(this.reserved, parse_index)
	parse_index += 1
	buffer.writeUInt8(this.sync_state, parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Doip_VehicleResponse_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.vin = Buffer.from(buffer, parse_index, 17)
	parse_index += 17
	this.addr = buffer.readUInt16BE(parse_index)
	parse_index += 2
	this.eid = Buffer.from(buffer, parse_index, 6)
	parse_index += 6
	this.gid = Buffer.from(buffer, parse_index, 6)
	parse_index += 6
	this.reserved = buffer.readUInt8(parse_index)
	parse_index += 1
	this.sync_state = buffer.readUInt8(parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Doip_VehicleResponse_Packet.prototype.createFromDoip_Packet = function (packet) {
	Doip_VehicleResponse_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Doip_VehicleResponse_Packet.prototype
	return packet
}

module.exports.Doip_VehicleResponse_Packet = Doip_VehicleResponse_Packet

////////////////Packet: Doip_RoutingActivateRequest_Packet////////////////
var Doip_RoutingActivateRequest_Packet = function (
	source_addr,
	activate_type,
	reserved_iso) {
	Doip_Packet.call(this)

	this.source_addr = source_addr
	this.activate_type = activate_type
	this.reserved_iso = reserved_iso
    this.payloadType = 5
}
Doip_RoutingActivateRequest_Packet.prototype.__proto__ = Doip_Packet.prototype
Doip_RoutingActivateRequest_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 2
	ele_len += 1
	ele_len += 4
	Doip_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt16BE(this.source_addr, parse_index)
	parse_index += 2
	buffer.writeUInt8(this.activate_type, parse_index)
	parse_index += 1
	buffer.writeUInt32BE(this.reserved_iso, parse_index)
	parse_index += 4
	this.parse_index = parse_index
}
Doip_RoutingActivateRequest_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.source_addr = buffer.readUInt16BE(parse_index)
	parse_index += 2
	this.activate_type = buffer.readUInt8(parse_index)
	parse_index += 1
	this.reserved_iso = buffer.readUInt32BE(parse_index)
	parse_index += 4
	this.parse_index = parse_index
}
Doip_RoutingActivateRequest_Packet.prototype.createFromDoip_Packet = function (packet) {
	Doip_RoutingActivateRequest_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Doip_RoutingActivateRequest_Packet.prototype
	return packet
}

module.exports.Doip_RoutingActivateRequest_Packet = Doip_RoutingActivateRequest_Packet

////////////////Packet: Doip_RoutingActivateResponse_Packet////////////////
var Doip_RoutingActivateResponse_Packet = function (
	test_addr,
	doip_addr,
	res_code,
	reserved_iso) {
	Doip_Packet.call(this)

	this.test_addr = test_addr
	this.doip_addr = doip_addr
	this.res_code = res_code
	this.reserved_iso = reserved_iso
    this.payloadType = 6
}
Doip_RoutingActivateResponse_Packet.prototype.__proto__ = Doip_Packet.prototype
Doip_RoutingActivateResponse_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 2
	ele_len += 2
	ele_len += 1
	ele_len += 4
	Doip_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt16BE(this.test_addr, parse_index)
	parse_index += 2
	buffer.writeUInt16BE(this.doip_addr, parse_index)
	parse_index += 2
	buffer.writeUInt8(this.res_code, parse_index)
	parse_index += 1
	buffer.writeUInt32BE(this.reserved_iso, parse_index)
	parse_index += 4
	this.parse_index = parse_index
}
Doip_RoutingActivateResponse_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.test_addr = buffer.readUInt16BE(parse_index)
	parse_index += 2
	this.doip_addr = buffer.readUInt16BE(parse_index)
	parse_index += 2
	this.res_code = buffer.readUInt8(parse_index)
	parse_index += 1
	this.reserved_iso = buffer.readUInt32BE(parse_index)
	parse_index += 4
	this.parse_index = parse_index
}
Doip_RoutingActivateResponse_Packet.prototype.createFromDoip_Packet = function (packet) {
	Doip_RoutingActivateResponse_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Doip_RoutingActivateResponse_Packet.prototype
	return packet
}

module.exports.Doip_RoutingActivateResponse_Packet = Doip_RoutingActivateResponse_Packet

////////////////Packet: Doip_EntityStatusResponse_Packet////////////////
var Doip_EntityStatusResponse_Packet = function (
	node_type,
	max_current_tcp,
	max_open_tcp,
	max_data_size) {
	Doip_Packet.call(this)

	this.node_type = node_type
	this.max_current_tcp = max_current_tcp
	this.max_open_tcp = max_open_tcp
	this.max_data_size = max_data_size
    this.payloadType = 16386
}
Doip_EntityStatusResponse_Packet.prototype.__proto__ = Doip_Packet.prototype
Doip_EntityStatusResponse_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	ele_len += 1
	ele_len += 1
	ele_len += 4
	Doip_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.node_type, parse_index)
	parse_index += 1
	buffer.writeUInt8(this.max_current_tcp, parse_index)
	parse_index += 1
	buffer.writeUInt8(this.max_open_tcp, parse_index)
	parse_index += 1
	buffer.writeUInt32BE(this.max_data_size, parse_index)
	parse_index += 4
	this.parse_index = parse_index
}
Doip_EntityStatusResponse_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.node_type = buffer.readUInt8(parse_index)
	parse_index += 1
	this.max_current_tcp = buffer.readUInt8(parse_index)
	parse_index += 1
	this.max_open_tcp = buffer.readUInt8(parse_index)
	parse_index += 1
	this.max_data_size = buffer.readUInt32BE(parse_index)
	parse_index += 4
	this.parse_index = parse_index
}
Doip_EntityStatusResponse_Packet.prototype.createFromDoip_Packet = function (packet) {
	Doip_EntityStatusResponse_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Doip_EntityStatusResponse_Packet.prototype
	return packet
}

module.exports.Doip_EntityStatusResponse_Packet = Doip_EntityStatusResponse_Packet

////////////////Packet: Doip_PowerModeResponse_Packet////////////////
var Doip_PowerModeResponse_Packet = function (
	mode) {
	Doip_Packet.call(this)

	this.mode = mode
    this.payloadType = 16388
}
Doip_PowerModeResponse_Packet.prototype.__proto__ = Doip_Packet.prototype
Doip_PowerModeResponse_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	Doip_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.mode, parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Doip_PowerModeResponse_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.mode = buffer.readUInt8(parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Doip_PowerModeResponse_Packet.prototype.createFromDoip_Packet = function (packet) {
	Doip_PowerModeResponse_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Doip_PowerModeResponse_Packet.prototype
	return packet
}

module.exports.Doip_PowerModeResponse_Packet = Doip_PowerModeResponse_Packet

////////////////Packet: Uds_Packet////////////////
var Uds_Packet = function (
	source_addr,
	target_addr,
	request_sid) {
	Doip_Packet.call(this)

	this.source_addr = source_addr
	this.target_addr = target_addr
	this.request_sid = request_sid
    this.payloadType = 32769
}
Uds_Packet.prototype.__proto__ = Doip_Packet.prototype
Uds_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 2
	ele_len += 2
	ele_len += 1
	Doip_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt16BE(this.source_addr, parse_index)
	parse_index += 2
	buffer.writeUInt16BE(this.target_addr, parse_index)
	parse_index += 2
	buffer.writeUInt8(this.request_sid, parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Uds_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.source_addr = buffer.readUInt16BE(parse_index)
	parse_index += 2
	this.target_addr = buffer.readUInt16BE(parse_index)
	parse_index += 2
	this.request_sid = buffer.readUInt8(parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Uds_Packet.prototype.createFromDoip_Packet = function (packet) {
	Uds_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_Packet.prototype
	return packet
}

module.exports.Uds_Packet = Uds_Packet

////////////////Packet: Doip_Uds_Packet_Pos_Ack////////////////
var Doip_Uds_Packet_Pos_Ack = function (
	source_addr,
	target_addr,
	ack_code) {
	Doip_Packet.call(this)

	this.source_addr = source_addr
	this.target_addr = target_addr
	this.ack_code = ack_code
    this.payloadType = 32770
}
Doip_Uds_Packet_Pos_Ack.prototype.__proto__ = Doip_Packet.prototype
Doip_Uds_Packet_Pos_Ack.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 2
	ele_len += 2
	ele_len += 1
	Doip_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt16BE(this.source_addr, parse_index)
	parse_index += 2
	buffer.writeUInt16BE(this.target_addr, parse_index)
	parse_index += 2
	buffer.writeUInt8(this.ack_code, parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Doip_Uds_Packet_Pos_Ack.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.source_addr = buffer.readUInt16BE(parse_index)
	parse_index += 2
	this.target_addr = buffer.readUInt16BE(parse_index)
	parse_index += 2
	this.ack_code = buffer.readUInt8(parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Doip_Uds_Packet_Pos_Ack.prototype.createFromDoip_Packet = function (packet) {
	Doip_Uds_Packet_Pos_Ack.prototype.deserialize.call(packet)
	packet.__proto__ = Doip_Uds_Packet_Pos_Ack.prototype
	return packet
}

module.exports.Doip_Uds_Packet_Pos_Ack = Doip_Uds_Packet_Pos_Ack

////////////////Packet: Doip_Uds_Packet_Neg_Ack////////////////
var Doip_Uds_Packet_Neg_Ack = function (
	source_addr,
	target_addr,
	nack_code) {
	Doip_Packet.call(this)

	this.source_addr = source_addr
	this.target_addr = target_addr
	this.nack_code = nack_code
    this.payloadType = 32771
}
Doip_Uds_Packet_Neg_Ack.prototype.__proto__ = Doip_Packet.prototype
Doip_Uds_Packet_Neg_Ack.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 2
	ele_len += 2
	ele_len += 1
	Doip_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt16BE(this.source_addr, parse_index)
	parse_index += 2
	buffer.writeUInt16BE(this.target_addr, parse_index)
	parse_index += 2
	buffer.writeUInt8(this.nack_code, parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Doip_Uds_Packet_Neg_Ack.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.source_addr = buffer.readUInt16BE(parse_index)
	parse_index += 2
	this.target_addr = buffer.readUInt16BE(parse_index)
	parse_index += 2
	this.nack_code = buffer.readUInt8(parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Doip_Uds_Packet_Neg_Ack.prototype.createFromDoip_Packet = function (packet) {
	Doip_Uds_Packet_Neg_Ack.prototype.deserialize.call(packet)
	packet.__proto__ = Doip_Uds_Packet_Neg_Ack.prototype
	return packet
}

module.exports.Doip_Uds_Packet_Neg_Ack = Doip_Uds_Packet_Neg_Ack

////////////////Packet: Uds_NegResponse_Packet////////////////
var Uds_NegResponse_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	service_code,
	res_code) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.service_code = service_code
	this.res_code = res_code
}
Uds_NegResponse_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_NegResponse_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	ele_len += 1
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.service_code, parse_index)
	parse_index += 1
	buffer.writeUInt8(this.res_code, parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Uds_NegResponse_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.service_code = buffer.readUInt8(parse_index)
	parse_index += 1
	this.res_code = buffer.readUInt8(parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Uds_NegResponse_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_NegResponse_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_NegResponse_Packet.prototype
	return packet
}

module.exports.Uds_NegResponse_Packet = Uds_NegResponse_Packet

////////////////Packet: Uds_DiagSessionControl_Packet////////////////
var Uds_DiagSessionControl_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	type,
	record) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.type = type
	this.record = record
}
Uds_DiagSessionControl_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_DiagSessionControl_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	if (this.record != null) {
		ele_len += this.record.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.type, parse_index)
	parse_index += 1
	if (this.record != null) {
		buffer.copy(this.record, parse_index)
		parse_index += this.record.length
	}
	this.parse_index = parse_index
}
Uds_DiagSessionControl_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.type = buffer.readUInt8(parse_index)
	parse_index += 1
	if (parse_index < buffer.length) {
		this.record = Buffer.from(buffer, parse_index)
		parse_index += this.record.length
	}
	this.parse_index = parse_index
}
Uds_DiagSessionControl_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_DiagSessionControl_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_DiagSessionControl_Packet.prototype
	return packet
}

module.exports.Uds_DiagSessionControl_Packet = Uds_DiagSessionControl_Packet

////////////////Packet: Uds_EcuReset_Packet////////////////
var Uds_EcuReset_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	reset_type) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.reset_type = reset_type
}
Uds_EcuReset_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_EcuReset_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.reset_type, parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Uds_EcuReset_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.reset_type = buffer.readUInt8(parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Uds_EcuReset_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_EcuReset_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_EcuReset_Packet.prototype
	return packet
}

module.exports.Uds_EcuReset_Packet = Uds_EcuReset_Packet

////////////////Packet: Uds_EcuResetPosRes_Packet////////////////
var Uds_EcuResetPosRes_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	reset_type,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.reset_type = reset_type
	this.buf = buf
}
Uds_EcuResetPosRes_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_EcuResetPosRes_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.reset_type, parse_index)
	parse_index += 1
	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_EcuResetPosRes_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.reset_type = buffer.readUInt8(parse_index)
	parse_index += 1
	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_EcuResetPosRes_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_EcuResetPosRes_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_EcuResetPosRes_Packet.prototype
	return packet
}

module.exports.Uds_EcuResetPosRes_Packet = Uds_EcuResetPosRes_Packet

////////////////Packet: Uds_SecurityAccess_Packet////////////////
var Uds_SecurityAccess_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	type,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.type = type
	this.buf = buf
}
Uds_SecurityAccess_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_SecurityAccess_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.type, parse_index)
	parse_index += 1
	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_SecurityAccess_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.type = buffer.readUInt8(parse_index)
	parse_index += 1
	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_SecurityAccess_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_SecurityAccess_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_SecurityAccess_Packet.prototype
	return packet
}

module.exports.Uds_SecurityAccess_Packet = Uds_SecurityAccess_Packet

////////////////Packet: Uds_SecurityAccessPosRes_Packet////////////////
var Uds_SecurityAccessPosRes_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	type,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.type = type
	this.buf = buf
}
Uds_SecurityAccessPosRes_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_SecurityAccessPosRes_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.type, parse_index)
	parse_index += 1
	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_SecurityAccessPosRes_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.type = buffer.readUInt8(parse_index)
	parse_index += 1
	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_SecurityAccessPosRes_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_SecurityAccessPosRes_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_SecurityAccessPosRes_Packet.prototype
	return packet
}

module.exports.Uds_SecurityAccessPosRes_Packet = Uds_SecurityAccessPosRes_Packet

////////////////Packet: Uds_ReadDataById_Packet////////////////
var Uds_ReadDataById_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	did) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.did = did
}
Uds_ReadDataById_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_ReadDataById_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 2
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt16BE(this.did, parse_index)
	parse_index += 2
	this.parse_index = parse_index
}
Uds_ReadDataById_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.did = buffer.readUInt16BE(parse_index)
	parse_index += 2
	this.parse_index = parse_index
}
Uds_ReadDataById_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_ReadDataById_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_ReadDataById_Packet.prototype
	return packet
}

module.exports.Uds_ReadDataById_Packet = Uds_ReadDataById_Packet

////////////////Packet: Uds_ReadDataByIdPosRes_Packet////////////////
var Uds_ReadDataByIdPosRes_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	did,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.did = did
	this.buf = buf
}
Uds_ReadDataByIdPosRes_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_ReadDataByIdPosRes_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 2
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt16BE(this.did, parse_index)
	parse_index += 2
	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_ReadDataByIdPosRes_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.did = buffer.readUInt16BE(parse_index)
	parse_index += 2
	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_ReadDataByIdPosRes_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_ReadDataByIdPosRes_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_ReadDataByIdPosRes_Packet.prototype
	return packet
}

module.exports.Uds_ReadDataByIdPosRes_Packet = Uds_ReadDataByIdPosRes_Packet

////////////////Packet: Uds_WriteDataById_Packet////////////////
var Uds_WriteDataById_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	did,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.did = did
	this.buf = buf
}
Uds_WriteDataById_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_WriteDataById_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 2
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt16BE(this.did, parse_index)
	parse_index += 2
	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_WriteDataById_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.did = buffer.readUInt16BE(parse_index)
	parse_index += 2
	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_WriteDataById_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_WriteDataById_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_WriteDataById_Packet.prototype
	return packet
}

module.exports.Uds_WriteDataById_Packet = Uds_WriteDataById_Packet

////////////////Packet: Uds_WriteDataByIdPosRes_Packet////////////////
var Uds_WriteDataByIdPosRes_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	did) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.did = did
}
Uds_WriteDataByIdPosRes_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_WriteDataByIdPosRes_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 2
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt16BE(this.did, parse_index)
	parse_index += 2
	this.parse_index = parse_index
}
Uds_WriteDataByIdPosRes_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.did = buffer.readUInt16BE(parse_index)
	parse_index += 2
	this.parse_index = parse_index
}
Uds_WriteDataByIdPosRes_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_WriteDataByIdPosRes_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_WriteDataByIdPosRes_Packet.prototype
	return packet
}

module.exports.Uds_WriteDataByIdPosRes_Packet = Uds_WriteDataByIdPosRes_Packet

////////////////Packet: Uds_RoutingControl_Packet////////////////
var Uds_RoutingControl_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	type,
	id,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.type = type
	this.id = id
	this.buf = buf
}
Uds_RoutingControl_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_RoutingControl_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	ele_len += 2
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.type, parse_index)
	parse_index += 1
	buffer.writeUInt16BE(this.id, parse_index)
	parse_index += 2
	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RoutingControl_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.type = buffer.readUInt8(parse_index)
	parse_index += 1
	this.id = buffer.readUInt16BE(parse_index)
	parse_index += 2
	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RoutingControl_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_RoutingControl_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_RoutingControl_Packet.prototype
	return packet
}

module.exports.Uds_RoutingControl_Packet = Uds_RoutingControl_Packet

////////////////Packet: Uds_RoutingControlPosRes_Packet////////////////
var Uds_RoutingControlPosRes_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	type,
	id,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.type = type
	this.id = id
	this.buf = buf
}
Uds_RoutingControlPosRes_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_RoutingControlPosRes_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	ele_len += 2
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.type, parse_index)
	parse_index += 1
	buffer.writeUInt16BE(this.id, parse_index)
	parse_index += 2
	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RoutingControlPosRes_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.type = buffer.readUInt8(parse_index)
	parse_index += 1
	this.id = buffer.readUInt16BE(parse_index)
	parse_index += 2
	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RoutingControlPosRes_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_RoutingControlPosRes_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_RoutingControlPosRes_Packet.prototype
	return packet
}

module.exports.Uds_RoutingControlPosRes_Packet = Uds_RoutingControlPosRes_Packet

////////////////Packet: Uds_RequestDownload_Packet////////////////
var Uds_RequestDownload_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	data_id,
	format_id,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.data_id = data_id
	this.format_id = format_id
	this.buf = buf
}
Uds_RequestDownload_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_RequestDownload_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	ele_len += 1
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.data_id, parse_index)
	parse_index += 1
	buffer.writeUInt8(this.format_id, parse_index)
	parse_index += 1
	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RequestDownload_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.data_id = buffer.readUInt8(parse_index)
	parse_index += 1
	this.format_id = buffer.readUInt8(parse_index)
	parse_index += 1
	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RequestDownload_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_RequestDownload_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_RequestDownload_Packet.prototype
	return packet
}

module.exports.Uds_RequestDownload_Packet = Uds_RequestDownload_Packet

////////////////Packet: Uds_RequestDownloadPosRes_Packet////////////////
var Uds_RequestDownloadPosRes_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	format_id,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.format_id = format_id
	this.buf = buf
}
Uds_RequestDownloadPosRes_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_RequestDownloadPosRes_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.format_id, parse_index)
	parse_index += 1
	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RequestDownloadPosRes_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.format_id = buffer.readUInt8(parse_index)
	parse_index += 1
	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RequestDownloadPosRes_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_RequestDownloadPosRes_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_RequestDownloadPosRes_Packet.prototype
	return packet
}

module.exports.Uds_RequestDownloadPosRes_Packet = Uds_RequestDownloadPosRes_Packet

////////////////Packet: Uds_TransferData_Packet////////////////
var Uds_TransferData_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	block_cnt,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.block_cnt = block_cnt
	this.buf = buf
}
Uds_TransferData_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_TransferData_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.block_cnt, parse_index)
	parse_index += 1
	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_TransferData_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.block_cnt = buffer.readUInt8(parse_index)
	parse_index += 1
	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_TransferData_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_TransferData_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_TransferData_Packet.prototype
	return packet
}

module.exports.Uds_TransferData_Packet = Uds_TransferData_Packet

////////////////Packet: Uds_TransferDataPosRes_Packet////////////////
var Uds_TransferDataPosRes_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	block_cnt,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.block_cnt = block_cnt
	this.buf = buf
}
Uds_TransferDataPosRes_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_TransferDataPosRes_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.block_cnt, parse_index)
	parse_index += 1
	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_TransferDataPosRes_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.block_cnt = buffer.readUInt8(parse_index)
	parse_index += 1
	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_TransferDataPosRes_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_TransferDataPosRes_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_TransferDataPosRes_Packet.prototype
	return packet
}

module.exports.Uds_TransferDataPosRes_Packet = Uds_TransferDataPosRes_Packet

////////////////Packet: Uds_RequestTransferExit_Packet////////////////
var Uds_RequestTransferExit_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.buf = buf
}
Uds_RequestTransferExit_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_RequestTransferExit_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RequestTransferExit_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RequestTransferExit_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_RequestTransferExit_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_RequestTransferExit_Packet.prototype
	return packet
}

module.exports.Uds_RequestTransferExit_Packet = Uds_RequestTransferExit_Packet

////////////////Packet: Uds_RequestTransferExitPosRes_Packet////////////////
var Uds_RequestTransferExitPosRes_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.buf = buf
}
Uds_RequestTransferExitPosRes_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_RequestTransferExitPosRes_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RequestTransferExitPosRes_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RequestTransferExitPosRes_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_RequestTransferExitPosRes_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_RequestTransferExitPosRes_Packet.prototype
	return packet
}

module.exports.Uds_RequestTransferExitPosRes_Packet = Uds_RequestTransferExitPosRes_Packet

////////////////Packet: Uds_RequestFileTransfer_Packet////////////////
var Uds_RequestFileTransfer_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	modeOfOperation,
	filePathAndNameLength,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.modeOfOperation = modeOfOperation
	this.filePathAndNameLength = filePathAndNameLength
	this.buf = buf
}
Uds_RequestFileTransfer_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_RequestFileTransfer_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	ele_len += 2
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.modeOfOperation, parse_index)
	parse_index += 1
	buffer.writeUInt16BE(this.filePathAndNameLength, parse_index)
	parse_index += 2
	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RequestFileTransfer_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.modeOfOperation = buffer.readUInt8(parse_index)
	parse_index += 1
	this.filePathAndNameLength = buffer.readUInt16BE(parse_index)
	parse_index += 2
	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RequestFileTransfer_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_RequestFileTransfer_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_RequestFileTransfer_Packet.prototype
	return packet
}

module.exports.Uds_RequestFileTransfer_Packet = Uds_RequestFileTransfer_Packet

////////////////Packet: Uds_RequestFileTransferPosRes_Packet////////////////
var Uds_RequestFileTransferPosRes_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	modeOfOperation,
	lengthFormatIdentifier,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.modeOfOperation = modeOfOperation
	this.lengthFormatIdentifier = lengthFormatIdentifier
	this.buf = buf
}
Uds_RequestFileTransferPosRes_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_RequestFileTransferPosRes_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	ele_len += 1
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.modeOfOperation, parse_index)
	parse_index += 1
	buffer.writeUInt8(this.lengthFormatIdentifier, parse_index)
	parse_index += 1
	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RequestFileTransferPosRes_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.modeOfOperation = buffer.readUInt8(parse_index)
	parse_index += 1
	this.lengthFormatIdentifier = buffer.readUInt8(parse_index)
	parse_index += 1
	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_RequestFileTransferPosRes_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_RequestFileTransferPosRes_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_RequestFileTransferPosRes_Packet.prototype
	return packet
}

module.exports.Uds_RequestFileTransferPosRes_Packet = Uds_RequestFileTransferPosRes_Packet

////////////////Packet: Uds_TesterPresent_Packet////////////////
var Uds_TesterPresent_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	zero) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.zero = zero
}
Uds_TesterPresent_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_TesterPresent_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.zero, parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Uds_TesterPresent_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.zero = buffer.readUInt8(parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Uds_TesterPresent_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_TesterPresent_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_TesterPresent_Packet.prototype
	return packet
}

module.exports.Uds_TesterPresent_Packet = Uds_TesterPresent_Packet

////////////////Packet: Uds_TesterPresentPosRes_Packet////////////////
var Uds_TesterPresentPosRes_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	zero) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.zero = zero
}
Uds_TesterPresentPosRes_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_TesterPresentPosRes_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.zero, parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Uds_TesterPresentPosRes_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.zero = buffer.readUInt8(parse_index)
	parse_index += 1
	this.parse_index = parse_index
}
Uds_TesterPresentPosRes_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_TesterPresentPosRes_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_TesterPresentPosRes_Packet.prototype
	return packet
}

module.exports.Uds_TesterPresentPosRes_Packet = Uds_TesterPresentPosRes_Packet

////////////////Packet: Uds_ReadDtc_Packet////////////////
var Uds_ReadDtc_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	reportType,
	buf) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.reportType = reportType
	this.buf = buf
}
Uds_ReadDtc_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_ReadDtc_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	if (this.buf != null) {
		ele_len += this.buf.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.reportType, parse_index)
	parse_index += 1
	if (this.buf != null) {
		buffer.copy(this.buf, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_ReadDtc_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.reportType = buffer.readUInt8(parse_index)
	parse_index += 1
	if (parse_index < buffer.length) {
		this.buf = Buffer.from(buffer, parse_index)
		parse_index += this.buf.length
	}
	this.parse_index = parse_index
}
Uds_ReadDtc_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_ReadDtc_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_ReadDtc_Packet.prototype
	return packet
}

module.exports.Uds_ReadDtc_Packet = Uds_ReadDtc_Packet

////////////////Packet: Uds_ClearDtc_Packet////////////////
var Uds_ClearDtc_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	group) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.group = group
}
Uds_ClearDtc_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_ClearDtc_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	if (this.group != null) {
		ele_len += this.group.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.copy(this.group, parse_index)
	parse_index += 3
	this.parse_index = parse_index
}
Uds_ClearDtc_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.group = Buffer.from(buffer, parse_index, 3)
	parse_index += 3
	this.parse_index = parse_index
}
Uds_ClearDtc_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_ClearDtc_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_ClearDtc_Packet.prototype
	return packet
}

module.exports.Uds_ClearDtc_Packet = Uds_ClearDtc_Packet

////////////////Packet: Uds_ControlDtc_Packet////////////////
var Uds_ControlDtc_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	type,
	record) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.type = type
	this.record = record
}
Uds_ControlDtc_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_ControlDtc_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	if (this.record != null) {
		ele_len += this.record.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.type, parse_index)
	parse_index += 1
	if (this.record != null) {
		buffer.copy(this.record, parse_index)
		parse_index += this.record.length
	}
	this.parse_index = parse_index
}
Uds_ControlDtc_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.type = buffer.readUInt8(parse_index)
	parse_index += 1
	if (parse_index < buffer.length) {
		this.record = Buffer.from(buffer, parse_index)
		parse_index += this.record.length
	}
	this.parse_index = parse_index
}
Uds_ControlDtc_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_ControlDtc_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_ControlDtc_Packet.prototype
	return packet
}

module.exports.Uds_ControlDtc_Packet = Uds_ControlDtc_Packet

////////////////Packet: Uds_CommunicationControl_Packet////////////////
var Uds_CommunicationControl_Packet = function (
	source_addr,
	target_addr,
	request_sid,
	controlType,
	communicationType,
	nodeIdNumber) {
	Uds_Packet.call(this,
	source_addr,
	target_addr,
	request_sid)

	this.controlType = controlType
	this.communicationType = communicationType
	this.nodeIdNumber = nodeIdNumber
}
Uds_CommunicationControl_Packet.prototype.__proto__ = Uds_Packet.prototype
Uds_CommunicationControl_Packet.prototype.serialize = function (len = 0) {
	var ele_len = len;
	ele_len += 1
	ele_len += 1
	if (this.nodeIdNumber != null) {
		ele_len += this.nodeIdNumber.length
	}
	Uds_Packet.prototype.serialize.call(this, ele_len)

	var buffer = this.buffer;
	var parse_index = this.parse_index

	buffer.writeUInt8(this.controlType, parse_index)
	parse_index += 1
	buffer.writeUInt8(this.communicationType, parse_index)
	parse_index += 1
	if (this.nodeIdNumber != null) {
		buffer.copy(this.nodeIdNumber, parse_index)
		parse_index += this.nodeIdNumber.length
	}
	this.parse_index = parse_index
}
Uds_CommunicationControl_Packet.prototype.deserialize = function () {
	var parse_index = this.parse_index
	var buffer = this.buffer

	this.controlType = buffer.readUInt8(parse_index)
	parse_index += 1
	this.communicationType = buffer.readUInt8(parse_index)
	parse_index += 1
	if (parse_index < buffer.length) {
		this.nodeIdNumber = Buffer.from(buffer, parse_index)
		parse_index += this.nodeIdNumber.length
	}
	this.parse_index = parse_index
}
Uds_CommunicationControl_Packet.prototype.createFromUds_Packet = function (packet) {
	Uds_CommunicationControl_Packet.prototype.deserialize.call(packet)
	packet.__proto__ = Uds_CommunicationControl_Packet.prototype
	return packet
}

module.exports.Uds_CommunicationControl_Packet = Uds_CommunicationControl_Packet
