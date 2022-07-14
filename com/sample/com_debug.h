/*
 *  TOPPERS/A-COM
 *      Automotive COM
 *
 *  Copyright (C) 2013-2015 by Center for Embedded Computing Systems
 *                             Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2014-2015 by AISIN COMCRUISE Co., Ltd., JAPAN
 *  Copyright (C) 2013-2015 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2014-2015 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2013-2015 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2014-2015 by SCSK Corporation, JAPAN
 *  Copyright (C) 2013-2015 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2013-2015 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2013-2015 by Witz Corporation
 *
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 *
 *  本ソフトウェアは，AUTOSAR（AUTomotive Open System ARchitecture）仕
 *  様に基づいている．上記の許諾は，AUTOSARの知的財産権を許諾するもので
 *  はない．AUTOSARは，AUTOSAR仕様に基づいたソフトウェアを商用目的で利
 *  用する者に対して，AUTOSARパートナーになることを求めている．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 *
 *  $Id: com_debug.h 1241 2015-03-25 07:26:02Z panasonic-ayane $
 */

#ifndef COM_DEBUG_H
#define COM_DEBUG_H

#include "Com.h"
#include "ComStack_Types.h"
#include "Com_Cfg.h"
#include "t_syslog.h"

#define dump0(str)	syslog(LOG_NOTICE, str)
#define dump1(str, arg1)	syslog(LOG_NOTICE, str, arg1)
#define dump2(str, arg1, arg2)	syslog(LOG_NOTICE, str, arg1, arg2)
#define dump3(str, arg1, arg2, arg3)	syslog(LOG_NOTICE, str, arg1, arg2, arg3)
#define dump4(str, arg1, arg2, arg3, arg4)	syslog(LOG_NOTICE, str, arg1, arg2, arg3, arg4)

LOCAL_INLINE void Debug_DumpAllConfiguration(void);
LOCAL_INLINE void Debug_DumpIpduGroup(PduIdType ipduGroupId);
LOCAL_INLINE void Debug_DumpAllIpdu(void);
LOCAL_INLINE void Debug_DumpIpdu(PduIdType PduId);
LOCAL_INLINE void Debug_DumpAllSignal(void);
LOCAL_INLINE void Debug_DumpSignal(Com_SignalIdType PduId);
LOCAL_INLINE char8 *Debug_PrintBits(void *p_data, uint8 size);

LOCAL_INLINE const char8 *
a_com_boolean_str(boolean val)
{
	if (val) {
		return("TRUE");
	}
	else {
		return("FALSE");
	}
}

