#ifndef __DOIP_PACKETS_H__
#define __DOIP_PACKETS_H__
#include <memory>
#include <stdint.h>
#include <vector>

#define DOIP_TBOX_LOGICAL_ADDRESS 0x0005
#define DOIP_TBOX_FUNCTION_ADDRESS 0xE400

class Doip_Packet
{
public:
    Doip_Packet() = default;
    Doip_Packet(uint8_t *buf, uint32_t length);
    Doip_Packet(Doip_Packet&& packet);
    virtual ~Doip_Packet();
    virtual int deserialize(void);
    virtual int serialize(void);
    uint8_t protocol_version = 0x2;
    uint8_t protocol_version_inv = ~0x2;
    uint16_t payloadType = 0x0;
    uint32_t payloadLength = 0x0;
    std::vector<uint8_t> *buffer = nullptr;
    uint32_t parse_index = 0;
protected:
    const uint32_t exp_payloadLength = 8;
};

/*
 * Packet: Doip_NegAck_Packet
 */

class Doip_NegAck_Packet : public Doip_Packet
{
public:
    Doip_NegAck_Packet(
        uint8_t code);
    Doip_NegAck_Packet(Doip_NegAck_Packet &&packet);
    Doip_NegAck_Packet(Doip_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t code;
    const uint32_t exp_payloadLength = 1;
};
/*
 * Packet: Doip_VehicleReqEid_Packet
 */

class Doip_VehicleReqEid_Packet : public Doip_Packet
{
public:
    Doip_VehicleReqEid_Packet(
        std::vector<uint8_t> &&eid);
    Doip_VehicleReqEid_Packet(Doip_VehicleReqEid_Packet &&packet);
    Doip_VehicleReqEid_Packet(Doip_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    std::vector<uint8_t> eid;
    const uint32_t exp_payloadLength = 6;
};
/*
 * Packet: Doip_VehicleReqVin_Packet
 */

class Doip_VehicleReqVin_Packet : public Doip_Packet
{
public:
    Doip_VehicleReqVin_Packet(
        std::vector<uint8_t> &&vin);
    Doip_VehicleReqVin_Packet(Doip_VehicleReqVin_Packet &&packet);
    Doip_VehicleReqVin_Packet(Doip_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    std::vector<uint8_t> vin;
    const uint32_t exp_payloadLength = 17;
};
/*
 * Packet: Doip_VehicleResponse_Packet
 */

class Doip_VehicleResponse_Packet : public Doip_Packet
{
public:
    Doip_VehicleResponse_Packet(
        std::vector<uint8_t> &&vin,
        uint16_t addr,
        std::vector<uint8_t> &&eid,
        std::vector<uint8_t> &&gid,
        uint8_t reserved,
        uint8_t sync_state);
    Doip_VehicleResponse_Packet(Doip_VehicleResponse_Packet &&packet);
    Doip_VehicleResponse_Packet(Doip_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    std::vector<uint8_t> vin;
    uint16_t addr;
    std::vector<uint8_t> eid;
    std::vector<uint8_t> gid;
    uint8_t reserved;
    uint8_t sync_state;
    const uint32_t exp_payloadLength = 17 + 2 + 6 + 6 + 1 + 1;
};
/*
 * Packet: Doip_RoutingActivateRequest_Packet
 */

class Doip_RoutingActivateRequest_Packet : public Doip_Packet
{
public:
    Doip_RoutingActivateRequest_Packet(
        uint16_t source_addr,
        uint8_t activate_type,
        uint32_t reserved_iso);
    Doip_RoutingActivateRequest_Packet(Doip_RoutingActivateRequest_Packet &&packet);
    Doip_RoutingActivateRequest_Packet(Doip_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint16_t source_addr;
    uint8_t activate_type;
    uint32_t reserved_iso;
    const uint32_t exp_payloadLength = 2 + 1 + 4;
};
/*
 * Packet: Doip_RoutingActivateResponse_Packet
 */

class Doip_RoutingActivateResponse_Packet : public Doip_Packet
{
public:
    Doip_RoutingActivateResponse_Packet(
        uint16_t test_addr,
        uint16_t doip_addr,
        uint8_t res_code,
        uint32_t reserved_iso);
    Doip_RoutingActivateResponse_Packet(Doip_RoutingActivateResponse_Packet &&packet);
    Doip_RoutingActivateResponse_Packet(Doip_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint16_t test_addr;
    uint16_t doip_addr;
    uint8_t res_code;
    uint32_t reserved_iso;
    const uint32_t exp_payloadLength = 2 + 2 + 1 + 4;
};
/*
 * Packet: Doip_EntityStatusResponse_Packet
 */

class Doip_EntityStatusResponse_Packet : public Doip_Packet
{
public:
    Doip_EntityStatusResponse_Packet(
        uint8_t node_type,
        uint8_t max_current_tcp,
        uint8_t max_open_tcp,
        uint32_t max_data_size);
    Doip_EntityStatusResponse_Packet(Doip_EntityStatusResponse_Packet &&packet);
    Doip_EntityStatusResponse_Packet(Doip_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t node_type;
    uint8_t max_current_tcp;
    uint8_t max_open_tcp;
    uint32_t max_data_size;
    const uint32_t exp_payloadLength = 1 + 1 + 1 + 4;
};
/*
 * Packet: Doip_PowerModeResponse_Packet
 */

class Doip_PowerModeResponse_Packet : public Doip_Packet
{
public:
    Doip_PowerModeResponse_Packet(
        uint8_t mode);
    Doip_PowerModeResponse_Packet(Doip_PowerModeResponse_Packet &&packet);
    Doip_PowerModeResponse_Packet(Doip_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t mode;
    const uint32_t exp_payloadLength = 1;
};
/*
 * Packet: Uds_Packet
 */

class Uds_Packet : public Doip_Packet
{
public:
    Uds_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid);
    Uds_Packet(Uds_Packet &&packet);
    Uds_Packet(Doip_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint16_t source_addr;
    uint16_t target_addr;
    uint8_t request_sid;
    const uint32_t exp_payloadLength = 2 + 2 + 1;
};
/*
 * Packet: Doip_Uds_Packet_Pos_Ack
 */

class Doip_Uds_Packet_Pos_Ack : public Doip_Packet
{
public:
    Doip_Uds_Packet_Pos_Ack(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t ack_code);
    Doip_Uds_Packet_Pos_Ack(Doip_Uds_Packet_Pos_Ack &&packet);
    Doip_Uds_Packet_Pos_Ack(Doip_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint16_t source_addr;
    uint16_t target_addr;
    uint8_t ack_code;
    const uint32_t exp_payloadLength = 2 + 2 + 1;
};
/*
 * Packet: Doip_Uds_Packet_Neg_Ack
 */

class Doip_Uds_Packet_Neg_Ack : public Doip_Packet
{
public:
    Doip_Uds_Packet_Neg_Ack(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t nack_code);
    Doip_Uds_Packet_Neg_Ack(Doip_Uds_Packet_Neg_Ack &&packet);
    Doip_Uds_Packet_Neg_Ack(Doip_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint16_t source_addr;
    uint16_t target_addr;
    uint8_t nack_code;
    const uint32_t exp_payloadLength = 2 + 2 + 1;
};
/*
 * Packet: Uds_NegResponse_Packet
 */

class Uds_NegResponse_Packet : public Uds_Packet
{
public:
    Uds_NegResponse_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t service_code,
        uint8_t res_code);
    Uds_NegResponse_Packet(Uds_NegResponse_Packet &&packet);
    Uds_NegResponse_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t service_code;
    uint8_t res_code;
    const uint32_t exp_payloadLength = 1 + 1;
};
/*
 * Packet: Uds_DiagSessionControl_Packet
 */

class Uds_DiagSessionControl_Packet : public Uds_Packet
{
public:
    Uds_DiagSessionControl_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t type,
        std::vector<uint8_t> &&record);
    Uds_DiagSessionControl_Packet(Uds_DiagSessionControl_Packet &&packet);
    Uds_DiagSessionControl_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t type;
    std::vector<uint8_t> record;
    const uint32_t exp_payloadLength = 1 + 0;
};
/*
 * Packet: Uds_DiagSessionControlPosRes_Packet
 */

class Uds_DiagSessionControlPosRes_Packet : public Uds_Packet
{
public:
    Uds_DiagSessionControlPosRes_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t type,
        std::vector<uint8_t> &&record);
    Uds_DiagSessionControlPosRes_Packet(Uds_DiagSessionControlPosRes_Packet &&packet);
    Uds_DiagSessionControlPosRes_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t type;
    std::vector<uint8_t> record;
    const uint32_t exp_payloadLength = 1 + 0;
};
/*
 * Packet: Uds_EcuReset_Packet
 */

class Uds_EcuReset_Packet : public Uds_Packet
{
public:
    Uds_EcuReset_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t reset_type);
    Uds_EcuReset_Packet(Uds_EcuReset_Packet &&packet);
    Uds_EcuReset_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t reset_type;
    const uint32_t exp_payloadLength = 1;
};
/*
 * Packet: Uds_EcuResetPosRes_Packet
 */

class Uds_EcuResetPosRes_Packet : public Uds_Packet
{
public:
    Uds_EcuResetPosRes_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t reset_type,
        std::vector<uint8_t> &&buf);
    Uds_EcuResetPosRes_Packet(Uds_EcuResetPosRes_Packet &&packet);
    Uds_EcuResetPosRes_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t reset_type;
    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 1 + 0;
};
/*
 * Packet: Uds_SecurityAccess_Packet
 */

class Uds_SecurityAccess_Packet : public Uds_Packet
{
public:
    Uds_SecurityAccess_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t type,
        std::vector<uint8_t> &&buf);
    Uds_SecurityAccess_Packet(Uds_SecurityAccess_Packet &&packet);
    Uds_SecurityAccess_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t type;
    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 1 + 0;
};
/*
 * Packet: Uds_SecurityAccessPosRes_Packet
 */

class Uds_SecurityAccessPosRes_Packet : public Uds_Packet
{
public:
    Uds_SecurityAccessPosRes_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t type,
        std::vector<uint8_t> &&buf);
    Uds_SecurityAccessPosRes_Packet(Uds_SecurityAccessPosRes_Packet &&packet);
    Uds_SecurityAccessPosRes_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t type;
    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 1 + 0;
};
/*
 * Packet: Uds_ReadDataById_Packet
 */

class Uds_ReadDataById_Packet : public Uds_Packet
{
public:
    Uds_ReadDataById_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint16_t did);
    Uds_ReadDataById_Packet(Uds_ReadDataById_Packet &&packet);
    Uds_ReadDataById_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint16_t did;
    const uint32_t exp_payloadLength = 2;
};
/*
 * Packet: Uds_ReadDataByIdPosRes_Packet
 */

class Uds_ReadDataByIdPosRes_Packet : public Uds_Packet
{
public:
    Uds_ReadDataByIdPosRes_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint16_t did,
        std::vector<uint8_t> &&buf);
    Uds_ReadDataByIdPosRes_Packet(Uds_ReadDataByIdPosRes_Packet &&packet);
    Uds_ReadDataByIdPosRes_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint16_t did;
    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 2 + 0;
};
/*
 * Packet: Uds_WriteDataById_Packet
 */

class Uds_WriteDataById_Packet : public Uds_Packet
{
public:
    Uds_WriteDataById_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint16_t did,
        std::vector<uint8_t> &&buf);
    Uds_WriteDataById_Packet(Uds_WriteDataById_Packet &&packet);
    Uds_WriteDataById_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint16_t did;
    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 2 + 0;
};
/*
 * Packet: Uds_WriteDataByIdPosRes_Packet
 */

