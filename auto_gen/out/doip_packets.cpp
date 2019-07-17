#include <algorithm>
#include <arpa/inet.h>
#include "doip_packets.h"
#include <exception>
#include <string.h>

/***********************Doip_Packet****************************/
Doip_Packet::Doip_Packet(uint8_t *buf, uint32_t length)
{
    if (length < exp_payloadLength)
    {
        throw std::runtime_error("Bad doip packet");
    }
    buffer = new std::vector<uint8_t>(length);
    memcpy(buffer->data(), buf, length);
    deserialize();
}

Doip_Packet::Doip_Packet(Doip_Packet&& packet)
{
    protocol_version = packet.protocol_version;
    protocol_version_inv = packet.protocol_version_inv;
    payloadType = packet.payloadType;
    payloadLength = packet.payloadLength;
    parse_index = packet.parse_index;
    buffer = packet.buffer;
    packet.buffer = nullptr;
}

Doip_Packet::~Doip_Packet()
{
    if (buffer != nullptr)
    {
        delete buffer;
    }
}

int Doip_Packet::deserialize(void)
{
    //TBD: simple header validity check
    parse_index = 0;
    auto raw_buf = buffer->data();
    protocol_version = raw_buf[parse_index++]; 
    protocol_version_inv = raw_buf[parse_index++];
    payloadType = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;
    payloadLength = ntohl(*(uint32_t *)(raw_buf + parse_index));
    parse_index += 4;
    return 0;
}

int Doip_Packet::serialize(void)
{
    if (buffer == nullptr)
    {
        buffer = new std::vector<uint8_t>(payloadLength + 8);
    }
    else
    {
        buffer->resize(payloadLength + 8);
    }
    parse_index = 0;
    auto raw_buf = buffer->data();
    raw_buf[parse_index++] = protocol_version;
    raw_buf[parse_index++] = protocol_version_inv;
    *(uint16_t *)(raw_buf + parse_index) = htons(payloadType);
    parse_index += 2;
    *(uint32_t *)(raw_buf + parse_index) = htonl(payloadLength);
    parse_index += 4;
    return 0;
}

/*
 * Packet: Doip_NegAck_Packet
 */

Doip_NegAck_Packet::Doip_NegAck_Packet(
    uint8_t code) :
    code(code)
{
    payloadType = 0;
    payloadLength += exp_payloadLength;
}

Doip_NegAck_Packet::Doip_NegAck_Packet(Doip_NegAck_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    code = packet.code;
}

Doip_NegAck_Packet::Doip_NegAck_Packet(Doip_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Doip_NegAck_Packet");
    }
    deserialize();
}


int Doip_NegAck_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    code = raw_buf[parse_index++];

    return 0;
}

int Doip_NegAck_Packet::serialize(void)
{
    Doip_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = code;

    return 0;
}

/*
 * Packet: Doip_VehicleReqEid_Packet
 */

Doip_VehicleReqEid_Packet::Doip_VehicleReqEid_Packet(
    std::vector<uint8_t> &&eid) :
    eid(eid)
{
    payloadType = 2;
    payloadLength += exp_payloadLength;
}

Doip_VehicleReqEid_Packet::Doip_VehicleReqEid_Packet(Doip_VehicleReqEid_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    eid = packet.eid;
}

Doip_VehicleReqEid_Packet::Doip_VehicleReqEid_Packet(Doip_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Doip_VehicleReqEid_Packet");
    }
    deserialize();
}


int Doip_VehicleReqEid_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    eid.assign(buffer->begin() + parse_index, buffer->begin() +
            parse_index + 6);
    parse_index += 6;

    return 0;
}

int Doip_VehicleReqEid_Packet::serialize(void)
{
    Doip_Packet::serialize();
    auto raw_buf = buffer->data();

    memcpy(raw_buf + parse_index, eid.data(), std::min(6, (int)eid.size()));
    parse_index += 6;

    return 0;
}

/*
 * Packet: Doip_VehicleReqVin_Packet
 */

Doip_VehicleReqVin_Packet::Doip_VehicleReqVin_Packet(
    std::vector<uint8_t> &&vin) :
    vin(vin)
{
    payloadType = 3;
    payloadLength += exp_payloadLength;
}

Doip_VehicleReqVin_Packet::Doip_VehicleReqVin_Packet(Doip_VehicleReqVin_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    vin = packet.vin;
}

Doip_VehicleReqVin_Packet::Doip_VehicleReqVin_Packet(Doip_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Doip_VehicleReqVin_Packet");
    }
    deserialize();
}


int Doip_VehicleReqVin_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    vin.assign(buffer->begin() + parse_index, buffer->begin() +
            parse_index + 17);
    parse_index += 17;

    return 0;
}

int Doip_VehicleReqVin_Packet::serialize(void)
{
    Doip_Packet::serialize();
    auto raw_buf = buffer->data();

    memcpy(raw_buf + parse_index, vin.data(), std::min(17, (int)vin.size()));
    parse_index += 17;

    return 0;
}

/*
 * Packet: Doip_VehicleResponse_Packet
 */

