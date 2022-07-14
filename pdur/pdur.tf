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
$  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
$  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
$  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
$  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
$      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
$      スコード中に含まれていること．
$  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
$      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
$      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
$      の無保証規定を掲載すること．
$  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
$      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
$      と．
$    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
$        作権表示，この利用条件および下記の無保証規定を掲載すること．
$    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
$        報告すること．
$  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
$      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
$      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
$      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
$      免責すること．
$
$  本ソフトウェアは，AUTOSAR（AUTomotive Open System ARchitecture）仕
$  様に基づいている．上記の許諾は，AUTOSARの知的財産権を許諾するもので
$  はない．AUTOSARは，AUTOSAR仕様に基づいたソフトウェアを商用目的で利
$  用する者に対して，AUTOSARパートナーになることを求めている．
$
$  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
$  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
$  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
$  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
$  の責任を負わない．
$
$  $Id: pdur.tf 425 2014-09-17 00:46:01Z fsi-dankei $
$

$ =====================================================================
$ boolean判定関数
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

$	// ゼロコストオペレーションチェック
$IF !IS_TRUE(PduRGeneral.PduRZeroCostOperation[1]) $
	$ERROR PduRGeneral.PduRZeroCostOperation.TEXT_LINE[1]$$FORMAT(_("PduRZeroCostOperation must be true."))$$END$$DIE()$
$END$

$error = 0$

$	// 受信PDU-IDチェック
$FOREACH canif_index CanIfRxPduCfg.ID_LIST$
	$canif_pduref = CanIfRxPduCfg.CanIfRxPduRef[canif_index]$

$	// CanIf→PduRとPduR→ComにおけるPDU-ID
	$FOREACH pdur_index PduRRoutingPath.ID_LIST$
		$IF EQ(PduRSrcPdu.PduRSrcPduRef[pdur_index], canif_pduref)$
			$FOREACH com_index ComIPdu.ID_LIST$
				$IF EQ(ComIPdu.ComPduIdRef[com_index], canif_pduref)$
$					// PduRSourcePduHandleIdに対応するComIPduHandleIdが一致していない
					$IF !EQ(PduRSrcPdu.PduRSourcePduHandleId[pdur_index], ComIPdu.ComIPduHandleId[com_index])$
						$ERROR PduRSrcPdu.PduRSourcePduHandleId.TEXT_LINE[pdur_index]$$FORMAT(_("PDU-ID mismatch PduRSourcePduHandleId:`%1%\' and ComIPduHandleId:`%2%\'."), PduRSrcPdu.PduRSourcePduHandleId[pdur_index], ComIPdu.ComIPduHandleId[com_index])$$END$
						$error = 1$
					$END$
				$END$
			$END$
		$END$
	$END$
$END$

$	// 送信PDU-IDチェック
$FOREACH canif_index CanIfTxPduCfg.ID_LIST$
	$canif_pduid = CanIfTxPduCfg.CanIfTxPduId[canif_index]$
	$canif_pduref = CanIfTxPduCfg.CanIfTxPduRef[canif_index]$

$	// Com→PduRとPduR→CanIfにおけるPDU-ID
	$FOREACH pdur_index PduRRoutingPath.ID_LIST$
		$IF EQ(PduRSrcPdu.PduRSrcPduRef[pdur_index], canif_pduref)$
$			// CanIfTxPduIdに対応するPduRSourcePduHandleIdが一致していない
			$IF !EQ(PduRSrcPdu.PduRSourcePduHandleId[pdur_index], canif_pduid)$
				$ERROR PduRSrcPdu.PduRSourcePduHandleId.TEXT_LINE[pdur_index]$$FORMAT(_("PDU-ID mismatch CanIfTxPduId:`%1%\' and PduRSourcePduHandleId:`%2%\'."), canif_pduid, PduRSrcPdu.PduRSourcePduHandleId[pdur_index])$$END$
				$error = 1$
			$END$

$			// 送信完了通知のためのPduRDestPduHandleIdが指定されていない場合，
$			// 後続のIDチェックができないのでエラー終了とする
			$IF !LENGTH(PduRDestPdu.PduRDestPduHandleId[pdur_index])$
				$ERROR$$FORMAT(_("PduRDestPduHandleId is not defined for PduRRoutingPath:`%1%\'."), PduRRoutingPath[pdur_index])$$END$$DIE()$
			$END$

$			// 送信完了通知用PDU-ID確認のために保持する
			$temp_pdur_dest_id = PduRDestPdu.PduRDestPduHandleId[pdur_index]$
		$END$
	$END$

$	// 送信完了通知(CanIf→PduRとPduR→ComにおけるPDU-ID)
	$FOREACH com_index ComIPdu.ID_LIST$
		$IF EQ(ComIPdu.ComPduIdRef[com_index], canif_pduref)$
$			// ComIPduHandleIdに対応するPduRDestPduHandleIdが一致していない
			$IF !EQ(ComIPdu.ComIPduHandleId[com_index], temp_pdur_dest_id)$
				$ERROR ComIPdu.ComIPduHandleId.TEXT_LINE[com_index]$$FORMAT(_("PDU-ID mismatch ComIPduHandleId:`%1%\' and PduRDestPduHandleId:`%2%\'."), ComIPdu.ComIPduHandleId[com_index], temp_pdur_dest_id)$$END$
				$error = 1$
			$END$
		$END$
	$END$
$END$

$	// ショートネームチェック[ecuc_sws_6074]
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


$	// プリコンパイル用ヘッダ
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


$	// Com用ヘッダ
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


$	// CanIf用ヘッダ
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