class Uds_WriteDataByIdPosRes_Packet : public Uds_Packet
{
public:
    Uds_WriteDataByIdPosRes_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint16_t did);
    Uds_WriteDataByIdPosRes_Packet(Uds_WriteDataByIdPosRes_Packet &&packet);
    Uds_WriteDataByIdPosRes_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint16_t did;
    const uint32_t exp_payloadLength = 2;
};
/*
 * Packet: Uds_RoutingControl_Packet
 */

class Uds_RoutingControl_Packet : public Uds_Packet
{
public:
    Uds_RoutingControl_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t type,
        uint16_t id,
        std::vector<uint8_t> &&buf);
    Uds_RoutingControl_Packet(Uds_RoutingControl_Packet &&packet);
    Uds_RoutingControl_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t type;
    uint16_t id;
    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 1 + 2 + 0;
};
/*
 * Packet: Uds_RoutingControlPosRes_Packet
 */

class Uds_RoutingControlPosRes_Packet : public Uds_Packet
{
public:
    Uds_RoutingControlPosRes_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t type,
        uint16_t id,
        std::vector<uint8_t> &&buf);
    Uds_RoutingControlPosRes_Packet(Uds_RoutingControlPosRes_Packet &&packet);
    Uds_RoutingControlPosRes_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t type;
    uint16_t id;
    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 1 + 2 + 0;
};
/*
 * Packet: Uds_RequestDownload_Packet
 */