Doip_VehicleResponse_Packet::Doip_VehicleResponse_Packet(
    std::vector<uint8_t> &&vin,
    uint16_t addr,
    std::vector<uint8_t> &&eid,
    std::vector<uint8_t> &&gid,
    uint8_t reserved,
    uint8_t sync_state) :
    vin(vin),
    addr(addr),
    eid(eid),
    gid(gid),
    reserved(reserved),
    sync_state(sync_state)
{
    payloadType = 4;
    payloadLength += exp_payloadLength;
}

Doip_VehicleResponse_Packet::Doip_VehicleResponse_Packet(Doip_VehicleResponse_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    vin = packet.vin;
    addr = packet.addr;
    eid = packet.eid;
    gid = packet.gid;
    reserved = packet.reserved;
    sync_state = packet.sync_state;
}

Doip_VehicleResponse_Packet::Doip_VehicleResponse_Packet(Doip_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Doip_VehicleResponse_Packet");
    }
    deserialize();
}


int Doip_VehicleResponse_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    vin.assign(buffer->begin() + parse_index, buffer->begin() +
            parse_index + 17);
    parse_index += 17;

    addr = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    eid.assign(buffer->begin() + parse_index, buffer->begin() +
            parse_index + 6);
    parse_index += 6;

    gid.assign(buffer->begin() + parse_index, buffer->begin() +
            parse_index + 6);
    parse_index += 6;

    reserved = raw_buf[parse_index++];

    sync_state = raw_buf[parse_index++];

    return 0;
}

int Doip_VehicleResponse_Packet::serialize(void)
{
    Doip_Packet::serialize();
    auto raw_buf = buffer->data();

    memcpy(raw_buf + parse_index, vin.data(), std::min(17, (int)vin.size()));
    parse_index += 17;

    *(uint16_t *)(raw_buf + parse_index) = htons(addr);
    parse_index += 2;

    memcpy(raw_buf + parse_index, eid.data(), std::min(6, (int)eid.size()));
    parse_index += 6;

    memcpy(raw_buf + parse_index, gid.data(), std::min(6, (int)gid.size()));
    parse_index += 6;

    raw_buf[parse_index++] = reserved;

    raw_buf[parse_index++] = sync_state;

    return 0;
}

/*
 * Packet: Doip_RoutingActivateRequest_Packet
 */

Doip_RoutingActivateRequest_Packet::Doip_RoutingActivateRequest_Packet(
    uint16_t source_addr,
    uint8_t activate_type,
    uint32_t reserved_iso) :
    source_addr(source_addr),
    activate_type(activate_type),
    reserved_iso(reserved_iso)
{
    payloadType = 5;
    payloadLength += exp_payloadLength;
}

Doip_RoutingActivateRequest_Packet::Doip_RoutingActivateRequest_Packet(Doip_RoutingActivateRequest_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    source_addr = packet.source_addr;
    activate_type = packet.activate_type;
    reserved_iso = packet.reserved_iso;
}

Doip_RoutingActivateRequest_Packet::Doip_RoutingActivateRequest_Packet(Doip_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Doip_RoutingActivateRequest_Packet");
    }
    deserialize();
}


int Doip_RoutingActivateRequest_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    source_addr = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    activate_type = raw_buf[parse_index++];

    reserved_iso = ntohl(*(uint32_t *)(raw_buf + parse_index));
    parse_index += 4;

    return 0;
}

int Doip_RoutingActivateRequest_Packet::serialize(void)
{
    Doip_Packet::serialize();
    auto raw_buf = buffer->data();

    *(uint16_t *)(raw_buf + parse_index) = htons(source_addr);
    parse_index += 2;

    raw_buf[parse_index++] = activate_type;

    *(uint32_t *)(raw_buf + parse_index) = htonl(reserved_iso);
    parse_index += 4;

    return 0;
}

/*
 * Packet: Doip_RoutingActivateResponse_Packet
 */

Doip_RoutingActivateResponse_Packet::Doip_RoutingActivateResponse_Packet(
    uint16_t test_addr,
    uint16_t doip_addr,
    uint8_t res_code,
    uint32_t reserved_iso) :
    test_addr(test_addr),
    doip_addr(doip_addr),
    res_code(res_code),
    reserved_iso(reserved_iso)
{
    payloadType = 6;
    payloadLength += exp_payloadLength;
}

Doip_RoutingActivateResponse_Packet::Doip_RoutingActivateResponse_Packet(Doip_RoutingActivateResponse_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    test_addr = packet.test_addr;
    doip_addr = packet.doip_addr;
    res_code = packet.res_code;
    reserved_iso = packet.reserved_iso;
}

Doip_RoutingActivateResponse_Packet::Doip_RoutingActivateResponse_Packet(Doip_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Doip_RoutingActivateResponse_Packet");
    }
    deserialize();
}


int Doip_RoutingActivateResponse_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    test_addr = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    doip_addr = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    res_code = raw_buf[parse_index++];

    reserved_iso = ntohl(*(uint32_t *)(raw_buf + parse_index));
    parse_index += 4;

    return 0;
}

