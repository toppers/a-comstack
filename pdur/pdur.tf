$
$  TOPPERS/A-PDUR
$      AuTomotive PDUR
$
$  Copyright (C) 2013-2014 by Center for Embedded Computing Systems
$              Graduate School of Information Science, Nagoya Univ., JAPAN
$  Copyright (C) 2013-2014 by FUJI SOFT INCORPORATED, JAPAN
$  Copyright (C) 2013-2014 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
$  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
$  Copyright (C) 2013-2014 by Sunny Giken Inc., JAPAN
$  Copyright (C) 2013-2014 by TOSHIBA CORPORATION, JAPAN
$  Copyright (C) 2013-2014 by Witz Corporation, JAPAN
$
$  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
$  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
$  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
$  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
$      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
$      ����������˴ޤޤ�Ƥ��뤳�ȡ�
$  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
$      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
$      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
$      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
$  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
$      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
$      �ȡ�
$    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
$        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
$    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
$        ��𤹤뤳�ȡ�
$  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
$      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
$      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
$      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
$      ���դ��뤳�ȡ�
$
$  �ܥ��եȥ������ϡ�AUTOSAR��AUTomotive Open System ARchitecture�˻�
$  �ͤ˴�Ť��Ƥ��롥�嵭�ε����ϡ�AUTOSAR����Ū�⻺������������Τ�
$  �Ϥʤ���AUTOSAR�ϡ�AUTOSAR���ͤ˴�Ť������եȥ�����������Ū����
$  �Ѥ���Ԥ��Ф��ơ�AUTOSAR�ѡ��ȥʡ��ˤʤ뤳�Ȥ���Ƥ��롥
$
$  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
$  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
$  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
$  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
$  ����Ǥ�����ʤ���
$
$  $Id: pdur.tf 425 2014-09-17 00:46:01Z fsi-dankei $
$

$ =====================================================================
$ booleanȽ��ؿ�
$ =====================================================================

$FUNCTION IS_TRUE$
	$true_list = {1, "1", "true", "TRUE", "ON", "ENABLE"}$
	$false_list = {0, "0", "false", "FALSE", "OFF", "DISABLE"}$
	$error_flag = 1$
	
	$FOREACH false false_list$
		$IF EQ(false, ARGV[1])$
			$check_result = VALUE("FALSE", 0)$
			$error_flag = 0$
		$END$
	$END$
	$FOREACH true true_list$
		$IF EQ(true, ARGV[1])$
			$check_result = VALUE("TRUE", 1)$
			$error_flag = 0$
		$END$
	$END$

	$IF error_flag > 0$
		$ERROR ARGV[2]$$FORMAT(_("%1% must be boolean type"), ARGV[1])$$END$
	$END$

	$RESULT = check_result$
$END$

$	// �������ȥ��ڥ졼���������å�
$IF !IS_TRUE(PduRGeneral.PduRZeroCostOperation[1]) $
	$ERROR PduRGeneral.PduRZeroCostOperation.TEXT_LINE[1]$$FORMAT(_("PduRZeroCostOperation must be true."))$$END$$DIE()$
$END$

$error = 0$

$	// ����PDU-ID�����å�
$FOREACH canif_index CanIfRxPduCfg.ID_LIST$
	$canif_pduref = CanIfRxPduCfg.CanIfRxPduRef[canif_index]$

$	// CanIf��PduR��PduR��Com�ˤ�����PDU-ID
	$FOREACH pdur_index PduRRoutingPath.ID_LIST$
		$IF EQ(PduRSrcPdu.PduRSrcPduRef[pdur_index], canif_pduref)$
			$FOREACH com_index ComIPdu.ID_LIST$
				$IF EQ(ComIPdu.ComPduIdRef[com_index], canif_pduref)$
$					// PduRSourcePduHandleId���б�����ComIPduHandleId�����פ��Ƥ��ʤ�
					$IF !EQ(PduRSrcPdu.PduRSourcePduHandleId[pdur_index], ComIPdu.ComIPduHandleId[com_index])$
						$ERROR PduRSrcPdu.PduRSourcePduHandleId.TEXT_LINE[pdur_index]$$FORMAT(_("PDU-ID mismatch PduRSourcePduHandleId:`%1%\' and ComIPduHandleId:`%2%\'."), PduRSrcPdu.PduRSourcePduHandleId[pdur_index], ComIPdu.ComIPduHandleId[com_index])$$END$
						$error = 1$
					$END$
				$END$
			$END$
		$END$
	$END$
$END$

$	// ����PDU-ID�����å�
$FOREACH canif_index CanIfTxPduCfg.ID_LIST$
	$canif_pduid = CanIfTxPduCfg.CanIfTxPduId[canif_index]$
	$canif_pduref = CanIfTxPduCfg.CanIfTxPduRef[canif_index]$

$	// Com��PduR��PduR��CanIf�ˤ�����PDU-ID
	$FOREACH pdur_index PduRRoutingPath.ID_LIST$
		$IF EQ(PduRSrcPdu.PduRSrcPduRef[pdur_index], canif_pduref)$
$			// CanIfTxPduId���б�����PduRSourcePduHandleId�����פ��Ƥ��ʤ�
			$IF !EQ(PduRSrcPdu.PduRSourcePduHandleId[pdur_index], canif_pduid)$
				$ERROR PduRSrcPdu.PduRSourcePduHandleId.TEXT_LINE[pdur_index]$$FORMAT(_("PDU-ID mismatch CanIfTxPduId:`%1%\' and PduRSourcePduHandleId:`%2%\'."), canif_pduid, PduRSrcPdu.PduRSourcePduHandleId[pdur_index])$$END$
				$error = 1$
			$END$