class Uds_RequestDownload_Packet : public Uds_Packet
{
public:
    Uds_RequestDownload_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t data_id,
        uint8_t format_id,
        std::vector<uint8_t> &&buf);
    Uds_RequestDownload_Packet(Uds_RequestDownload_Packet &&packet);
    Uds_RequestDownload_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t data_id;
    uint8_t format_id;
    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 1 + 1 + 0;
};
/*
 * Packet: Uds_RequestDownloadPosRes_Packet
 */

class Uds_RequestDownloadPosRes_Packet : public Uds_Packet
{
public:
    Uds_RequestDownloadPosRes_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t format_id,
        std::vector<uint8_t> &&buf);
    Uds_RequestDownloadPosRes_Packet(Uds_RequestDownloadPosRes_Packet &&packet);
    Uds_RequestDownloadPosRes_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t format_id;
    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 1 + 0;
};
/*
 * Packet: Uds_TransferData_Packet
 */

class Uds_TransferData_Packet : public Uds_Packet
{
public:
    Uds_TransferData_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t block_cnt,
        std::vector<uint8_t> &&buf);
    Uds_TransferData_Packet(Uds_TransferData_Packet &&packet);
    Uds_TransferData_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t block_cnt;
    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 1 + 0;
};
/*
 * Packet: Uds_TransferDataPosRes_Packet
 */