int Doip_RoutingActivateResponse_Packet::serialize(void)
{
    Doip_Packet::serialize();
    auto raw_buf = buffer->data();

    *(uint16_t *)(raw_buf + parse_index) = htons(test_addr);
    parse_index += 2;

    *(uint16_t *)(raw_buf + parse_index) = htons(doip_addr);
    parse_index += 2;

    raw_buf[parse_index++] = res_code;

    *(uint32_t *)(raw_buf + parse_index) = htonl(reserved_iso);
    parse_index += 4;

    return 0;
}

/*
 * Packet: Doip_EntityStatusResponse_Packet
 */

Doip_EntityStatusResponse_Packet::Doip_EntityStatusResponse_Packet(
    uint8_t node_type,
    uint8_t max_current_tcp,
    uint8_t max_open_tcp,
    uint32_t max_data_size) :
    node_type(node_type),
    max_current_tcp(max_current_tcp),
    max_open_tcp(max_open_tcp),
    max_data_size(max_data_size)
{
    payloadType = 16386;
    payloadLength += exp_payloadLength;
}

Doip_EntityStatusResponse_Packet::Doip_EntityStatusResponse_Packet(Doip_EntityStatusResponse_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    node_type = packet.node_type;
    max_current_tcp = packet.max_current_tcp;
    max_open_tcp = packet.max_open_tcp;
    max_data_size = packet.max_data_size;
}

Doip_EntityStatusResponse_Packet::Doip_EntityStatusResponse_Packet(Doip_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Doip_EntityStatusResponse_Packet");
    }
    deserialize();
}


int Doip_EntityStatusResponse_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    node_type = raw_buf[parse_index++];

    max_current_tcp = raw_buf[parse_index++];

    max_open_tcp = raw_buf[parse_index++];

    max_data_size = ntohl(*(uint32_t *)(raw_buf + parse_index));
    parse_index += 4;

    return 0;
}

int Doip_EntityStatusResponse_Packet::serialize(void)
{
    Doip_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = node_type;

    raw_buf[parse_index++] = max_current_tcp;

    raw_buf[parse_index++] = max_open_tcp;

    *(uint32_t *)(raw_buf + parse_index) = htonl(max_data_size);
    parse_index += 4;

    return 0;
}

/*
 * Packet: Doip_PowerModeResponse_Packet
 */

Doip_PowerModeResponse_Packet::Doip_PowerModeResponse_Packet(
    uint8_t mode) :
    mode(mode)
{
    payloadType = 16388;
    payloadLength += exp_payloadLength;
}

Doip_PowerModeResponse_Packet::Doip_PowerModeResponse_Packet(Doip_PowerModeResponse_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    mode = packet.mode;
}

Doip_PowerModeResponse_Packet::Doip_PowerModeResponse_Packet(Doip_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Doip_PowerModeResponse_Packet");
    }
    deserialize();
}


int Doip_PowerModeResponse_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    mode = raw_buf[parse_index++];

    return 0;
}

int Doip_PowerModeResponse_Packet::serialize(void)
{
    Doip_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = mode;

    return 0;
}

/*
 * Packet: Uds_Packet
 */

Uds_Packet::Uds_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid) :
    source_addr(source_addr),
    target_addr(target_addr),
    request_sid(request_sid)
{
    payloadType = 32769;
    payloadLength += exp_payloadLength;
}

Uds_Packet::Uds_Packet(Uds_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    source_addr = packet.source_addr;
    target_addr = packet.target_addr;
    request_sid = packet.request_sid;
}

Uds_Packet::Uds_Packet(Doip_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_Packet");
    }
    deserialize();
}


int Uds_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    source_addr = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    target_addr = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    request_sid = raw_buf[parse_index++];

    return 0;
}

int Uds_Packet::serialize(void)
{
    Doip_Packet::serialize();
    auto raw_buf = buffer->data();

    *(uint16_t *)(raw_buf + parse_index) = htons(source_addr);
    parse_index += 2;

    *(uint16_t *)(raw_buf + parse_index) = htons(target_addr);
    parse_index += 2;

    raw_buf[parse_index++] = request_sid;

    return 0;
}

/*
 * Packet: Doip_Uds_Packet_Pos_Ack
 */

Doip_Uds_Packet_Pos_Ack::Doip_Uds_Packet_Pos_Ack(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t ack_code) :
    source_addr(source_addr),
    target_addr(target_addr),
    ack_code(ack_code)
{
    payloadType = 32770;
    payloadLength += exp_payloadLength;
}

Doip_Uds_Packet_Pos_Ack::Doip_Uds_Packet_Pos_Ack(Doip_Uds_Packet_Pos_Ack &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    source_addr = packet.source_addr;
    target_addr = packet.target_addr;
    ack_code = packet.ack_code;
}

Doip_Uds_Packet_Pos_Ack::Doip_Uds_Packet_Pos_Ack(Doip_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Doip_Uds_Packet_Pos_Ack");
    }
    deserialize();
}