LOCAL_INLINE const char8 *
a_com_param_str(uint32 val)
{
	switch (val) {
	case COM_ALWAYS:									return("COM_ALWAYS");
	case COM_MASKED_NEW_DIFFERS_MASKED_OLD:				return("COM_MASKED_NEW_DIFFERS_MASKED_OLD");
	case COM_MASKED_NEW_DIFFERS_X:						return("COM_MASKED_NEW_DIFFERS_X");
	case COM_MASKED_NEW_EQUALS_X:						return("COM_MASKED_NEW_EQUALS_X");
	case COM_NEVER:										return("COM_NEVER");
	case COM_NEW_IS_OUTSIDE:							return("COM_NEW_IS_OUTSIDE");
	case COM_NEW_IS_WITHIN:								return("COM_NEW_IS_WITHIN");
	case COM_ONE_EVERY_N:								return("COM_ONE_EVERY_N");
	case COM_SEND:										return("COM_SEND");
	case COM_RECEIVE:									return("COM_RECEIVE");
	case COM_DEFERRED:									return("COM_DEFERRED");
	case COM_IMMEDIATE:									return("COM_IMMEDIATE");
	case COM_CONFIRMATION:								return("COM_CONFIRMATION");
	case COM_TRANSMIT:									return("COM_TRANSMIT");
	case COM_TRIGGER_TRANSMIT:							return("COM_TRIGGER_TRANSMIT");
	case COM_NOTIFY:									return("COM_NOTIFY");
	case COM_REPLACE:									return("COM_REPLACE");
	case COM_NONE:										return("COM_NONE");
	case COM_BIG_ENDIAN:								return("COM_BIG_ENDIAN");
	case COM_LITTLE_ENDIAN:								return("COM_LITTLE_ENDIAN");
	case COM_OPAQUE:									return("COM_OPAQUE");
	case COM_BOOLEAN:									return("COM_BOOLEAN");
	case COM_SINT8:										return("COM_SINT8");
	case COM_SINT16:									return("COM_SINT16");
	case COM_SINT32:									return("COM_SINT32");
	case COM_UINT8:										return("COM_UINT8");
	case COM_UINT16:									return("COM_UINT16");
	case COM_UINT32:									return("COM_UINT32");
	case COM_UINT8_N:									return("COM_UINT8_N");
	case COM_UINT8_DYN:									return("COM_UINT8_DYN");
	case COM_FLOAT32:									return("COM_FLOAT32");
	case COM_FLOAT64:									return("COM_FLOAT64");
	case COM_PENDING:									return("COM_PENDING");
	case COM_TRIGGERED:									return("COM_TRIGGERED");
	case COM_TRIGGERED_ON_CHANGE:						return("COM_TRIGGERED_ON_CHANGE");
	case COM_TRIGGERED_ON_CHANGE_WITHOUT_REPETITION:	return("COM_TRIGGERED_ON_CHANGE_WITHOUT_REPETITION");
	case COM_TRIGGERED_WITHOUT_REPETITION:				return("COM_TRIGGERED_WITHOUT_REPETITION");
	case COM_DIRECT:									return("COM_DIRECT");
	case COM_PERIODIC:									return("COM_PERIODIC");
	case COM_MIXED:										return("COM_MIXED");
	case COM_NORMAL:									return("COM_NORMAL");
	case COM_TP:										return("COM_TP");
	case COM_INVALID_UINT8:								return("COM_INVALID_UINT8");
	case COM_INVALID_UINT16:							return("COM_INVALID_UINT16");
	case COM_INVALID_UINT32:							return("COM_INVALID_UINT32");
	default:
		dump2("## Fatal Error!![%s:%d]", __FILE__, __LINE__);
		break;
	}
	return("Error");
}

LOCAL_INLINE void
Debug_DumpAllConfiguration(void)
{
	dump0("==========================================");
	dump0(" Debug_DumpAllConfiguration");
	dump0("==========================================");
	dump1("ComConfigurationId: %d", p_cur_com_config->ComConfigurationId);
	dump1("tnum_signal: %d", GET_SIGNAL_NUM());
	dump1("tnum_vector: %d", GET_VECTOR_NUM());
	dump1("tnum_ipdu_g: %d", GET_IPDU_G_NUM());
	dump1("tnum_ipdu: %d", GET_IPDU_NUM());
	dump1("tnum_rx_ipdu: %d", GET_RX_IPDU_NUM());
	dump1("tnum_tx_ipdu: %d", GET_TX_IPDU_NUM());
	dump0("");
}

LOCAL_INLINE void
Debug_DumpIpduGroup(PduIdType ipduGroupId)
{
	PduIdType	i, cnt;
	uint8		vector, pos, mask;

	dump0("==========================================");
	dump0(" Debug_DumpIpduGroup");
	dump0("==========================================");
	dump1("----- IPDU-GROUP-ID: %d -----", ipduGroupId);

	pos = ipduGroupId % 8U;
	mask = 1U << pos;
	cnt = 0U;
	for (i = 0U; i < GET_IPDU_NUM(); i++) {
		vector = (*(GET_IPDU_INIB(i)->p_ipdu_group_vector))[ipduGroupId / 8U];
		if ((vector & mask) != 0U) {
			cnt++;
		}
	}
	dump1("IPDU num: %d", cnt);
	dump0("");
}

LOCAL_INLINE void
Debug_DumpAllIpdu(void)
{
	PduIdType i;

	dump0("==========================================");
	dump0(" Debug_DumpAllIpdu");
	dump0("==========================================");
	for (i = 0U; i < GET_IPDU_NUM(); i++) {
		Debug_DumpIpdu(i);
	}
	dump0("");
}