class Uds_TransferDataPosRes_Packet : public Uds_Packet
{
public:
    Uds_TransferDataPosRes_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t block_cnt,
        std::vector<uint8_t> &&buf);
    Uds_TransferDataPosRes_Packet(Uds_TransferDataPosRes_Packet &&packet);
    Uds_TransferDataPosRes_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t block_cnt;
    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 1 + 0;
};
/*
 * Packet: Uds_RequestTransferExit_Packet
 */

class Uds_RequestTransferExit_Packet : public Uds_Packet
{
public:
    Uds_RequestTransferExit_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        std::vector<uint8_t> &&buf);
    Uds_RequestTransferExit_Packet(Uds_RequestTransferExit_Packet &&packet);
    Uds_RequestTransferExit_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 0;
};
/*
 * Packet: Uds_RequestTransferExitPosRes_Packet
 */

class Uds_RequestTransferExitPosRes_Packet : public Uds_Packet
{
public:
    Uds_RequestTransferExitPosRes_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        std::vector<uint8_t> &&buf);
    Uds_RequestTransferExitPosRes_Packet(Uds_RequestTransferExitPosRes_Packet &&packet);
    Uds_RequestTransferExitPosRes_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 0;
};
/*
 * Packet: Uds_RequestFileTransfer_Packet
 */

class Uds_RequestFileTransfer_Packet : public Uds_Packet
{
public:
    Uds_RequestFileTransfer_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t modeOfOperation,
        uint16_t filePathAndNameLength,
        std::vector<uint8_t> &&buf);
    Uds_RequestFileTransfer_Packet(Uds_RequestFileTransfer_Packet &&packet);
    Uds_RequestFileTransfer_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t modeOfOperation;
    uint16_t filePathAndNameLength;
    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 1 + 2 + 0;
};
/*
 * Packet: Uds_RequestFileTransferPosRes_Packet
 */