int Doip_Uds_Packet_Pos_Ack::deserialize(void)
{
    auto raw_buf = buffer->data();

    source_addr = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    target_addr = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    ack_code = raw_buf[parse_index++];

    return 0;
}

int Doip_Uds_Packet_Pos_Ack::serialize(void)
{
    Doip_Packet::serialize();
    auto raw_buf = buffer->data();

    *(uint16_t *)(raw_buf + parse_index) = htons(source_addr);
    parse_index += 2;

    *(uint16_t *)(raw_buf + parse_index) = htons(target_addr);
    parse_index += 2;

    raw_buf[parse_index++] = ack_code;

    return 0;
}

/*
 * Packet: Doip_Uds_Packet_Neg_Ack
 */

Doip_Uds_Packet_Neg_Ack::Doip_Uds_Packet_Neg_Ack(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t nack_code) :
    source_addr(source_addr),
    target_addr(target_addr),
    nack_code(nack_code)
{
    payloadType = 32771;
    payloadLength += exp_payloadLength;
}

Doip_Uds_Packet_Neg_Ack::Doip_Uds_Packet_Neg_Ack(Doip_Uds_Packet_Neg_Ack &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    source_addr = packet.source_addr;
    target_addr = packet.target_addr;
    nack_code = packet.nack_code;
}

Doip_Uds_Packet_Neg_Ack::Doip_Uds_Packet_Neg_Ack(Doip_Packet &&packet) :
    Doip_Packet(std::forward<Doip_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Doip_Uds_Packet_Neg_Ack");
    }
    deserialize();
}


int Doip_Uds_Packet_Neg_Ack::deserialize(void)
{
    auto raw_buf = buffer->data();

    source_addr = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    target_addr = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    nack_code = raw_buf[parse_index++];

    return 0;
}

int Doip_Uds_Packet_Neg_Ack::serialize(void)
{
    Doip_Packet::serialize();
    auto raw_buf = buffer->data();

    *(uint16_t *)(raw_buf + parse_index) = htons(source_addr);
    parse_index += 2;

    *(uint16_t *)(raw_buf + parse_index) = htons(target_addr);
    parse_index += 2;

    raw_buf[parse_index++] = nack_code;

    return 0;
}

/*
 * Packet: Uds_NegResponse_Packet
 */

Uds_NegResponse_Packet::Uds_NegResponse_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t service_code,
    uint8_t res_code) :
    Uds_Packet(source_addr, target_addr, request_sid),
    service_code(service_code),
    res_code(res_code)
{
    payloadLength += exp_payloadLength;
}

Uds_NegResponse_Packet::Uds_NegResponse_Packet(Uds_NegResponse_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    service_code = packet.service_code;
    res_code = packet.res_code;
}

Uds_NegResponse_Packet::Uds_NegResponse_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_NegResponse_Packet");
    }
    deserialize();
}


int Uds_NegResponse_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    service_code = raw_buf[parse_index++];

    res_code = raw_buf[parse_index++];

    return 0;
}

int Uds_NegResponse_Packet::serialize(void)
{
    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = service_code;

    raw_buf[parse_index++] = res_code;

    return 0;
}

/*
 * Packet: Uds_DiagSessionControl_Packet
 */

Uds_DiagSessionControl_Packet::Uds_DiagSessionControl_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t type,
    std::vector<uint8_t> &&record) :
    Uds_Packet(source_addr, target_addr, request_sid),
    type(type),
    record(record)
{
    payloadLength += exp_payloadLength;
}

Uds_DiagSessionControl_Packet::Uds_DiagSessionControl_Packet(Uds_DiagSessionControl_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    type = packet.type;
    record = packet.record;
}

Uds_DiagSessionControl_Packet::Uds_DiagSessionControl_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_DiagSessionControl_Packet");
    }
    deserialize();
}


int Uds_DiagSessionControl_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    type = raw_buf[parse_index++];

    record.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_DiagSessionControl_Packet::serialize(void)
{
    payloadLength += record.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = type;

    memcpy(raw_buf + parse_index, record.data(), record.size());
    parse_index += record.size();

    return 0;
}

/*
 * Packet: Uds_DiagSessionControlPosRes_Packet
 */

Uds_DiagSessionControlPosRes_Packet::Uds_DiagSessionControlPosRes_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t type,
    std::vector<uint8_t> &&record) :
    Uds_Packet(source_addr, target_addr, request_sid),
    type(type),
    record(record)
{
    payloadLength += exp_payloadLength;
}

Uds_DiagSessionControlPosRes_Packet::Uds_DiagSessionControlPosRes_Packet(Uds_DiagSessionControlPosRes_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    type = packet.type;
    record = packet.record;
}

Uds_DiagSessionControlPosRes_Packet::Uds_DiagSessionControlPosRes_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_DiagSessionControlPosRes_Packet");
    }
    deserialize();
}


int Uds_DiagSessionControlPosRes_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    type = raw_buf[parse_index++];

    record.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_DiagSessionControlPosRes_Packet::serialize(void)
{
    payloadLength += record.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = type;

    memcpy(raw_buf + parse_index, record.data(), record.size());
    parse_index += record.size();

    return 0;
}