LOCAL_INLINE void
Debug_DumpIpdu(PduIdType PduId)
{
	PduIdType			i;
	const IPDU_INIB		*p_ipdu_inib;
	const TX_IPDU_CB	*p_tx_ipdu_cb;
	const TX_IPDU_INIB	*p_tx_ipdu_inib = NULL_PTR;
	const TX_MODE_INIB	*p_cur_tx_mode_inib;

	dump0("==========================================");
	dump1(" Debug_DumpIpdu (IPDU-ID: %d)", PduId);
	dump0("==========================================");

	p_ipdu_inib = GET_IPDU_INIB(PduId);

	dump1("ComIPduCancellationSupport: %s", a_com_boolean_str(p_ipdu_inib->ComIPduCancellationSupport));
	dump1("ComIPduDirection: %s", a_com_param_str(p_ipdu_inib->ComIPduDirection));
	dump1("ComIPduSignalProcessing: %s", a_com_param_str(p_ipdu_inib->ComIPduSignalProcessing));
	if (p_ipdu_inib->p_tx_ipdu_inib != NULL_PTR) {
		p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
		dump1("ComMinimumDelayTime: %d", p_tx_ipdu_inib->ComMinimumDelayTime);
		dump1("ComTxIPduClearUpdateBit: %s", a_com_param_str(p_tx_ipdu_inib->ComTxIPduClearUpdateBit));
		dump1("ComTxIPduUnusedAreasDefault: 0x%x", p_tx_ipdu_inib->ComTxIPduUnusedAreasDefault);
	}
	dump1("PduRSourcePduHandleId: %x", p_ipdu_inib->PduRSourcePduHandleId);
	dump1("PduLength: %d", p_ipdu_inib->PduLength);
	dump1("tnum_signal: %d", p_ipdu_inib->tnum_signal);
	for (i = 0U; i < p_ipdu_inib->PduLength; i++) {
		dump3("p_ipdu_buffer[%02d]: %s (0x%x)", i,
			  Debug_PrintBits(&(p_ipdu_inib->p_ipdu_buffer)[i], 8U),
			  (p_ipdu_inib->p_ipdu_buffer)[i]);
		Debug_PrintBits(&(p_ipdu_inib->p_ipdu_buffer)[i], 8U);
	}

	for (i = 0U; i < ((GET_IPDU_G_NUM() / 8U) + 1U); i++) {
		dump3("p_ipdu_group_vector[%d]: %s (0x%x)", i,
			  Debug_PrintBits(&((p_ipdu_inib->p_ipdu_group_vector)[i]), 8U),
			  (*(p_ipdu_inib->p_ipdu_group_vector))[i]);
	}

	dump1("IPDU_IS_STARTED(p_state): %s", a_com_boolean_str(IPDU_IS_STARTED(p_ipdu_inib->p_state)));
	dump1("IPDU_IS_UPDATED(p_state): %s", a_com_boolean_str(IPDU_IS_UPDATED(p_ipdu_inib->p_state)));
	dump1("IPDU_IS_NOTICED(p_state): %s", a_com_boolean_str(IPDU_IS_NOTICED(p_ipdu_inib->p_state)));
	dump1("IPDU_IS_DIRECT_RETRITED(p_state): %s", a_com_boolean_str(IPDU_IS_DIRECT_RETRITED(p_ipdu_inib->p_state)));
	dump1("IPDU_IS_PEROODIC_RETRITED(p_state): %s", a_com_boolean_str(IPDU_IS_PERIODIC_RETRITED(p_ipdu_inib->p_state)));
	dump1("IPDU_IS_TRIGGER_RETRITED(p_state): %s", a_com_boolean_str(IPDU_IS_TRIGGER_RETRITED(p_ipdu_inib->p_state)));
	dump1("IPDU_IS_WITHOUT_REPETITION(p_state): %s", a_com_boolean_str(IPDU_IS_WITHOUT_REPETITION(p_ipdu_inib->p_state)));
	dump1("IPDU_IS_DM(p_state): %s", a_com_boolean_str(IPDU_IS_DM(p_ipdu_inib->p_state)));

	if (p_ipdu_inib->ComIPduDirection == COM_SEND) {
		p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
		dump1("repeat_cnt: %d", p_tx_ipdu_cb->repeat_cnt);
		dump1("interval_mf_cnt: %d", p_tx_ipdu_cb->interval_mf_cnt);
		dump1("period_mf_cnt: %d", p_tx_ipdu_cb->period_mf_cnt);
		dump1("mdt_mf_cnt: %d", p_tx_ipdu_cb->mdt_mf_cnt);
		p_cur_tx_mode_inib = p_tx_ipdu_cb->p_cur_tx_mode_inib;
		dump1("ComTxModeMode: %s", a_com_param_str(p_cur_tx_mode_inib->ComTxModeMode));
		dump1("ComTxModeNumberOfRepetitions: %d", p_cur_tx_mode_inib->ComTxModeNumberOfRepetitions);
		dump1("ComTxModeRepetitionPeriod: %d", p_cur_tx_mode_inib->ComTxModeRepetitionPeriod);
		dump1("ComTxModeTimeOffset: %d", p_cur_tx_mode_inib->ComTxModeTimeOffset);
		dump1("ComTxModeTimePeriod: %d", p_cur_tx_mode_inib->ComTxModeTimePeriod);
		if ((p_tx_ipdu_inib != NULL_PTR) && (p_cur_tx_mode_inib == p_tx_ipdu_inib->p_tx_mode_true_inib)) {
			dump0("tx_mode: TRUE");
		}
		else {
			dump0("tx_mode: FALSE");
		}
	}

	dump0("");
}

