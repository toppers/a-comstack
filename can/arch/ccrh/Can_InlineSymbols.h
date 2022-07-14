/*
 *  TOPPERS/A-CAN
 *      Automotive CAN
 *
 *  Copyright (C) 2014 by FUJI SOFT INCORPORATED, JAPAN
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
 *  $Id: Can_InlineSymbols.h 907 2014-12-24 02:47:55Z shigihara $
 */

#ifndef TOPPERS_CAN_INLINESYMBOL_CCRH_H
#define TOPPERS_CAN_INLINESYMBOL_CCRH_H

/*
 *  コンパイラ依存定義
 */
/* Can_Prc.h */
#pragma inline port_init
#pragma inline can_target_init_unit_phase1
#pragma inline can_target_init_controller_phase1
#pragma inline can_target_init_controller_phase2
#pragma inline can_target_init_controller_phase3
#pragma inline can_target_rbox_initialize
#pragma inline can_target_tbox_initialize
#pragma inline can_target_init_unit_phase2
#pragma inline can_target_change_baudrate
#pragma inline can_target_start_controller_and_change_interrupt
#pragma inline can_target_stop_controller_and_change_interrupt
#pragma inline can_target_sleep_controller_and_change_interrupt
#pragma inline can_target_wakeup_controller_and_change_interrupt
#pragma inline can_target_disable_controller_interrupts
#pragma inline can_target_enable_controller_interrupts
#pragma inline can_target_check_wakeup
#pragma inline can_target_transmit
#pragma inline can_target_check_and_get_rbox
#pragma inline can_target_get_rdata
#pragma inline can_target_check_and_get_tbox
#pragma inline can_target_get_mode
#pragma inline can_target_busy_wait


#endif /* TOPPERS_CAN_INLINESYMBOL_CCRH_H */