/*
 * Packet: Uds_EcuReset_Packet
 */

Uds_EcuReset_Packet::Uds_EcuReset_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t reset_type) :
    Uds_Packet(source_addr, target_addr, request_sid),
    reset_type(reset_type)
{
    payloadLength += exp_payloadLength;
}

Uds_EcuReset_Packet::Uds_EcuReset_Packet(Uds_EcuReset_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    reset_type = packet.reset_type;
}

Uds_EcuReset_Packet::Uds_EcuReset_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_EcuReset_Packet");
    }
    deserialize();
}


int Uds_EcuReset_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    reset_type = raw_buf[parse_index++];

    return 0;
}

int Uds_EcuReset_Packet::serialize(void)
{
    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = reset_type;

    return 0;
}

/*
 * Packet: Uds_EcuResetPosRes_Packet
 */

Uds_EcuResetPosRes_Packet::Uds_EcuResetPosRes_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t reset_type,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    reset_type(reset_type),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_EcuResetPosRes_Packet::Uds_EcuResetPosRes_Packet(Uds_EcuResetPosRes_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    reset_type = packet.reset_type;
    buf = packet.buf;
}

Uds_EcuResetPosRes_Packet::Uds_EcuResetPosRes_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_EcuResetPosRes_Packet");
    }
    deserialize();
}


int Uds_EcuResetPosRes_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    reset_type = raw_buf[parse_index++];

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_EcuResetPosRes_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = reset_type;

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_SecurityAccess_Packet
 */

Uds_SecurityAccess_Packet::Uds_SecurityAccess_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t type,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    type(type),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_SecurityAccess_Packet::Uds_SecurityAccess_Packet(Uds_SecurityAccess_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    type = packet.type;
    buf = packet.buf;
}

Uds_SecurityAccess_Packet::Uds_SecurityAccess_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_SecurityAccess_Packet");
    }
    deserialize();
}


int Uds_SecurityAccess_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    type = raw_buf[parse_index++];

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_SecurityAccess_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = type;

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_SecurityAccessPosRes_Packet
 */

Uds_SecurityAccessPosRes_Packet::Uds_SecurityAccessPosRes_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t type,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    type(type),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_SecurityAccessPosRes_Packet::Uds_SecurityAccessPosRes_Packet(Uds_SecurityAccessPosRes_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    type = packet.type;
    buf = packet.buf;
}

Uds_SecurityAccessPosRes_Packet::Uds_SecurityAccessPosRes_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_SecurityAccessPosRes_Packet");
    }
    deserialize();
}


int Uds_SecurityAccessPosRes_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    type = raw_buf[parse_index++];

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_SecurityAccessPosRes_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = type;

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_ReadDataById_Packet
 */

Uds_ReadDataById_Packet::Uds_ReadDataById_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint16_t did) :
    Uds_Packet(source_addr, target_addr, request_sid),
    did(did)
{
    payloadLength += exp_payloadLength;
}

Uds_ReadDataById_Packet::Uds_ReadDataById_Packet(Uds_ReadDataById_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    did = packet.did;
}

Uds_ReadDataById_Packet::Uds_ReadDataById_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_ReadDataById_Packet");
    }
    deserialize();
}


int Uds_ReadDataById_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    did = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    return 0;
}

int Uds_ReadDataById_Packet::serialize(void)
{
    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    *(uint16_t *)(raw_buf + parse_index) = htons(did);
    parse_index += 2;

    return 0;
}

/*
 * Packet: Uds_ReadDataByIdPosRes_Packet
 */

Uds_ReadDataByIdPosRes_Packet::Uds_ReadDataByIdPosRes_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint16_t did,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    did(did),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_ReadDataByIdPosRes_Packet::Uds_ReadDataByIdPosRes_Packet(Uds_ReadDataByIdPosRes_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    did = packet.did;
    buf = packet.buf;
}

Uds_ReadDataByIdPosRes_Packet::Uds_ReadDataByIdPosRes_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_ReadDataByIdPosRes_Packet");
    }
    deserialize();
}


int Uds_ReadDataByIdPosRes_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    did = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_ReadDataByIdPosRes_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    *(uint16_t *)(raw_buf + parse_index) = htons(did);
    parse_index += 2;

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_WriteDataById_Packet
 */

Uds_WriteDataById_Packet::Uds_WriteDataById_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint16_t did,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    did(did),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_WriteDataById_Packet::Uds_WriteDataById_Packet(Uds_WriteDataById_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    did = packet.did;
    buf = packet.buf;
}

Uds_WriteDataById_Packet::Uds_WriteDataById_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_WriteDataById_Packet");
    }
    deserialize();
}


int Uds_WriteDataById_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    did = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_WriteDataById_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    *(uint16_t *)(raw_buf + parse_index) = htons(did);
    parse_index += 2;

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_WriteDataByIdPosRes_Packet
 */

Uds_WriteDataByIdPosRes_Packet::Uds_WriteDataByIdPosRes_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint16_t did) :
    Uds_Packet(source_addr, target_addr, request_sid),
    did(did)
{
    payloadLength += exp_payloadLength;
}