LOCAL_INLINE void
Debug_DumpAllSignal(void)
{
	Com_SignalIdType i;

	dump0("==========================================");
	dump0(" Debug_DumpAllSignal");
	dump0("==========================================");
	for (i = 0U; i < GET_SIGNAL_NUM(); i++) {
		Debug_DumpSignal(i);
	}
	dump0("");
}

LOCAL_INLINE void
Debug_DumpSignal(Com_SignalIdType SignalId)
{
	uint16				i;
	const SIGNAL_INIB	*p_signal_inib;
	const FILTER_INIB	*p_filter_inib;

	dump0("==========================================");
	dump1(" Debug_DumpSignal (SIGNAL-ID: %d)", SignalId);
	dump0("==========================================");

	p_signal_inib = GET_SIGNAL_INIB(SignalId);

	dump1("ComBitPosition: %d", p_signal_inib->ComBitPosition);
	dump1("ComBitSize: %d", p_signal_inib->ComBitSize);
	dump1("ComDataInvalidAction: %s", a_com_param_str(p_signal_inib->ComDataInvalidAction));
	dump1("ComFirstTimeout: %d", p_signal_inib->ComFirstTimeout);
	dump1("ComRxDataTimeoutAction: %s", a_com_param_str(p_signal_inib->ComRxDataTimeoutAction));

	switch (p_signal_inib->ComSignalType) {
	case COM_BOOLEAN:
		if (p_signal_inib->ComSignalDataInvalidValue != NULL_PTR) {
			dump1("ComSignalDataInvalidValue: %d", *(boolean *) p_signal_inib->ComSignalDataInvalidValue);
		}
		else {
			dump0("ComSignalDataInvalidValue: NULL_PTR");
		}
		dump1("ComSignalInitValue: %d", *(boolean *) p_signal_inib->ComSignalInitValue);
		break;
	case COM_SINT8:
		if (p_signal_inib->ComSignalDataInvalidValue != NULL_PTR) {
			dump1("ComSignalDataInvalidValue: %d", *(sint8 *) p_signal_inib->ComSignalDataInvalidValue);
		}
		else {
			dump0("ComSignalDataInvalidValue: NULL_PTR");
		}
		dump1("ComSignalInitValue: %d", *(sint8 *) p_signal_inib->ComSignalInitValue);
		break;
	case COM_SINT16:
		if (p_signal_inib->ComSignalDataInvalidValue != NULL_PTR) {
			dump1("ComSignalDataInvalidValue: %d", *(sint16 *) p_signal_inib->ComSignalDataInvalidValue);
		}
		else {
			dump0("ComSignalDataInvalidValue: NULL_PTR");
		}
		dump1("ComSignalInitValue: %d", *(sint16 *) p_signal_inib->ComSignalInitValue);
		break;
	case COM_SINT32:
		if (p_signal_inib->ComSignalDataInvalidValue != NULL_PTR) {
			dump1("ComSignalDataInvalidValue: %d", *(sint32 *) p_signal_inib->ComSignalDataInvalidValue);
		}
		else {
			dump0("ComSignalDataInvalidValue: NULL_PTR");
		}
		dump1("ComSignalInitValue: %d", *(sint32 *) p_signal_inib->ComSignalInitValue);
		break;
	case COM_UINT8:
		if (p_signal_inib->ComSignalDataInvalidValue != NULL_PTR) {
			dump1("ComSignalDataInvalidValue: %d", *(uint8 *) p_signal_inib->ComSignalDataInvalidValue);
		}
		else {
			dump0("ComSignalDataInvalidValue: NULL_PTR");
		}
		dump1("ComSignalInitValue: %d", *(uint8 *) p_signal_inib->ComSignalInitValue);
		break;
	case COM_UINT16:
		if (p_signal_inib->ComSignalDataInvalidValue != NULL_PTR) {
			dump1("ComSignalDataInvalidValue: %d", *(uint16 *) p_signal_inib->ComSignalDataInvalidValue);
		}
		else {
			dump0("ComSignalDataInvalidValue: NULL_PTR");
		}
		dump1("ComSignalInitValue: %d", *(uint16 *) p_signal_inib->ComSignalInitValue);
		break;
	case COM_UINT32:
		if (p_signal_inib->ComSignalDataInvalidValue != NULL_PTR) {
			dump1("ComSignalDataInvalidValue: %d", *(uint32 *) p_signal_inib->ComSignalDataInvalidValue);
		}
		else {
			dump0("ComSignalDataInvalidValue: NULL_PTR");
		}
		dump1("ComSignalInitValue: %d", *(uint32 *) p_signal_inib->ComSignalInitValue);
		break;
	case COM_UINT8_N:
		if (p_signal_inib->ComSignalDataInvalidValue == NULL_PTR) {
			dump0("ComSignalDataInvalidValue: NULL_PTR");
		}
		for (i = 0U; i < p_signal_inib->ComSignalLength; i++) {
			if (p_signal_inib->ComSignalDataInvalidValue != NULL_PTR) {
				dump2("ComSignalDataInvalidValue[%d]: %d", i, ((uint8 *) p_signal_inib->ComSignalDataInvalidValue)[i]);
			}
			dump2("ComSignalInitValue[%d]: %d", i, ((uint8 *) p_signal_inib->ComSignalInitValue)[i]);
		}
		break;
	case COM_FLOAT32:
		if (p_signal_inib->ComSignalDataInvalidValue != NULL_PTR) {
			dump1("ComSignalDataInvalidValue: %d", *(uint32 *) p_signal_inib->ComSignalDataInvalidValue);
		}
		else {
			dump0("ComSignalDataInvalidValue: NULL_PTR");
		}
		dump1("ComSignalInitValue: %d", *(uint32 *) p_signal_inib->ComSignalInitValue);
		break;
	case COM_FLOAT64:
		if (p_signal_inib->ComSignalDataInvalidValue != NULL_PTR) {
			dump1("ComSignalDataInvalidValue: %d", *(uint64 *) p_signal_inib->ComSignalDataInvalidValue);
		}
		else {
			dump0("ComSignalDataInvalidValue: NULL_PTR");
		}
		dump1("ComSignalInitValue: %d", *(uint64 *) p_signal_inib->ComSignalInitValue);
		break;
	default:
		break;
	}

	dump1("ComSignalEndianness: %s", a_com_param_str(p_signal_inib->ComSignalEndianness));
	dump1("ComSignalLength: %d", p_signal_inib->ComSignalLength);
	dump1("ComSignalType: %s", a_com_param_str(p_signal_inib->ComSignalType));
	dump1("ComTimeout: %d", p_signal_inib->ComTimeout);
	dump1("ComTransferProperty: %s", a_com_param_str(p_signal_inib->ComTransferProperty));
	dump1("ComUpdateBitPosition: %d", p_signal_inib->ComUpdateBitPosition);

	if (p_signal_inib->p_signal_buffer != NULL_PTR) {
		switch (p_signal_inib->ComSignalType) {
		case COM_BOOLEAN:
			dump1("p_signal_buffer: %s", a_com_boolean_str(*(boolean *) p_signal_inib->p_signal_buffer));
			break;
		case COM_SINT8:
			dump2("p_signal_buffer: %s (0x%x)", Debug_PrintBits(&(*(sint8 *) p_signal_inib->p_signal_buffer), 8U),
				  *(sint8 *) p_signal_inib->p_signal_buffer);
			break;
		case COM_SINT16:
			dump2("p_signal_buffer: %s (0x%x)", Debug_PrintBits(&(*(sint16 *) p_signal_inib->p_signal_buffer), 16U),
				  *(sint16 *) p_signal_inib->p_signal_buffer);
			break;
		case COM_SINT32:
			dump2("p_signal_buffer: %s (0x%x)", Debug_PrintBits(&(*(sint32 *) p_signal_inib->p_signal_buffer), 32U),
				  *(sint32 *) p_signal_inib->p_signal_buffer);
			break;
		case COM_UINT8:
			dump2("p_signal_buffer: %s (0x%x)", Debug_PrintBits(&(*(uint8 *) p_signal_inib->p_signal_buffer), 8U),
				  *(uint8 *) p_signal_inib->p_signal_buffer);
			break;
		case COM_UINT16:
			dump2("p_signal_buffer: %s (0x%x)", Debug_PrintBits(&(*(uint16 *) p_signal_inib->p_signal_buffer), 16U),
				  *(uint16 *) p_signal_inib->p_signal_buffer);
			break;
		case COM_UINT32:
			dump2("p_signal_buffer: %s (0x%x)", Debug_PrintBits(&(*(uint32 *) p_signal_inib->p_signal_buffer), 32U),
				  *(uint32 *) p_signal_inib->p_signal_buffer);
			break;
		case COM_UINT8_N:
			for (i = 0U; i < p_signal_inib->ComSignalLength; i++) {
				dump3("p_signal_buffer[%d]: %s (0x%x)", i,
					  Debug_PrintBits(&(((uint8 *) p_signal_inib->p_signal_buffer)[i]), 8U),
					  ((uint8 *) p_signal_inib->p_signal_buffer)[i]);
			}
			break;
		case COM_FLOAT32:
			dump2("p_signal_buffer: %s (0x%x)", Debug_PrintBits(&(*(float32 *) p_signal_inib->p_signal_buffer), 32U),
				  *(float32 *) p_signal_inib->p_signal_buffer);
			break;
		case COM_FLOAT64:
			dump2("p_signal_buffer: %s (0x%x)", Debug_PrintBits(&(*(float64 *) p_signal_inib->p_signal_buffer), 64U),
				  *(float64 *) p_signal_inib->p_signal_buffer);
			break;
		default:
			/* todo */
			break;
		}
	}

	if (p_signal_inib->p_filter_inib != NULL_PTR) {
		p_filter_inib = p_signal_inib->p_filter_inib;
		dump1("ComFilterAlgorithm: %s", a_com_param_str(p_filter_inib->ComFilterAlgorithm));
		dump1("ComFilterMask: %d", p_filter_inib->ComFilterMask);
		dump1("ComFilterMax: %d", p_filter_inib->ComFilterMax);
		dump1("ComFilterMin: %d", p_filter_inib->ComFilterMin);
		dump1("ComFilterOffset: %d", p_filter_inib->ComFilterOffset);
		dump1("ComFilterPeriod: %d", p_filter_inib->ComFilterPeriod);
		dump1("ComFilterX: %d", p_filter_inib->ComFilterX);
		switch (p_signal_inib->ComSignalType) {
		case COM_BOOLEAN:
			dump1("p_filter_buffer: %s", a_com_boolean_str(*(boolean *) p_filter_inib->p_filter_buffer));
			break;
		case COM_SINT8:
			dump2("p_filter_buffer: %s (0x%x)", Debug_PrintBits(&(*(sint8 *) p_filter_inib->p_filter_buffer), 8U),
				  *(sint8 *) p_filter_inib->p_filter_buffer);
			break;
		case COM_SINT16:
			dump2("p_filter_buffer: %s (0x%x)", Debug_PrintBits(&(*(sint16 *) p_filter_inib->p_filter_buffer), 16U),
				  *(sint16 *) p_filter_inib->p_filter_buffer);
			break;
		case COM_SINT32:
			dump2("p_filter_buffer: %s (0x%x)", Debug_PrintBits(&(*(sint32 *) p_filter_inib->p_filter_buffer), 32U),
				  *(sint32 *) p_filter_inib->p_filter_buffer);
			break;
		case COM_UINT8:
			dump2("p_filter_buffer: %s (0x%x)", Debug_PrintBits(&(*(uint8 *) p_filter_inib->p_filter_buffer), 8U),
				  *(uint8 *) p_filter_inib->p_filter_buffer);
			break;
		case COM_UINT16:
			dump2("p_filter_buffer: %s (0x%x)", Debug_PrintBits(&(*(uint16 *) p_filter_inib->p_filter_buffer), 16U),
				  *(uint16 *) p_filter_inib->p_filter_buffer);
			break;
		case COM_UINT32:
			dump2("p_filter_buffer: %s (0x%x)", Debug_PrintBits(&(*(uint32 *) p_filter_inib->p_filter_buffer), 32U),
				  *(uint32 *) p_filter_inib->p_filter_buffer);
			break;
		case COM_UINT8_N:
			for (i = 0U; i < p_signal_inib->ComSignalLength; i++) {
				dump3("p_filter_buffer[%d]: %s (0x%x)", i,
					  Debug_PrintBits(&(((uint8 *) p_filter_inib->p_filter_buffer)[i]), 8U),
					  ((uint8 *) p_filter_inib->p_filter_buffer)[i]);
			}
			break;
		case COM_FLOAT32:
			dump2("p_filter_buffer: %s (0x%x)", Debug_PrintBits(&(*(float32 *) p_filter_inib->p_filter_buffer), 32U),
				  *(float32 *) p_filter_inib->p_filter_buffer);
			break;
		case COM_FLOAT64:
			dump2("p_filter_buffer: %s (0x%x)", Debug_PrintBits(&(*(float64 *) p_filter_inib->p_filter_buffer), 64U),
				  *(float64 *) p_filter_inib->p_filter_buffer);
			break;
		default:
			break;
		}

	}

	dump0("");
}