$			// ������λ���ΤΤ����PduRDestPduHandleId�����ꤵ��Ƥ��ʤ���硤
$			// ��³��ID�����å����Ǥ��ʤ��Τǥ��顼��λ�Ȥ���
			$IF !LENGTH(PduRDestPdu.PduRDestPduHandleId[pdur_index])$
				$ERROR$$FORMAT(_("PduRDestPduHandleId is not defined for PduRRoutingPath:`%1%\'."), PduRRoutingPath[pdur_index])$$END$$DIE()$
			$END$

$			// ������λ������PDU-ID��ǧ�Τ�����ݻ�����
			$temp_pdur_dest_id = PduRDestPdu.PduRDestPduHandleId[pdur_index]$
		$END$
	$END$

$	// ������λ����(CanIf��PduR��PduR��Com�ˤ�����PDU-ID)
	$FOREACH com_index ComIPdu.ID_LIST$
		$IF EQ(ComIPdu.ComPduIdRef[com_index], canif_pduref)$
$			// ComIPduHandleId���б�����PduRDestPduHandleId�����פ��Ƥ��ʤ�
			$IF !EQ(ComIPdu.ComIPduHandleId[com_index], temp_pdur_dest_id)$
				$ERROR ComIPdu.ComIPduHandleId.TEXT_LINE[com_index]$$FORMAT(_("PDU-ID mismatch ComIPduHandleId:`%1%\' and PduRDestPduHandleId:`%2%\'."), ComIPdu.ComIPduHandleId[com_index], temp_pdur_dest_id)$$END$
				$error = 1$
			$END$
		$END$
	$END$
$END$

$	// ���硼�ȥ͡�������å�[ecuc_sws_6074]
$FOREACH index1 PduRRoutingPath.ID_LIST$
	$short_name = PduRSrcPdu[index1]$
	$src_id = PduRSrcPdu.PduRSourcePduHandleId[index1]$
	$FOREACH index2 RANGE(index1 + 1, LENGTH(PduRRoutingPath.ID_LIST))$
		$IF EQ(short_name, PduRSrcPdu[index2])$
			$IF !EQ(src_id, PduRSrcPdu.PduRSourcePduHandleId[index2])$
				$ERROR PduRSrcPdu.PduRSourcePduHandleId.TEXT_LINE[index2]$$FORMAT(_("PDU-ID or ShortName is invalid: `%1%\' indicates `%2%\' and `%3%\'."), short_name, src_id, PduRSrcPdu.PduRSourcePduHandleId[index2])$$END$
				$error = 1$
			$END$
		$END$
	$END$

	$IF LENGTH(PduRDestPdu.PduRDestPduHandleId[index1])$
		$short_name = PduRDestPdu[index1]$
		$dest_id = PduRDestPdu.PduRDestPduHandleId[index1]$
		$FOREACH index2 RANGE(index1 + 1, LENGTH(PduRRoutingPath.ID_LIST))$
			$IF EQ(short_name, PduRDestPdu[index2])$
				$IF LENGTH(PduRDestPdu.PduRDestPduHandleId[index2]) && !EQ(dest_id, PduRDestPdu.PduRDestPduHandleId[index2])$
					$ERROR PduRDestPdu.PduRDestPduHandleId.TEXT_LINE[index2]$$FORMAT(_("PDU-ID or ShortName is invalid: `%1%\' indicates `%2%\' and `%3%\'."), short_name, dest_id, PduRDestPdu.PduRDestPduHandleId[index2])$$END$
					$error = 1$
				$END$
			$END$
		$END$
	$END$
$END$

$IF (error != 0)$
	$DIE()$
$END$


$	// �ץꥳ��ѥ����ѥإå�
$FILE "PduR_Cfg.h"$
/* PduR_Cfg.h */$NL$
#ifndef TOPPERS_PDUR_CFG_H$NL$
#define TOPPERS_PDUR_CFG_H$NL$
$NL$
$FOREACH index PduRRoutingPath.ID_LIST$
	#define PduRConf_PduRSourcePduHandleId_$PduRSrcPdu[index]$		$PduRSrcPdu.PduRSourcePduHandleId[index]$$NL$
	$IF LENGTH(PduRDestPdu.PduRDestPduHandleId[index])$
		#define PduRConf_PduRDestPduHandleId_$PduRDestPdu[index]$		$PduRDestPdu.PduRDestPduHandleId[index]$$NL$
	$END$
$END$
$NL$
#endif /* TOPPERS_PDUR_CFG_H */$NL$


$	// Com�ѥإå�
$FILE "PduR_Com.h"$
/* PduR_Com.h */$NL$
#ifndef TOPPERS_PDUR_COM_H$NL$
#define TOPPERS_PDUR_COM_H$NL$
$NL$
#include "CanIf.h"$NL$
$NL$
#define PduR_ComTransmit		CanIf_Transmit$NL$
#define PduR_ComCancelTransmit	CanIf_CancelTransmit$NL$
$NL$
#endif /* TOPPERS_PDUR_COM_H */$NL$


$	// CanIf�ѥإå�
$FILE "PduR_CanIf.h"$
/* PduR_CanIf.h */$NL$
#ifndef TOPPERS_PDUR_CANIF_H$NL$
#define TOPPERS_PDUR_CANIF_H$NL$
$NL$
#include "Com.h"$NL$
$NL$
#define PduR_CanIfRxIndication		Com_RxIndication$NL$
#define PduR_CanIfTxConfirmation	Com_TxConfirmation$NL$
$NL$
#endif /* TOPPERS_PDUR_CANIF_H */$NL$