Uds_WriteDataByIdPosRes_Packet::Uds_WriteDataByIdPosRes_Packet(Uds_WriteDataByIdPosRes_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    did = packet.did;
}

Uds_WriteDataByIdPosRes_Packet::Uds_WriteDataByIdPosRes_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_WriteDataByIdPosRes_Packet");
    }
    deserialize();
}


int Uds_WriteDataByIdPosRes_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    did = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    return 0;
}

int Uds_WriteDataByIdPosRes_Packet::serialize(void)
{
    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    *(uint16_t *)(raw_buf + parse_index) = htons(did);
    parse_index += 2;

    return 0;
}

/*
 * Packet: Uds_RoutingControl_Packet
 */

Uds_RoutingControl_Packet::Uds_RoutingControl_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t type,
    uint16_t id,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    type(type),
    id(id),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_RoutingControl_Packet::Uds_RoutingControl_Packet(Uds_RoutingControl_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    type = packet.type;
    id = packet.id;
    buf = packet.buf;
}

Uds_RoutingControl_Packet::Uds_RoutingControl_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_RoutingControl_Packet");
    }
    deserialize();
}


int Uds_RoutingControl_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    type = raw_buf[parse_index++];

    id = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_RoutingControl_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = type;

    *(uint16_t *)(raw_buf + parse_index) = htons(id);
    parse_index += 2;

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_RoutingControlPosRes_Packet
 */

Uds_RoutingControlPosRes_Packet::Uds_RoutingControlPosRes_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t type,
    uint16_t id,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    type(type),
    id(id),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_RoutingControlPosRes_Packet::Uds_RoutingControlPosRes_Packet(Uds_RoutingControlPosRes_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    type = packet.type;
    id = packet.id;
    buf = packet.buf;
}

Uds_RoutingControlPosRes_Packet::Uds_RoutingControlPosRes_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_RoutingControlPosRes_Packet");
    }
    deserialize();
}


int Uds_RoutingControlPosRes_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    type = raw_buf[parse_index++];

    id = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_RoutingControlPosRes_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = type;

    *(uint16_t *)(raw_buf + parse_index) = htons(id);
    parse_index += 2;

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_RequestDownload_Packet
 */

Uds_RequestDownload_Packet::Uds_RequestDownload_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t data_id,
    uint8_t format_id,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    data_id(data_id),
    format_id(format_id),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_RequestDownload_Packet::Uds_RequestDownload_Packet(Uds_RequestDownload_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    data_id = packet.data_id;
    format_id = packet.format_id;
    buf = packet.buf;
}

Uds_RequestDownload_Packet::Uds_RequestDownload_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_RequestDownload_Packet");
    }
    deserialize();
}


int Uds_RequestDownload_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    data_id = raw_buf[parse_index++];

    format_id = raw_buf[parse_index++];

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_RequestDownload_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = data_id;

    raw_buf[parse_index++] = format_id;

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_RequestDownloadPosRes_Packet
 */

Uds_RequestDownloadPosRes_Packet::Uds_RequestDownloadPosRes_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t format_id,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    format_id(format_id),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_RequestDownloadPosRes_Packet::Uds_RequestDownloadPosRes_Packet(Uds_RequestDownloadPosRes_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    format_id = packet.format_id;
    buf = packet.buf;
}

Uds_RequestDownloadPosRes_Packet::Uds_RequestDownloadPosRes_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_RequestDownloadPosRes_Packet");
    }
    deserialize();
}


int Uds_RequestDownloadPosRes_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    format_id = raw_buf[parse_index++];

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_RequestDownloadPosRes_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = format_id;

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_TransferData_Packet
 */

Uds_TransferData_Packet::Uds_TransferData_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t block_cnt,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    block_cnt(block_cnt),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_TransferData_Packet::Uds_TransferData_Packet(Uds_TransferData_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    block_cnt = packet.block_cnt;
    buf = packet.buf;
}

Uds_TransferData_Packet::Uds_TransferData_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_TransferData_Packet");
    }
    deserialize();
}


int Uds_TransferData_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    block_cnt = raw_buf[parse_index++];

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_TransferData_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = block_cnt;

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_TransferDataPosRes_Packet
 */

Uds_TransferDataPosRes_Packet::Uds_TransferDataPosRes_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t block_cnt,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    block_cnt(block_cnt),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_TransferDataPosRes_Packet::Uds_TransferDataPosRes_Packet(Uds_TransferDataPosRes_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    block_cnt = packet.block_cnt;
    buf = packet.buf;
}

Uds_TransferDataPosRes_Packet::Uds_TransferDataPosRes_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_TransferDataPosRes_Packet");
    }
    deserialize();
}


int Uds_TransferDataPosRes_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    block_cnt = raw_buf[parse_index++];

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_TransferDataPosRes_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = block_cnt;

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_RequestTransferExit_Packet
 */

Uds_RequestTransferExit_Packet::Uds_RequestTransferExit_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_RequestTransferExit_Packet::Uds_RequestTransferExit_Packet(Uds_RequestTransferExit_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    buf = packet.buf;
}