LOCAL_INLINE char8 *
Debug_PrintBits(void *p_data, uint8 size)
{
	uint32			i, mask;
	uint32			udata1 = 0U;
	uint32			udata2 = 0U;
	static char8	str[65];

	for (i = 0U; i < 65U; i++) {
		str[i] = 0;
	}

	if (size == 64U) {
		udata1 = (uint32) (((*((uint64 *) p_data)) >> 32U) & 0xFFFFFFFFU);
		udata2 = (uint32) ((*((uint64 *) p_data)) & 0xFFFFFFFFU);
	}
	else if (size == 8U) {
		udata1 = (uint32) (*((uint8 *) p_data));
	}
	else if (size == 16U) {
		udata1 = (uint32) (*((uint16 *) p_data));
	}
	else {
		udata1 = *((uint32 *) p_data);
	}

	if (size != 64U) {
		for (i = 0U; i < size; i++) {
			mask = 1U << i;
			if ((udata1 & mask) != 0U) {
				str[size - 1U - i] = 0x31;
			}
			else {
				str[size - 1U - i] = 0x30;
			}
		}
	}
	else {
		for (i = 0U; i < 32U; i++) {
			mask = 1U << i;
			if ((udata1 & mask) != 0U) {
				str[32U - 1U - i] = 0x31;
			}
			else {
				str[32U - 1U - i] = 0x30;
			}
			if ((udata2 & mask) != 0U) {
				str[64U - 1U - i] = 0x31;
			}
			else {
				str[64U - 1U - i] = 0x30;
			}
		}
	}

	return(str);
}

#endif /* COM_DEBUG_H */