class Uds_RequestFileTransferPosRes_Packet : public Uds_Packet
{
public:
    Uds_RequestFileTransferPosRes_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t modeOfOperation,
        uint8_t lengthFormatIdentifier,
        std::vector<uint8_t> &&buf);
    Uds_RequestFileTransferPosRes_Packet(Uds_RequestFileTransferPosRes_Packet &&packet);
    Uds_RequestFileTransferPosRes_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t modeOfOperation;
    uint8_t lengthFormatIdentifier;
    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 1 + 1 + 0;
};
/*
 * Packet: Uds_TesterPresent_Packet
 */

class Uds_TesterPresent_Packet : public Uds_Packet
{
public:
    Uds_TesterPresent_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t zero);
    Uds_TesterPresent_Packet(Uds_TesterPresent_Packet &&packet);
    Uds_TesterPresent_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t zero;
    const uint32_t exp_payloadLength = 1;
};
/*
 * Packet: Uds_TesterPresentPosRes_Packet
 */

class Uds_TesterPresentPosRes_Packet : public Uds_Packet
{
public:
    Uds_TesterPresentPosRes_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t zero);
    Uds_TesterPresentPosRes_Packet(Uds_TesterPresentPosRes_Packet &&packet);
    Uds_TesterPresentPosRes_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t zero;
    const uint32_t exp_payloadLength = 1;
};
/*
 * Packet: Uds_ReadDtc_Packet
 */

class Uds_ReadDtc_Packet : public Uds_Packet
{
public:
    Uds_ReadDtc_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t reportType,
        std::vector<uint8_t> &&buf);
    Uds_ReadDtc_Packet(Uds_ReadDtc_Packet &&packet);
    Uds_ReadDtc_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t reportType;
    std::vector<uint8_t> buf;
    const uint32_t exp_payloadLength = 1 + 0;
};
/*
 * Packet: Uds_ClearDtc_Packet
 */

class Uds_ClearDtc_Packet : public Uds_Packet
{
public:
    Uds_ClearDtc_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        std::vector<uint8_t> &&group);
    Uds_ClearDtc_Packet(Uds_ClearDtc_Packet &&packet);
    Uds_ClearDtc_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    std::vector<uint8_t> group;
    const uint32_t exp_payloadLength = 3;
};
/*
 * Packet: Uds_ControlDtc_Packet
 */

class Uds_ControlDtc_Packet : public Uds_Packet
{
public:
    Uds_ControlDtc_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t type,
        std::vector<uint8_t> &&record);
    Uds_ControlDtc_Packet(Uds_ControlDtc_Packet &&packet);
    Uds_ControlDtc_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t type;
    std::vector<uint8_t> record;
    const uint32_t exp_payloadLength = 1 + 0;
};
/*
 * Packet: Uds_CommunicationControl_Packet
 */

class Uds_CommunicationControl_Packet : public Uds_Packet
{
public:
    Uds_CommunicationControl_Packet(
        uint16_t source_addr,
        uint16_t target_addr,
        uint8_t request_sid,
        uint8_t controlType,
        uint8_t communicationType,
        std::vector<uint8_t> &&nodeIdNumber);
    Uds_CommunicationControl_Packet(Uds_CommunicationControl_Packet &&packet);
    Uds_CommunicationControl_Packet(Uds_Packet &&packet);
    virtual int deserialize(void);
    virtual int serialize(void);

    uint8_t controlType;
    uint8_t communicationType;
    std::vector<uint8_t> nodeIdNumber;
    const uint32_t exp_payloadLength = 1 + 1 + 0;
};

class DoipRequestHandler
{
public:
    virtual int process(std::shared_ptr<Doip_Packet>, uint16_t addr) = 0;
};

class DoipResponseHandler
{
public:
    virtual int process(std::vector<uint8_t> *buf, uint16_t addr) = 0;
};
#endif