Uds_RequestTransferExit_Packet::Uds_RequestTransferExit_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_RequestTransferExit_Packet");
    }
    deserialize();
}


int Uds_RequestTransferExit_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_RequestTransferExit_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_RequestTransferExitPosRes_Packet
 */

Uds_RequestTransferExitPosRes_Packet::Uds_RequestTransferExitPosRes_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_RequestTransferExitPosRes_Packet::Uds_RequestTransferExitPosRes_Packet(Uds_RequestTransferExitPosRes_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    buf = packet.buf;
}

Uds_RequestTransferExitPosRes_Packet::Uds_RequestTransferExitPosRes_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_RequestTransferExitPosRes_Packet");
    }
    deserialize();
}


int Uds_RequestTransferExitPosRes_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_RequestTransferExitPosRes_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_RequestFileTransfer_Packet
 */

Uds_RequestFileTransfer_Packet::Uds_RequestFileTransfer_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t modeOfOperation,
    uint16_t filePathAndNameLength,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    modeOfOperation(modeOfOperation),
    filePathAndNameLength(filePathAndNameLength),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_RequestFileTransfer_Packet::Uds_RequestFileTransfer_Packet(Uds_RequestFileTransfer_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    modeOfOperation = packet.modeOfOperation;
    filePathAndNameLength = packet.filePathAndNameLength;
    buf = packet.buf;
}

Uds_RequestFileTransfer_Packet::Uds_RequestFileTransfer_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_RequestFileTransfer_Packet");
    }
    deserialize();
}


int Uds_RequestFileTransfer_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    modeOfOperation = raw_buf[parse_index++];

    filePathAndNameLength = ntohs(*(uint16_t *)(raw_buf + parse_index));
    parse_index += 2;

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_RequestFileTransfer_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = modeOfOperation;

    *(uint16_t *)(raw_buf + parse_index) = htons(filePathAndNameLength);
    parse_index += 2;

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_RequestFileTransferPosRes_Packet
 */

Uds_RequestFileTransferPosRes_Packet::Uds_RequestFileTransferPosRes_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t modeOfOperation,
    uint8_t lengthFormatIdentifier,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    modeOfOperation(modeOfOperation),
    lengthFormatIdentifier(lengthFormatIdentifier),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_RequestFileTransferPosRes_Packet::Uds_RequestFileTransferPosRes_Packet(Uds_RequestFileTransferPosRes_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    modeOfOperation = packet.modeOfOperation;
    lengthFormatIdentifier = packet.lengthFormatIdentifier;
    buf = packet.buf;
}

Uds_RequestFileTransferPosRes_Packet::Uds_RequestFileTransferPosRes_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_RequestFileTransferPosRes_Packet");
    }
    deserialize();
}


int Uds_RequestFileTransferPosRes_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    modeOfOperation = raw_buf[parse_index++];

    lengthFormatIdentifier = raw_buf[parse_index++];

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_RequestFileTransferPosRes_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = modeOfOperation;

    raw_buf[parse_index++] = lengthFormatIdentifier;

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_TesterPresent_Packet
 */

Uds_TesterPresent_Packet::Uds_TesterPresent_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t zero) :
    Uds_Packet(source_addr, target_addr, request_sid),
    zero(zero)
{
    payloadLength += exp_payloadLength;
}

Uds_TesterPresent_Packet::Uds_TesterPresent_Packet(Uds_TesterPresent_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    zero = packet.zero;
}

Uds_TesterPresent_Packet::Uds_TesterPresent_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_TesterPresent_Packet");
    }
    deserialize();
}


int Uds_TesterPresent_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    zero = raw_buf[parse_index++];

    return 0;
}

int Uds_TesterPresent_Packet::serialize(void)
{
    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = zero;

    return 0;
}

/*
 * Packet: Uds_TesterPresentPosRes_Packet
 */

Uds_TesterPresentPosRes_Packet::Uds_TesterPresentPosRes_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t zero) :
    Uds_Packet(source_addr, target_addr, request_sid),
    zero(zero)
{
    payloadLength += exp_payloadLength;
}

Uds_TesterPresentPosRes_Packet::Uds_TesterPresentPosRes_Packet(Uds_TesterPresentPosRes_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    zero = packet.zero;
}

Uds_TesterPresentPosRes_Packet::Uds_TesterPresentPosRes_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_TesterPresentPosRes_Packet");
    }
    deserialize();
}


int Uds_TesterPresentPosRes_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    zero = raw_buf[parse_index++];

    return 0;
}

int Uds_TesterPresentPosRes_Packet::serialize(void)
{
    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = zero;

    return 0;
}

/*
 * Packet: Uds_ReadDtc_Packet
 */

Uds_ReadDtc_Packet::Uds_ReadDtc_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t reportType,
    std::vector<uint8_t> &&buf) :
    Uds_Packet(source_addr, target_addr, request_sid),
    reportType(reportType),
    buf(buf)
{
    payloadLength += exp_payloadLength;
}

Uds_ReadDtc_Packet::Uds_ReadDtc_Packet(Uds_ReadDtc_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    reportType = packet.reportType;
    buf = packet.buf;
}

Uds_ReadDtc_Packet::Uds_ReadDtc_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_ReadDtc_Packet");
    }
    deserialize();
}


int Uds_ReadDtc_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    reportType = raw_buf[parse_index++];

    buf.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_ReadDtc_Packet::serialize(void)
{
    payloadLength += buf.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = reportType;

    memcpy(raw_buf + parse_index, buf.data(), buf.size());
    parse_index += buf.size();

    return 0;
}

/*
 * Packet: Uds_ClearDtc_Packet
 */

Uds_ClearDtc_Packet::Uds_ClearDtc_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    std::vector<uint8_t> &&group) :
    Uds_Packet(source_addr, target_addr, request_sid),
    group(group)
{
    payloadLength += exp_payloadLength;
}

Uds_ClearDtc_Packet::Uds_ClearDtc_Packet(Uds_ClearDtc_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    group = packet.group;
}

Uds_ClearDtc_Packet::Uds_ClearDtc_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_ClearDtc_Packet");
    }
    deserialize();
}


int Uds_ClearDtc_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    group.assign(buffer->begin() + parse_index, buffer->begin() +
            parse_index + 3);
    parse_index += 3;

    return 0;
}

int Uds_ClearDtc_Packet::serialize(void)
{
    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    memcpy(raw_buf + parse_index, group.data(), std::min(3, (int)group.size()));
    parse_index += 3;

    return 0;
}

/*
 * Packet: Uds_ControlDtc_Packet
 */

Uds_ControlDtc_Packet::Uds_ControlDtc_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t type,
    std::vector<uint8_t> &&record) :
    Uds_Packet(source_addr, target_addr, request_sid),
    type(type),
    record(record)
{
    payloadLength += exp_payloadLength;
}

Uds_ControlDtc_Packet::Uds_ControlDtc_Packet(Uds_ControlDtc_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    type = packet.type;
    record = packet.record;
}

Uds_ControlDtc_Packet::Uds_ControlDtc_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_ControlDtc_Packet");
    }
    deserialize();
}


int Uds_ControlDtc_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    type = raw_buf[parse_index++];

    record.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_ControlDtc_Packet::serialize(void)
{
    payloadLength += record.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = type;

    memcpy(raw_buf + parse_index, record.data(), record.size());
    parse_index += record.size();

    return 0;
}

/*
 * Packet: Uds_CommunicationControl_Packet
 */

Uds_CommunicationControl_Packet::Uds_CommunicationControl_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint8_t controlType,
    uint8_t communicationType,
    std::vector<uint8_t> &&nodeIdNumber) :
    Uds_Packet(source_addr, target_addr, request_sid),
    controlType(controlType),
    communicationType(communicationType),
    nodeIdNumber(nodeIdNumber)
{
    payloadLength += exp_payloadLength;
}

Uds_CommunicationControl_Packet::Uds_CommunicationControl_Packet(Uds_CommunicationControl_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    controlType = packet.controlType;
    communicationType = packet.communicationType;
    nodeIdNumber = packet.nodeIdNumber;
}

Uds_CommunicationControl_Packet::Uds_CommunicationControl_Packet(Uds_Packet &&packet) :
    Uds_Packet(std::forward<Uds_Packet>(packet))
{
    if (buffer->size() - parse_index < exp_payloadLength)
    {
        throw std::runtime_error("Bad Uds_CommunicationControl_Packet");
    }
    deserialize();
}


int Uds_CommunicationControl_Packet::deserialize(void)
{
    auto raw_buf = buffer->data();

    controlType = raw_buf[parse_index++];

    communicationType = raw_buf[parse_index++];

    nodeIdNumber.assign(buffer->begin() + parse_index, buffer->end());
    parse_index += buffer->size() - parse_index;

    return 0;
}

int Uds_CommunicationControl_Packet::serialize(void)
{
    payloadLength += nodeIdNumber.size();

    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    raw_buf[parse_index++] = controlType;

    raw_buf[parse_index++] = communicationType;

    memcpy(raw_buf + parse_index, nodeIdNumber.data(), nodeIdNumber.size());
    parse_index += nodeIdNumber.size();

    return 0;
}


#if 0
//TBD: non-auto generated code:
Uds_ReadDataByIdPosRes_Packet::Uds_ReadDataByIdPosRes_Packet(
    uint16_t source_addr,
    uint16_t target_addr,
    uint8_t request_sid,
    uint16_t did,
    std::vector<uint8_t> &&data) :
    Uds_Packet(source_addr, target_addr, request_sid),
    did(did),
    data(data)
{
    payloadLength += exp_payloadLength + data.size();
}

int Uds_ReadDataByIdPosRes_Packet::serialize(void)
{
    Uds_Packet::serialize();
    auto raw_buf = buffer->data();

    *(uint16_t *)(raw_buf + parse_index) = htons(did);
    parse_index += 2;
    data.assign(buffer->begin() + parse_index, buffer->begin() +
            parse_index + data.size());
    parse_index += data.size();

    return 0;
}
#endif
